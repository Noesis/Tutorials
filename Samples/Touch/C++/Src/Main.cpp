////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/RegisterComponent.h>
#include <NsGui/MatrixTransform.h>
#include <NsGui/Canvas.h>
#include <NsGui/Rectangle.h>
#include <NsGui/Brushes.h>
#include <NsGui/SolidColorBrush.h>
#include <NsGui/Panel.h>
#include <NsGui/IntegrationAPI.h>
#include <NsMath/Transform.h>
#include <NsApp/EmbeddedXamlProvider.h>
#include <NsApp/ApplicationLauncher.h>
#include <NsApp/EntryPoint.h>
#include <NsApp/Application.h>
#include <NsApp/Window.h>

#include "App.xaml.bin.h"
#include "MainWindow.xaml.bin.h"


using namespace Noesis;
using namespace NoesisApp;


namespace Touch
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class App final: public Application
{
    NS_IMPLEMENT_INLINE_REFLECTION_(App, Application, "Touch.App")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class MainWindow final: public Window
{
public:
    MainWindow()
    {
        InitializeComponent();
    }

    void OnManipulationStarting(const ManipulationStartingEventArgs& e) override
    {
        Noesis::Rectangle* rectangle = DynamicCast<Noesis::Rectangle*>(e.source);
        if (rectangle != 0)
        {
            Panel::SetZIndex(rectangle, ++_index);
            e.mode = ManipulationModes_All;
            e.manipulationContainer = _root;
            e.handled = true;
        }

        ParentClass::OnManipulationStarting(e);
    }

    void OnManipulationStarted(const ManipulationStartedEventArgs& e) override
    {
        Noesis::Rectangle* rectangle = DynamicCast<Noesis::Rectangle*>(e.source);
        if (rectangle != 0)
        {
            rectangle->SetStroke(Brushes::White());
            e.handled = true;
        }

        ParentClass::OnManipulationStarted(e);
    }

    void OnManipulationInertiaStarting(const ManipulationInertiaStartingEventArgs& e) override
    {
        Noesis::Rectangle* rectangle = DynamicCast<Noesis::Rectangle*>(e.source);
        if (rectangle != 0)
        {
            e.translationBehavior.desiredDeceleration = 360.0f / (100.0f * 1000.0f);
            e.rotationBehavior.desiredDeceleration = 50.0f / (100.0f * 1000.0f);
            e.expansionBehavior.desiredDeceleration = 300.0f / (100.0f * 1000.0f);
            e.handled = true;
        }

        ParentClass::OnManipulationInertiaStarting(e);
    }

    void OnManipulationDelta(const ManipulationDeltaEventArgs& e) override
    {
        Noesis::Rectangle* rectangle = DynamicCast<Noesis::Rectangle*>(e.source);
        if (rectangle != 0)
        {
            MatrixTransform* transform = (MatrixTransform*)rectangle->GetRenderTransform();
            Transform2 mtx = transform->GetMatrix();

            const Noesis::ManipulationDelta& d = e.deltaManipulation;
            const Noesis::Point& o = e.manipulationOrigin;

            mtx.RotateAt(d.rotation * DegToRad, o.x, o.y);
            mtx.ScaleAt(d.scale, d.scale, o.x, o.y);
            mtx.Translate(d.translation.x, d.translation.y);

            transform->SetMatrix(mtx);
            e.handled = true;
        }

        ParentClass::OnManipulationDelta(e);
    }

    void OnManipulationCompleted(const ManipulationCompletedEventArgs& e) override
    {
        Noesis::Rectangle* rectangle = DynamicCast<Noesis::Rectangle*>(e.source);
        if (rectangle != 0)
        {
            rectangle->SetStroke(0);
            e.handled = true;
        }

        ParentClass::OnManipulationCompleted(e);
    }

private:
    void InitializeComponent()
    {
        GUI::LoadComponent(this, "MainWindow.xaml");
    }

    bool ConnectField(BaseComponent* object, const char* name) override
    {
        NS_CONNECT_FIELD(_root, "root");

        return false;
    }

private:
    int _index = 0;
    Canvas* _root = 0;

    NS_IMPLEMENT_INLINE_REFLECTION_(MainWindow, Window, "Touch.MainWindow")
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        RegisterComponent<Touch::App>();
        RegisterComponent<Touch::MainWindow>();
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
