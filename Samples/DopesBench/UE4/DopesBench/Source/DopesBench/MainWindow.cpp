////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "MainWindow.h"

#include <NsCore/ReflectionImplement.h>
#include <NsCore/HighResTimer.h>
#include <NsGui/IntegrationAPI.h>
#include <NsGui/Button.h>
#include <NsGui/Canvas.h>
#include <NsGui/ItemsControl.h>
#include <NsGui/TextBlock.h>
#include <NsGui/UIElementCollection.h>
#include <NsGui/SolidColorBrush.h>
#include <NsGui/RotateTransform.h>
#include <NsGui/IView.h>


#define FRAND (rand() / (float)RAND_MAX)


using namespace DopesBench;


////////////////////////////////////////////////////////////////////////////////////////////////////
float Item::GetTop() const
{
    return _top;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Item::SetTop(float value)
{
    if (_top != value)
    {
        _top = value;
        _changed(this, Noesis::Symbol("Top"));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float Item::GetLeft() const
{
    return _left;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Item::SetLeft(float value)
{
    if (_left != value)
    {
        _left = value;
        _changed(this, Noesis::Symbol("Left"));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float Item::GetRotation() const
{
    return _rotation;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Item::SetRotation(float value)
{
    if (_rotation != value)
    {
        _rotation = value;
        _changed(this, Noesis::Symbol("Rotation"));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::Color& Item::GetColor() const
{
    return _color;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Item::SetColor(const Noesis::Color& value)
{
    if (_color != value)
    {
        _color = value;
        _changed(this, Noesis::Symbol("Color"));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::PropertyChangedEventHandler& Item::PropertyChanged()
{
    return _changed;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_IMPLEMENT_REFLECTION(Item)
{
    NsImpl<Noesis::INotifyPropertyChanged>();

    NsProp("Top", &Item::GetTop, &Item::SetTop);
    NsProp("Left", &Item::GetLeft, &Item::SetLeft);
    NsProp("Rotation", &Item::GetRotation, &Item::SetRotation);
    NsProp("Color", &Item::GetColor, &Item::SetColor);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MainWindow::MainWindow(): runningTest(0)
{
    InitializeComponent();

    list = *new Noesis::Collection<Item>();
    for (int i = 0; i < max; i++)
    {
        list->Add(Noesis::MakePtr<Item>());
    }

    Loaded() += [this](Noesis::BaseComponent*, const Noesis::RoutedEventArgs&)
    {
        GetView()->Rendering() += MakeDelegate(this, &MainWindow::OnRendering);
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::InitializeComponent()
{
    Noesis::GUI::LoadComponent(this, "MainWindow.xaml");

    stop = FindName<Noesis::Button>("stop");
    build = FindName<Noesis::Button>("build");
    reuse = FindName<Noesis::Button>("reuse");
    binding = FindName<Noesis::Button>("binding");
    change = FindName<Noesis::Button>("change");

    canvas = FindName<Noesis::Canvas>("canvas");
    items = FindName<Noesis::ItemsControl>("items");
    dopes = FindName<Noesis::TextBlock>("dopes");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool MainWindow::ConnectEvent(Noesis::BaseComponent* source, const char* event, const char* handler)
{
    NS_CONNECT_EVENT(Noesis::Button, Click, Stop_Clicked);
    NS_CONNECT_EVENT(Noesis::Button, Click, Build_Clicked);
    NS_CONNECT_EVENT(Noesis::Button, Click, Reuse_Clicked);
    NS_CONNECT_EVENT(Noesis::Button, Click, Binding_Clicked);
    NS_CONNECT_EVENT(Noesis::Button, Click, Change_Clicked);

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::OnRendering(Noesis::IView*)
{
    switch (runningTest)
    {
        case 0: break;
        case 1: TestBuild(); break;
        case 2: TestReuse(); break;
        case 3: TestBinding(); break;
        case 4: TestChange(); break;
        default: break;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::TestBuild()
{
    uint64_t start = Noesis::HighResTimer::Ticks();
    uint64_t ticks = start;

    //60hz, 16ms to build the frame
    while (Noesis::HighResTimer::Seconds(ticks - start) * 1000 < 16)
    {
        ticks = Noesis::HighResTimer::Ticks();

        Noesis::Ptr<Noesis::TextBlock> label = *new Noesis::TextBlock();
        label->SetText("Dope");
        Noesis::Ptr<Noesis::SolidColorBrush> brush = *new Noesis::SolidColorBrush(Noesis::Color(FRAND, FRAND, FRAND));
        label->SetForeground(brush);
        Noesis::Ptr<Noesis::RotateTransform> transform = *new Noesis::RotateTransform(FRAND * 360.0f);
        label->SetRenderTransformOrigin(Noesis::Point(0.5f, 0.5f));
        label->SetRenderTransform(transform);

        Noesis::Canvas::SetLeft(label, FRAND * canvas->GetActualWidth());
        Noesis::Canvas::SetTop(label, FRAND * canvas->GetActualHeight());

        if (processed > max)
        {
            canvas->GetChildren()->RemoveAt(0);
        }

        canvas->GetChildren()->Add(label);

        processed++;

        double seconds = Noesis::HighResTimer::Seconds(ticks - prevTicks);
        if (seconds * 1000 > 500)
        {
            double r = (double)(processed - prevProcessed) / seconds;
            prevTicks = ticks;
            prevProcessed = processed;

            if (processed > max)
            {
                char text[256];
                sprintf_s(text, "%.2f Dopes/s", r);
                dopes->SetText(text);
                avgSum += r;
                avgN++;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::TestReuse()
{
    uint64_t start = Noesis::HighResTimer::Ticks();
    uint64_t ticks = start;

    //60hz, 16ms to build the frame
    while (Noesis::HighResTimer::Seconds(ticks - start) * 1000 < 16)
    {
        ticks = Noesis::HighResTimer::Ticks();

        Noesis::Ptr<Noesis::TextBlock> label;
        if (processed < max)
        {
            label = *new Noesis::TextBlock();
            label->SetText("Dope");
            Noesis::Ptr<Noesis::SolidColorBrush> brush = *new Noesis::SolidColorBrush();
            label->SetForeground(brush);
            Noesis::Ptr<Noesis::RotateTransform> transform = *new Noesis::RotateTransform();
            label->SetRenderTransformOrigin(Noesis::Point(0.5f, 0.5f));
            label->SetRenderTransform(transform);
        }
        else
        {
            label.Reset((Noesis::TextBlock*)canvas->GetChildren()->Get(0));
            canvas->GetChildren()->RemoveAt(0);
        }

        ((Noesis::SolidColorBrush*)label->GetForeground())->SetColor(Noesis::Color(FRAND, FRAND, FRAND));
        ((Noesis::RotateTransform*)label->GetRenderTransform())->SetAngle(FRAND * 360.0f);

        Noesis::Canvas::SetLeft(label, FRAND * canvas->GetActualWidth());
        Noesis::Canvas::SetTop(label, FRAND * canvas->GetActualHeight());

        canvas->GetChildren()->Add(label);

        processed++;

        double seconds = Noesis::HighResTimer::Seconds(ticks - prevTicks);
        if (seconds * 1000 > 500)
        {
            double r = (double)(processed - prevProcessed) / seconds;
            prevTicks = ticks;
            prevProcessed = processed;

            if (processed > max)
            {
                char text[256];
                sprintf_s(text, "%.2f Dopes/s", r);
                dopes->SetText(text);
                avgSum += r;
                avgN++;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::TestBinding()
{
    uint64_t start = Noesis::HighResTimer::Ticks();
    uint64_t ticks = start;

    //60hz, 16ms to build the frame
    while (Noesis::HighResTimer::Seconds(ticks - start) * 1000 < 16)
    {
        ticks = Noesis::HighResTimer::Ticks();

        Item* item = list->Get(processed % max);
        item->SetColor(Noesis::Color(FRAND, FRAND, FRAND));
        item->SetRotation(FRAND * 360.0f);
        item->SetLeft(FRAND * canvas->GetActualWidth());
        item->SetTop(FRAND * canvas->GetActualHeight());

        processed++;

        double seconds = Noesis::HighResTimer::Seconds(ticks - prevTicks);
        if (seconds * 1000 > 500)
        {
            double r = (double)(processed - prevProcessed) / seconds;
            prevTicks = ticks;
            prevProcessed = processed;

            if (processed > max)
            {
                char text[256];
                sprintf_s(text, "%.2f Dopes/s", r);
                dopes->SetText(text);
                avgSum += r;
                avgN++;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::TestChange()
{
    uint64_t start = Noesis::HighResTimer::Ticks();
    uint64_t ticks = start;

    //60hz, 16ms to build the frame
    while (Noesis::HighResTimer::Seconds(ticks - start) * 1000 < 16)
    {
        ticks = Noesis::HighResTimer::Ticks();

        if (processed < max)
        {
            Noesis::Ptr<Noesis::TextBlock> label = *new Noesis::TextBlock();
            label->SetText("Dope");
            Noesis::Ptr<Noesis::SolidColorBrush> brush = *new Noesis::SolidColorBrush(Noesis::Color(FRAND, FRAND, FRAND));
            label->SetForeground(brush);
            Noesis::Ptr<Noesis::RotateTransform> transform = *new Noesis::RotateTransform(FRAND * 360.0f);
            label->SetRenderTransformOrigin(Noesis::Point(0.5f, 0.5f));
            label->SetRenderTransform(transform);

            Noesis::Canvas::SetLeft(label, FRAND * canvas->GetActualWidth());
            Noesis::Canvas::SetTop(label, FRAND * canvas->GetActualHeight());

            canvas->GetChildren()->Add(label);
        }
        else
        {
            const char* texts[] = { "Dope", "dOpe", "doPe", "dopE", "DOpe", "dOPe", "doPE" };
            Noesis::TextBlock* label = (Noesis::TextBlock*)canvas->GetChildren()->Get(processed % max);
            label->SetText(texts[processed % NS_COUNTOF(texts)]);
        }

        processed++;

        double seconds = Noesis::HighResTimer::Seconds(ticks - prevTicks);
        if (seconds * 1000 > 500)
        {
            double r = (double)(processed - prevProcessed) / seconds;
            prevTicks = ticks;
            prevProcessed = processed;

            if (processed > max)
            {
                char text[256];
                sprintf_s(text, "%.2f Dopes/s", r);
                dopes->SetText(text);
                avgSum += r;
                avgN++;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::StartTest(int test)
{
    runningTest = test;

    stop->SetVisibility(Noesis::Visibility_Visible);
    dopes->SetVisibility(Noesis::Visibility_Visible);
    build->SetVisibility(Noesis::Visibility_Collapsed);
    reuse->SetVisibility(Noesis::Visibility_Collapsed);
    binding->SetVisibility(Noesis::Visibility_Collapsed);
    change->SetVisibility(Noesis::Visibility_Collapsed);

    items->SetItemsSource(0);
    canvas->GetChildren()->Clear();
    dopes->SetText("Warming up..");

    processed = 0;

    prevTicks = Noesis::HighResTimer::Ticks();
    prevProcessed = 0;
    avgSum = 0;
    avgN = 0;

    srand(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::Stop_Clicked(Noesis::BaseComponent*, const Noesis::RoutedEventArgs&)
{
    stop->SetVisibility(Noesis::Visibility_Collapsed);
    build->SetVisibility(Noesis::Visibility_Visible);
    reuse->SetVisibility(Noesis::Visibility_Visible);
    binding->SetVisibility(Noesis::Visibility_Visible);
    change->SetVisibility(Noesis::Visibility_Visible);

    float avg = float(avgSum / (double)avgN);
    char text[256];
    sprintf_s(text, "%.2f Dopes/s (AVG)", avg);
    dopes->SetText(text);

    runningTest = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::Build_Clicked(Noesis::BaseComponent*, const Noesis::RoutedEventArgs&)
{
    StartTest(1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::Reuse_Clicked(Noesis::BaseComponent*, const Noesis::RoutedEventArgs&)
{
    StartTest(2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::Binding_Clicked(Noesis::BaseComponent*, const Noesis::RoutedEventArgs&)
{
    StartTest(3);
    items->SetItemsSource(list);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::Change_Clicked(Noesis::BaseComponent*, const Noesis::RoutedEventArgs&)
{
    StartTest(4);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_IMPLEMENT_REFLECTION_(DopesBench::MainWindow, "DopesBench.MainWindow")
