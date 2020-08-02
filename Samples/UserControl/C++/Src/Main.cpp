////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionImplementEmpty.h>
#include <NsCore/RegisterComponent.h>
#include <NsApp/EntryPoint.h>
#include <NsApp/Application.h>
#include <NsApp/EmbeddedXamlProvider.h>
#include <NsApp/EmbeddedFontProvider.h>
#include <NsApp/ApplicationLauncher.h>
#include <NsApp/Window.h>
#include <NsGui/IntegrationAPI.h>
#include <NsGui/BaseMultiValueConverter.h>
#include <NsDrawing/Color.h>

#include "NumericUpDown.h"

#include "App.xaml.bin.h"
#include "MainWindow.xaml.bin.h"
#include "NumericUpDown.xaml.bin.h"
#include "Aero Matics Regular.ttf.bin.h"


using namespace Noesis;
using namespace NoesisApp;


namespace UserControls
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class App final: public Application
{
    NS_IMPLEMENT_INLINE_REFLECTION_(App, Application, "UserControls.App")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class MainWindow final: public Window
{
public:
    MainWindow()
    {
        InitializeComponent();
    }

private:
    void InitializeComponent()
    {
        Noesis::GUI::LoadComponent(this, "MainWindow.xaml");
    }

    NS_IMPLEMENT_INLINE_REFLECTION_(MainWindow, Window, "UserControls.MainWindow")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class ColorConverter final: public BaseMultiValueConverter
{
public:
    bool TryConvert(ArrayRef<BaseComponent*> values, const Type*, BaseComponent*,
        Noesis::Ptr<BaseComponent>& result) override
    {
        NS_ASSERT(values.Size() == 3);
        int r = Boxing::Unbox<int>(values[0]);
        int g = Boxing::Unbox<int>(values[1]);
        int b = Boxing::Unbox<int>(values[2]);

        result = Boxing::Box(Color(r, g, b));
        return true;
    }

    NS_IMPLEMENT_INLINE_REFLECTION_(ColorConverter, BaseMultiValueConverter,
        "UserControls.ColorConverter");
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        RegisterComponent<UserControls::App>();
        RegisterComponent<UserControls::MainWindow>();
        RegisterComponent<UserControls::NumericUpDown>();
        RegisterComponent<UserControls::ColorConverter>();
    }

    Noesis::Ptr<XamlProvider> GetXamlProvider() const override
    {
        EmbeddedXaml xamls[] = 
        {
            { "App.xaml", App_xaml },
            { "MainWindow.xaml", MainWindow_xaml },
            { "NumericUpDown.xaml", NumericUpDown_xaml }
        };

        return *new EmbeddedXamlProvider(xamls);
    }

    Noesis::Ptr<FontProvider> GetFontProvider() const override
    {
        EmbeddedFont fonts[] =
        {
            { "", Aero_Matics_Regular_ttf }
        };

        return *new EmbeddedFontProvider(fonts);
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
