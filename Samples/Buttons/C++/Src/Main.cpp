////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/RegisterComponent.h>
#include <NsApp/ApplicationLauncher.h>
#include <NsApp/EmbeddedXamlProvider.h>
#include <NsApp/EmbeddedFontProvider.h>
#include <NsApp/EntryPoint.h>

#include "MainWindow.xaml.h"
#include "App.xaml.h"

#include "App.xaml.bin.h"
#include "Resources.xaml.bin.h"
#include "MainWindow.xaml.bin.h"
#include "Aero Matics Regular.ttf.bin.h"
#include "AudioSlide.mp3.bin.h"
#include "AudioClick.mp3.bin.h"


using namespace Buttons;
using namespace Noesis;
using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        RegisterComponent<Buttons::MainWindow>();
        RegisterComponent<Buttons::App>();
    }

    Noesis::Ptr<XamlProvider> GetXamlProvider() const override
    {
        EmbeddedXaml xamls[] = 
        {
            { "App.xaml", App_xaml },
            { "Resources.xaml", Resources_xaml },
            { "MainWindow.xaml", MainWindow_xaml },
            { "AudioSlide.mp3", AudioSlide_mp3 },
            { "AudioClick.mp3", AudioClick_mp3 }
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
