////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/TypeId.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/RegisterComponent.h>
#include <NsApp/EntryPoint.h>
#include <NsApp/Application.h>
#include <NsApp/EmbeddedXamlProvider.h>
#include <NsApp/EmbeddedFontProvider.h>
#include <NsApp/ApplicationLauncher.h>
#include <NsApp/Window.h>
#include <NsGui/IntegrationAPI.h>
#include <NsGui/SolidColorBrush.h>
#include <NsDrawing/Color.h>

#include "NumericUpDown.h"

#include "App.xaml.bin.h"
#include "MainWindow.xaml.bin.h"
#include "NumericUpDown.xaml.bin.h"
#include "Aero Matics Regular.ttf.bin.h"


using namespace Noesis;
using namespace NoesisApp;


namespace UserControl
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class App final: public Application
{
    NS_IMPLEMENT_INLINE_REFLECTION(App, Application)
    {
        NsMeta<TypeId>("UserControl.App");
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class MainWindow final: public Window
{
public:
    MainWindow()
    {
        InitializeComponent();

        _bg = FindName<SolidColorBrush>("BgColor");
        _fg = FindName<SolidColorBrush>("FgColor");
    }

private:
    void InitializeComponent()
    {
        Noesis::GUI::LoadComponent(this, "MainWindow.xaml");
    }

    // This code-behind is needed because MultiBindings are not yet supported
    // http://stackoverflow.com/questions/1978316/binding-r-g-b-properties-of-color-in-wpf
    bool ConnectEvent(BaseComponent* source, const char* event, const char* handler) override
    {
        NS_CONNECT_EVENT(NumericUpDown, ValueChanged, BgR_ValueChanged);
        NS_CONNECT_EVENT(NumericUpDown, ValueChanged, BgG_ValueChanged);
        NS_CONNECT_EVENT(NumericUpDown, ValueChanged, BgB_ValueChanged);
        NS_CONNECT_EVENT(NumericUpDown, ValueChanged, FgR_ValueChanged);
        NS_CONNECT_EVENT(NumericUpDown, ValueChanged, FgG_ValueChanged);
        NS_CONNECT_EVENT(NumericUpDown, ValueChanged, FgB_ValueChanged);
        return false;
    }

    void BgR_ValueChanged(BaseComponent*, const RoutedPropertyChangedEventArgs<int>& args)
    {
        Color color = _bg->GetColor();
        _bg->SetColor(Color(args.newValue, color.GetGreenI(), color.GetBlueI(), color.GetAlphaI()));
    }
    
    void BgG_ValueChanged(BaseComponent*, const RoutedPropertyChangedEventArgs<int>& args)
    {
        Color color = _bg->GetColor();
        _bg->SetColor(Color(color.GetRedI(), args.newValue, color.GetBlueI(), color.GetAlphaI()));
    }
    
    void BgB_ValueChanged(BaseComponent*, const RoutedPropertyChangedEventArgs<int>& args)
    {
        Color color = _bg->GetColor();
        _bg->SetColor(Color(color.GetRedI(), color.GetGreenI(), args.newValue, color.GetAlphaI()));
    }
    
    void FgR_ValueChanged(BaseComponent*, const RoutedPropertyChangedEventArgs<int>& args)
    {
        Color color = _fg->GetColor();
        _fg->SetColor(Color(args.newValue, color.GetGreenI(), color.GetBlueI(), color.GetAlphaI()));
    }
    
    void FgG_ValueChanged(BaseComponent*, const RoutedPropertyChangedEventArgs<int>& args)
    {
        Color color = _fg->GetColor();
        _fg->SetColor(Color(color.GetRedI(), args.newValue, color.GetBlueI(), color.GetAlphaI()));
    }
    
    void FgB_ValueChanged(BaseComponent*, const RoutedPropertyChangedEventArgs<int>& args)
    {
        Color color = _fg->GetColor();
        _fg->SetColor(Color(color.GetRedI(), color.GetGreenI(), args.newValue, color.GetAlphaI()));
    }

private:
    SolidColorBrush* _fg;
    SolidColorBrush* _bg;

    NS_IMPLEMENT_INLINE_REFLECTION(MainWindow, Window)
    {
        NsMeta<TypeId>("UserControl.MainWindow");
    }
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        NsRegisterComponent<::UserControl::App>();
        NsRegisterComponent<::UserControl::MainWindow>();
        NsRegisterComponent<::UserControl::NumericUpDown>();
    }

    Ptr<XamlProvider> GetXamlProvider() const override
    {
        EmbeddedXaml xamls[] = 
        {
            { "App.xaml", App_xaml, sizeof(App_xaml) },
            { "MainWindow.xaml", MainWindow_xaml, sizeof(MainWindow_xaml) },
            { "NumericUpDown.xaml", NumericUpDown_xaml, sizeof(NumericUpDown_xaml) }
        };

        return *new EmbeddedXamlProvider(xamls, NS_COUNTOF(xamls));
    }

    Ptr<FontProvider> GetFontProvider() const override
    {
        EmbeddedFont fonts[] =
        {
            { "", Aero_Matics_Regular_ttf, sizeof(Aero_Matics_Regular_ttf) }
        };

        return *new EmbeddedFontProvider(fonts, NS_COUNTOF(fonts));
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
