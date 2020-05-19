////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionImplementEmpty.h>
#include <NsCore/RegisterComponent.h>
#include <NsCore/Boxing.h>
#include <NsApp/EntryPoint.h>
#include <NsApp/Application.h>
#include <NsApp/EmbeddedXamlProvider.h>
#include <NsApp/EmbeddedFontProvider.h>
#include <NsApp/ApplicationLauncher.h>
#include <NsApp/Window.h>
#include <NsGui/BaseValueConverter.h>

#include "DateTime.h"

#include "App.xaml.bin.h"
#include "MainWindow.xaml.bin.h"
#include "Aero Matics Regular.ttf.bin.h"


using namespace Noesis;
using namespace NoesisApp;


namespace CustomControl
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class App final: public Application
{
    NS_IMPLEMENT_INLINE_REFLECTION_(App, Application, "CustomControl.App")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class MainWindow final: public Window
{
    NS_IMPLEMENT_INLINE_REFLECTION_(MainWindow, Window, "CustomControl.MainWindow")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class HoursConverter: public BaseValueConverter
{
public:
    bool TryConvert(BaseComponent* value, const Type* type, BaseComponent* /*parameter*/,
        Noesis::Ptr<BaseComponent>& result)
    {
        if (Boxing::CanUnbox<int>(value) && type == TypeOf<float>())
        {
            int hours = Boxing::Unbox<int>(value);
            result = Boxing::Box(hours * 30.0f);
            return true;
        }

        return false;
    }

    NS_IMPLEMENT_INLINE_REFLECTION_(HoursConverter, BaseValueConverter, "CustomControl.HoursConverter")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class MinutesConverter: public BaseValueConverter
{
public:
    bool TryConvert(BaseComponent* value, const Type* type, BaseComponent* /*parameter*/,
        Noesis::Ptr<BaseComponent>& result)
    {
        if (Boxing::CanUnbox<int>(value) && type == TypeOf<float>())
        {
            int minutes = Boxing::Unbox<int>(value);
            result = Boxing::Box(minutes * 6.0f);
            return true;
        }

        return false;
    }

    NS_IMPLEMENT_INLINE_REFLECTION_(MinutesConverter, BaseValueConverter, "CustomControl.MinutesConverter")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class SecondsConverter: public BaseValueConverter
{
public:
    bool TryConvert(BaseComponent* value, const Type* type, BaseComponent* /*parameter*/,
        Noesis::Ptr<BaseComponent>& result)
    {
        if (Boxing::CanUnbox<int>(value) && type == TypeOf<float>())
        {
            int seconds = Boxing::Unbox<int>(value);
            result = Boxing::Box(seconds * 6.0f);
            return true;
        }

        return false;
    }

    NS_IMPLEMENT_INLINE_REFLECTION_(SecondsConverter, BaseValueConverter, "CustomControl.SecondsConverter")
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        RegisterComponent<CustomControl::App>();
        RegisterComponent<CustomControl::MainWindow>();
        RegisterComponent<CustomControl::DateTime>();
        RegisterComponent<CustomControl::HoursConverter>();
        RegisterComponent<CustomControl::MinutesConverter>();
        RegisterComponent<CustomControl::SecondsConverter>();
    }

    Noesis::Ptr<XamlProvider> GetXamlProvider() const override
    {
        EmbeddedXaml xamls[] = 
        {
            { "App.xaml", App_xaml },
            { "MainWindow.xaml", MainWindow_xaml },
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
