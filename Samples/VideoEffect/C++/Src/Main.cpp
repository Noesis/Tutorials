////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/RegisterComponent.h>
#include <NsApp/ApplicationLauncher.h>
#include <NsApp/EmbeddedXamlProvider.h>
#include <NsApp/EntryPoint.h>
#include <NsApp/Application.h>
#include <NsApp/Window.h>

#include "ChromaticAberrationEffect.h"

#include "App.xaml.bin.h"
#include "MainWindow.xaml.bin.h"
#include "Particles.mp4.bin.h"


using namespace Noesis;
using namespace NoesisApp;


namespace VideoEffect
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class App final: public NoesisApp::Application
{
    NS_IMPLEMENT_INLINE_REFLECTION_(App, Application, "VideoEffect.App")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class MainWindow final: public NoesisApp::Window
{
    NS_IMPLEMENT_INLINE_REFLECTION_(MainWindow, Window, "VideoEffect.MainWindow")
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        RegisterComponent<VideoEffect::ChromaticAberrationEffect>();
        RegisterComponent<VideoEffect::MainWindow>();
        RegisterComponent<VideoEffect::App>();
    }

    Noesis::Ptr<XamlProvider> GetXamlProvider() const override
    {
        EmbeddedXaml xamls[] = 
        {
            { "App.xaml", App_xaml },
            { "MainWindow.xaml", MainWindow_xaml },
            { "Particles.mp4", Particles_mp4 }
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
