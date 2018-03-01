////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/TypeId.h>
#include <NsCore/ReflectionImplement.h>
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
    NS_IMPLEMENT_INLINE_REFLECTION(App, Application)
    {
        NsMeta<TypeId>("CustomControl.App");
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class MainWindow final: public Window
{
    NS_IMPLEMENT_INLINE_REFLECTION(MainWindow, Window)
    {
        NsMeta<TypeId>("CustomControl.MainWindow");
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class HoursConverter: public BaseValueConverter
{
public:
    bool TryConvert(BaseComponent* value, const Type* type, BaseComponent* /*parameter*/,
        Ptr<BaseComponent>& result)
    {
        if (Boxing::CanUnbox<int>(value) && type == TypeOf<float>())
        {
            int hours = Boxing::Unbox<int>(value);
            result = Boxing::Box(hours * 30.0f);
            return true;
        }

        return false;
    }

    NS_IMPLEMENT_INLINE_REFLECTION(HoursConverter, BaseValueConverter)
    {
        NsMeta<TypeId>("CustomControl.HoursConverter");
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class MinutesConverter: public BaseValueConverter
{
public:
    bool TryConvert(BaseComponent* value, const Type* type, BaseComponent* /*parameter*/,
        Ptr<BaseComponent>& result)
    {
        if (Boxing::CanUnbox<int>(value) && type == TypeOf<float>())
        {
            int minutes = Boxing::Unbox<int>(value);
            result = Boxing::Box(minutes * 6.0f);
            return true;
        }

        return false;
    }

    NS_IMPLEMENT_INLINE_REFLECTION(MinutesConverter, BaseValueConverter)
    {
        NsMeta<TypeId>("CustomControl.MinutesConverter");
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class SecondsConverter: public BaseValueConverter
{
public:
    bool TryConvert(BaseComponent* value, const Type* type, BaseComponent* /*parameter*/,
        Ptr<BaseComponent>& result)
    {
        if (Boxing::CanUnbox<int>(value) && type == TypeOf<float>())
        {
            int seconds = Boxing::Unbox<int>(value);
            result = Boxing::Box(seconds * 6.0f);
            return true;
        }

        return false;
    }

    NS_IMPLEMENT_INLINE_REFLECTION(SecondsConverter, BaseValueConverter)
    {
        NsMeta<TypeId>("CustomControl.SecondsConverter");
    }
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        NsRegisterComponent<CustomControl::App>();
        NsRegisterComponent<CustomControl::MainWindow>();
        NsRegisterComponent<CustomControl::DateTime>();
        NsRegisterComponent<CustomControl::HoursConverter>();
        NsRegisterComponent<CustomControl::MinutesConverter>();
        NsRegisterComponent<CustomControl::SecondsConverter>();
    }

    Ptr<XamlProvider> GetXamlProvider() const override
    {
        EmbeddedXaml xamls[] = 
        {
            { "App.xaml", App_xaml, sizeof(App_xaml) },
            { "MainWindow.xaml", MainWindow_xaml, sizeof(MainWindow_xaml) },
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
