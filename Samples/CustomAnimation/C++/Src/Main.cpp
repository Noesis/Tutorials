////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionImplementEmpty.h>
#include <NsCore/RegisterComponent.h>
#include <NsCore/EnumConverter.h>
#include <NsApp/EmbeddedXamlProvider.h>
#include <NsApp/EmbeddedFontProvider.h>
#include <NsApp/ApplicationLauncher.h>
#include <NsApp/EntryPoint.h>
#include <NsApp/Application.h>
#include <NsApp/Window.h>

#include "BounceAnimation.h"
#include "ElasticAnimation.h"
#include "ExponentialAnimation.h"
#include "BackAnimation.h"
#include "CircleAnimation.h"

#include "App.xaml.bin.h"
#include "MainWindow.xaml.bin.h"
#include "Aero Matics Regular.ttf.bin.h"


using namespace Noesis;
using namespace NoesisApp;


namespace CustomAnimation
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class App final: public Application
{
    NS_IMPLEMENT_INLINE_REFLECTION_(App, Application, "CustomAnimation.App")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class MainWindow final: public Window
{
    NS_IMPLEMENT_INLINE_REFLECTION_(MainWindow, Window, "CustomAnimation.MainWindow")
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        RegisterComponent<CustomAnimation::App>();
        RegisterComponent<CustomAnimation::MainWindow>();
        RegisterComponent<CustomAnimation::BounceAnimation>();
        RegisterComponent<CustomAnimation::ElasticAnimation>();
        RegisterComponent<CustomAnimation::ExponentialAnimation>();
        RegisterComponent<CustomAnimation::BackAnimation>();
        RegisterComponent<CustomAnimation::CircleAnimation>();
        RegisterComponent<EnumConverter<CustomAnimation::BounceAnimation::EdgeBehaviorEnum>>();
        RegisterComponent<EnumConverter<CustomAnimation::ElasticAnimation::EdgeBehaviorEnum>>();
        RegisterComponent<EnumConverter<CustomAnimation::ExponentialAnimation::EdgeBehaviorEnum>>();
        RegisterComponent<EnumConverter<CustomAnimation::BackAnimation::EdgeBehaviorEnum>>();
        RegisterComponent<EnumConverter<CustomAnimation::CircleAnimation::DirectionEnum>>();
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
