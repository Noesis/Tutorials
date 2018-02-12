////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/RegisterComponent.h>
#include <NsCore/EnumConverter.h>
#include <NsApp/ApplicationLauncher.h>
#include <NsApp/EmbeddedXamlProvider.h>
#include <NsApp/EmbeddedFontProvider.h>
#include <NsApp/EmbeddedTextureProvider.h>
#include <NsApp/EntryPoint.h>

#include "MainWindow.xaml.h"
#include "App.xaml.h"
#include "ThousandConverter.h"
#include "Player.h"

#include "App.xaml.bin.h"
#include "MainWindow.xaml.bin.h"
#include "Cheboyga.ttf.bin.h"
#include "PERRYGOT.TTF.bin.h"


using namespace Scoreboard;
using namespace Noesis;
using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        NsRegisterComponent<Scoreboard::MainWindow>();
        NsRegisterComponent<Scoreboard::App>();
        NsRegisterComponent<Scoreboard::ThousandConverter>();
        NsRegisterComponent<EnumConverter<Scoreboard::Team>>();
        NsRegisterComponent<EnumConverter<Scoreboard::Class>>();
    }

    Ptr<XamlProvider> GetXamlProvider() const override
    {
        EmbeddedXaml xamls[] = 
        {
            { "App.xaml", App_xaml, sizeof(App_xaml) },
            { "MainWindow.xaml", MainWindow_xaml, sizeof(MainWindow_xaml) }
        };

        return *new EmbeddedXamlProvider(xamls, NS_COUNTOF(xamls));
    }

    Ptr<FontProvider> GetFontProvider() const override
    {
        EmbeddedFont fonts[] = 
        {
            { "Fonts", Cheboyga_ttf, sizeof(Cheboyga_ttf) },
            { "Fonts", PERRYGOT_TTF, sizeof(PERRYGOT_TTF) }
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
