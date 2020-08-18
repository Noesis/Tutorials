////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionImplementEmpty.h>
#include <NsCore/RegisterComponent.h>
#include <NsCore/HighResTimer.h>
#include <NsCore/Vector.h>
#include <NsApp/EmbeddedXamlProvider.h>
#include <NsApp/ApplicationLauncher.h>
#include <NsApp/EntryPoint.h>
#include <NsApp/Application.h>
#include <NsApp/Window.h>
#include <NsGui/IntegrationAPI.h>
#include <NsGui/Button.h>
#include <NsGui/TextBlock.h>
#include <NsGui/Canvas.h>
#include <NsGui/ItemsControl.h>
#include <NsGui/UIElementCollection.h>
#include <NsGui/IView.h>
#include <NsGui/SolidColorBrush.h>
#include <NsGui/RotateTransform.h>
#include <NsGui/Collection.h>
#include <NsDrawing/Color.h>

#include "App.xaml.bin.h"
#include "MainWindow.xaml.bin.h"


#define FRAND() (rand() / (float)RAND_MAX)


using namespace Noesis;
using namespace NoesisApp;


namespace DopesBench
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class App final: public Application
{
    NS_IMPLEMENT_INLINE_REFLECTION_(App, Application, "DopesBench.App")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class Item: public BaseComponent, public INotifyPropertyChanged
{
public:
    float GetTop() const { return _top; }
    void SetTop(float value)
    {
        if (_top != value)
        {
            _top = value;
            _changed(this, Symbol("Top"));
        }
    }

    float GetLeft() const { return _left; }
    void SetLeft(float value)
    {
        if (_left != value)
        {
            _left = value;
            _changed(this, Symbol("Left"));
        }
    }

    float GetRotation() const { return _rotation; }
    void SetRotation(float value)
    {
        if (_rotation != value)
        {
            _rotation = value;
            _changed(this, Symbol("Rotation"));
        }
    }

    const Color& GetColor() const { return _color; }
    void SetColor(const Color& value)
    {
        if (_color != value)
        {
            _color = value;
            _changed(this, Symbol("Color"));
        }
    }

    PropertyChangedEventHandler& PropertyChanged() override { return _changed; }

    NS_IMPLEMENT_INTERFACE_FIXUP

private:
    float _top;
    float _left;
    float _rotation;
    Color _color;
    PropertyChangedEventHandler _changed;

    NS_IMPLEMENT_INLINE_REFLECTION(Item, BaseComponent)
    {
        NsImpl<INotifyPropertyChanged>();

        NsProp("Top", &Item::GetTop, &Item::SetTop);
        NsProp("Left", &Item::GetLeft, &Item::SetLeft);
        NsProp("Rotation", &Item::GetRotation, &Item::SetRotation);
        NsProp("Color", &Item::GetColor, &Item::SetColor);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class MainWindow final: public Window
{
public:
    MainWindow()
    {
        InitializeComponent();

        list = *new Collection<Item>();
        for (int i = 0; i < max; i++)
        {
            list->Add(MakePtr<Item>());
        }

        Loaded() += [this](BaseComponent*, const RoutedEventArgs&)
        {
            SetFontSize(24.0f * GetDisplay()->GetScale());

            GetView()->Rendering() += MakeDelegate(this, &MainWindow::OnRendering);
        };
    }

private:
    void InitializeComponent()
    {
        GUI::LoadComponent(this, "MainWindow.xaml");

        stop = FindName<Button>("stop");
        startST = FindName<Button>("startST");
        startReuseST = FindName<Button>("startReuseST");
        startBindingST = FindName<Button>("startBindingST");
        startChangeST = FindName<Button>("startChangeST");

        absolute = FindName<Canvas>("absolute");
        items = FindName<ItemsControl>("items");
        dopes = FindName<TextBlock>("dopes");
    }

    bool ConnectEvent(BaseComponent* source, const char* event, const char* handler) override
    {
        NS_CONNECT_EVENT(Button, Click, Stop_Clicked);
        NS_CONNECT_EVENT(Button, Click, startST_Clicked);
        NS_CONNECT_EVENT(Button, Click, startReuseST_Clicked);
        NS_CONNECT_EVENT(Button, Click, startBindingST_Clicked);
        NS_CONNECT_EVENT(Button, Click, startChangeST_Clicked);

        return false;
    }

    void OnRendering(IView*)
    {
        renderingCallback();
    }

    void StartTestST()
    {
        srand(0);

        breakTest = false;

        processed = 0;

        prevTicks = HighResTimer::Ticks();
        prevProcessed = 0;
        avgSum = 0;
        avgN = 0;

        renderingCallback = [this]()
        {
            uint64_t start = HighResTimer::Ticks();
            uint64_t ticks = start;

            if (breakTest)
            {
                float avg = float(avgSum / (double)avgN);
                String text(String::VarArgs(), "%.2f Dopes/s (AVG)", avg);
                dopes->SetText(text.Str());

                renderingCallback = RenderingCallback();
                return;
            }

            //60hz, 16ms to build the frame
            while (HighResTimer::Seconds(ticks - start) * 1000 < 16)
            {
                ticks = HighResTimer::Ticks();

                Ptr<TextBlock> label = *new TextBlock();
                label->SetText("Dope");
                Ptr<SolidColorBrush> brush = *new SolidColorBrush(Color(FRAND(), FRAND(), FRAND()));
                label->SetForeground(brush);
                Ptr<RotateTransform> transform = *new RotateTransform(FRAND() * 360.0f);
                label->SetRenderTransformOrigin(Point(0.5f, 0.5f));
                label->SetRenderTransform(transform);

                Canvas::SetLeft(label, FRAND() * absolute->GetActualWidth());
                Canvas::SetTop(label, FRAND() * absolute->GetActualHeight());

                if (processed > max)
                {
                    absolute->GetChildren()->RemoveAt(0);
                }

                absolute->GetChildren()->Add(label);

                processed++;

                double seconds = HighResTimer::Seconds(ticks - prevTicks);
                if (seconds * 1000 > 500)
                {
                    double r = (double)(processed - prevProcessed) / seconds;
                    prevTicks = ticks;
                    prevProcessed = processed;

                    if (processed > max)
                    {
                        String text(String::VarArgs(), "%.2f Dopes/s", r);
                        dopes->SetText(text.Str());
                        avgSum += r;
                        avgN++;
                    }
                }
            }
        };
    }

    void StartTestReuseST()
    {
        srand(0);

        breakTest = false;

        processed = 0;

        prevTicks = HighResTimer::Ticks();
        prevProcessed = 0;
        avgSum = 0;
        avgN = 0;

        renderingCallback = [this]()
        {
            uint64_t start = HighResTimer::Ticks();
            uint64_t ticks = start;

            if (breakTest)
            {
                float avg = float(avgSum / (double)avgN);
                String text(String::VarArgs(), "%.2f Dopes/s (AVG)", avg);
                dopes->SetText(text.Str());

                renderingCallback = RenderingCallback();
                return;
            }

            //60hz, 16ms to build the frame
            while (HighResTimer::Seconds(ticks - start) * 1000 < 16)
            {
                ticks = HighResTimer::Ticks();

                Ptr<TextBlock> label;
                if (cache.Size() == 0)
                {
                    label = *new TextBlock();
                    Ptr<SolidColorBrush> brush = *new SolidColorBrush();
                    label->SetForeground(brush);
                    Ptr<RotateTransform> transform = *new RotateTransform();
                    label->SetRenderTransformOrigin(Point(0.5f, 0.5f));
                    label->SetRenderTransform(transform);
                }
                else
                {
                    label = cache.Back();
                    cache.PopBack();
                }

                label->SetText("Dope");
                ((SolidColorBrush*)label->GetForeground())->SetColor(Color(FRAND(), FRAND(), FRAND()));
                ((RotateTransform*)label->GetRenderTransform())->SetAngle(FRAND() * 360.0f);

                Canvas::SetLeft(label, FRAND() * absolute->GetActualWidth());
                Canvas::SetTop(label, FRAND() * absolute->GetActualHeight());

                if (processed > max)
                {
                    cache.EmplaceBack().Reset((TextBlock*)absolute->GetChildren()->Get(0));
                    absolute->GetChildren()->RemoveAt(0);
                }

                absolute->GetChildren()->Add(label);

                processed++;

                double seconds = HighResTimer::Seconds(ticks - prevTicks);
                if (seconds * 1000 > 500)
                {
                    double r = (double)(processed - prevProcessed) / seconds;
                    prevTicks = ticks;
                    prevProcessed = processed;

                    if (processed > max)
                    {
                        String text(String::VarArgs(), "%.2f Dopes/s", r);
                        dopes->SetText(text.Str());
                        avgSum += r;
                        avgN++;
                    }
                }
            }
        };
    }

    void StartTestBindingST()
    {
        srand(0);

        breakTest = false;

        processed = 0;

        prevTicks = HighResTimer::Ticks();
        prevProcessed = 0;
        avgSum = 0;
        avgN = 0;

        items->SetItemsSource(list);

        renderingCallback = [this]()
        {
            uint64_t start = HighResTimer::Ticks();
            uint64_t ticks = start;

            if (breakTest)
            {
                float avg = float(avgSum / (double)avgN);
                String text(String::VarArgs(), "%.2f Dopes/s (AVG)", avg);
                dopes->SetText(text.Str());

                renderingCallback = RenderingCallback();
                return;
            }

            //60hz, 16ms to build the frame
            while (HighResTimer::Seconds(ticks - start) * 1000 < 16)
            {
                ticks = HighResTimer::Ticks();

                Item* item = list->Get(processed % max);
                item->SetColor(Color(FRAND(), FRAND(), FRAND()));
                item->SetRotation(FRAND() * 360.0f);
                item->SetLeft(FRAND() * absolute->GetActualWidth());
                item->SetTop(FRAND() * absolute->GetActualHeight());

                processed++;

                double seconds = HighResTimer::Seconds(ticks - prevTicks);
                if (seconds * 1000 > 500)
                {
                    double r = (double)(processed - prevProcessed) / seconds;
                    prevTicks = ticks;
                    prevProcessed = processed;

                    if (processed > max)
                    {
                        String text(String::VarArgs(), "%.2f Dopes/s", r);
                        dopes->SetText(text.Str());
                        avgSum += r;
                        avgN++;
                    }
                }
            }
        };
    }

    void StartTestChangeST()
    {
        srand(0);

        breakTest = false;

        processed = 0;

        prevTicks = HighResTimer::Ticks();
        prevProcessed = 0;
        avgSum = 0;
        avgN = 0;

        renderingCallback = [this]()
        {
            uint64_t start = HighResTimer::Ticks();
            uint64_t ticks = start;

            if (breakTest)
            {
                float avg = float(avgSum / (double)avgN);
                String text(String::VarArgs(), "%.2f Dopes/s (AVG)", avg);
                dopes->SetText(text.Str());

                renderingCallback = RenderingCallback();
                return;
            }

            //60hz, 16ms to build the frame
            while (HighResTimer::Seconds(ticks - start) * 1000 < 16)
            {
                ticks = HighResTimer::Ticks();

                if (processed < max)
                {
                    Ptr<TextBlock> label = *new TextBlock();
                    label->SetText("Dope");
                    Ptr<SolidColorBrush> brush = *new SolidColorBrush(Color(FRAND(), FRAND(), FRAND()));
                    label->SetForeground(brush);
                    Ptr<RotateTransform> transform = *new RotateTransform(FRAND() * 360.0f);
                    label->SetRenderTransformOrigin(Point(0.5f, 0.5f));
                    label->SetRenderTransform(transform);

                    Canvas::SetLeft(label, FRAND() * absolute->GetActualWidth());
                    Canvas::SetTop(label, FRAND() * absolute->GetActualHeight());

                    absolute->GetChildren()->Add(label);
                }
                else
                {
                    const char* texts[] = { "Dope", "dOpe", "doPe", "dopE", "DOpe", "dOPe", "doPE" };
                    TextBlock* label = (TextBlock*)absolute->GetChildren()->Get(processed % max);
                    label->SetText(texts[processed % NS_COUNTOF(texts)]);
                }

                processed++;

                double seconds = HighResTimer::Seconds(ticks - prevTicks);
                if (seconds * 1000 > 500)
                {
                    double r = (double)(processed - prevProcessed) / seconds;
                    prevTicks = ticks;
                    prevProcessed = processed;

                    if (processed > max)
                    {
                        String text(String::VarArgs(), "%.2f Dopes/s", r);
                        dopes->SetText(text.Str());
                        avgSum += r;
                        avgN++;
                    }
                }
            }
        };
    }

    void SetControlsAtStart()
    {
        stop->SetVisibility(Visibility_Visible);
        dopes->SetVisibility(Visibility_Visible);
        startST->SetVisibility(Visibility_Collapsed);
        startReuseST->SetVisibility(Visibility_Collapsed);
        startBindingST->SetVisibility(Visibility_Collapsed);
        startChangeST->SetVisibility(Visibility_Collapsed);

        items->SetItemsSource(0);
        absolute->GetChildren()->Clear();
        dopes->SetText("Warming up..");
    }

    void Stop_Clicked(BaseComponent*, const RoutedEventArgs&)
    {
        breakTest = true;
        stop->SetVisibility(Visibility_Collapsed);
        startST->SetVisibility(Visibility_Visible);
        startReuseST->SetVisibility(Visibility_Visible);
        startBindingST->SetVisibility(Visibility_Visible);
        startChangeST->SetVisibility(Visibility_Visible);

        cache.Clear();
    }

    void startST_Clicked(BaseComponent*, const RoutedEventArgs&)
    {
        SetControlsAtStart();
        StartTestST();
    }
    void startReuseST_Clicked(BaseComponent*, const RoutedEventArgs&)
    {
        SetControlsAtStart();
        StartTestReuseST();
    }
    void startBindingST_Clicked(BaseComponent*, const RoutedEventArgs&)
    {
        SetControlsAtStart();
        StartTestBindingST();
    }
    void startChangeST_Clicked(BaseComponent*, const RoutedEventArgs&)
    {
        SetControlsAtStart();
        StartTestChangeST();
    }

private:
    volatile bool breakTest = false;
    const int max = 600;

    int processed = 0;

    uint64_t prevTicks = 0;
    int prevProcessed = 0;
    double avgSum = 0;
    int avgN = 0;

    Button* stop;
    Button* startST;
    Button* startReuseST;
    Button* startBindingST;
    Button* startChangeST;

    Canvas* absolute;
    ItemsControl* items;
    TextBlock* dopes;

    Vector<Ptr<TextBlock>> cache;
    Ptr<Collection<Item>> list;

    typedef Delegate<void ()> RenderingCallback;
    RenderingCallback renderingCallback;

    NS_IMPLEMENT_INLINE_REFLECTION_(MainWindow, Window, "DopesBench.MainWindow")
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        RegisterComponent<DopesBench::App>();
        RegisterComponent<DopesBench::MainWindow>();
    }

    Noesis::Ptr<XamlProvider> GetXamlProvider() const override
    {
        EmbeddedXaml xamls[] = 
        {
            { "App.xaml", App_xaml },
            { "MainWindow.xaml", MainWindow_xaml }
        };

        return *new EmbeddedXamlProvider(xamls);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
int NsMain(int argc, char **argv)
{
    AppLauncher launcher;
    launcher.SetArguments(argc, argv);
    launcher.SetApplicationFile("App.xaml");
    return launcher.Run();
}
