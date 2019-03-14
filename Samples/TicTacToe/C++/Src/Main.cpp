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
#include <NsApp/EntryPoint.h>

#include "App.xaml.h"
#include "MainWindow.xaml.h"
#include "ViewModel.h"

#include "App.xaml.bin.h"
#include "MainWindow.xaml.bin.h"
#include "Multicolore.otf.bin.h"
#include "NoughtEffect.mp3.bin.h"
#include "CrossEffect.mp3.bin.h"
#include "WinEffect.mp3.bin.h"
#include "TieEffect.mp3.bin.h"


using namespace TicTacToe;
using namespace Noesis;
using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        NsRegisterComponent<TicTacToe::MainWindow>();
        NsRegisterComponent<TicTacToe::App>();
        NsRegisterComponent<Noesis::EnumConverter<TicTacToe::State>>();
    }

    Ptr<XamlProvider> GetXamlProvider() const override
    {
        EmbeddedXaml xamls[] = 
        {
            { "App.xaml", App_xaml, sizeof(App_xaml) },
            { "MainWindow.xaml", MainWindow_xaml, sizeof(MainWindow_xaml) },
            { "Sounds/NoughtEffect.mp3", NoughtEffect_mp3, sizeof(NoughtEffect_mp3) },
            { "Sounds/CrossEffect.mp3", CrossEffect_mp3, sizeof(CrossEffect_mp3) },
            { "Sounds/WinEffect.mp3", WinEffect_mp3, sizeof(WinEffect_mp3) },
            { "Sounds/TieEffect.mp3", TieEffect_mp3, sizeof(TieEffect_mp3) }
        };

        return *new EmbeddedXamlProvider(xamls, NS_COUNTOF(xamls));
    }

    Ptr<FontProvider> GetFontProvider() const override
    {
        EmbeddedFont fonts[] = 
        {
            { "Fonts", Multicolore_otf, sizeof(Multicolore_otf) }
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
