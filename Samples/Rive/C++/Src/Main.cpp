////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionImplementEmpty.h>
#include <NsCore/RegisterComponent.h>
#include <NsApp/EmbeddedXamlProvider.h>
#include <NsApp/EmbeddedFontProvider.h>
#include <NsApp/ApplicationLauncher.h>
#include <NsApp/EntryPoint.h>
#include <NsApp/Application.h>
#include <NsApp/Window.h>

#include "App.xaml.bin.h"
#include "MainWindow.xaml.bin.h"
#include "Milky Boba.otf.bin.h"
#include "background.riv.bin.h"
#include "leaves-tl.riv.bin.h"
#include "leaves-tr.riv.bin.h"
#include "leaves-br.riv.bin.h"
#include "leaves-bl.riv.bin.h"
#include "logo.riv.bin.h"
#include "start.riv.bin.h"
#include "rewards.riv.bin.h"
#include "settings.riv.bin.h"


using namespace Noesis;
using namespace NoesisApp;


namespace Rive
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class App final: public Application
{
    NS_IMPLEMENT_INLINE_REFLECTION_(App, Application, "Rive.App")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class MainWindow final: public Window
{
    NS_IMPLEMENT_INLINE_REFLECTION_(MainWindow, Window, "Rive.MainWindow")
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        RegisterComponent<Rive::App>();
        RegisterComponent<Rive::MainWindow>();
    }

    Noesis::Ptr<XamlProvider> GetXamlProvider() const override
    {
        EmbeddedXaml xamls[] = 
        {
            { "App.xaml", App_xaml },
            { "MainWindow.xaml", MainWindow_xaml },
            { "background.riv", background_riv },
            { "leaves-tl.riv", leaves_tl_riv },
            { "leaves-tr.riv", leaves_tr_riv },
            { "leaves-br.riv", leaves_br_riv },
            { "leaves-bl.riv", leaves_bl_riv },
            { "logo.riv", logo_riv },
            { "start.riv", start_riv },
            { "rewards.riv", rewards_riv },
            { "settings.riv", settings_riv }
        };

        return *new EmbeddedXamlProvider(xamls);
    }

    Noesis::Ptr<FontProvider> GetFontProvider() const override
    {
        EmbeddedFont fonts[] =
        {
            { "", Milky_Boba_otf }
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
