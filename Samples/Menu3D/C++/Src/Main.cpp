////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/RegisterComponent.h>
#include <NsApp/ApplicationLauncher.h>
#include <NsApp/EmbeddedXamlProvider.h>
#include <NsApp/EmbeddedTextureProvider.h>
#include <NsApp/EmbeddedFontProvider.h>
#include <NsApp/EntryPoint.h>

#include "App.xaml.h"
#include "MainWindow.xaml.h"
#include "MenuDescription.xaml.h"
#include "MainMenu.xaml.h"
#include "StartMenu.xaml.h"
#include "SettingsMenu.xaml.h"
#include "OptionSelector.xaml.h"
#include "MultiplierConverter.h"

#include "App.xaml.bin.h"
#include "MenuResources.xaml.bin.h"
#include "MenuDescription.xaml.bin.h"
#include "MainWindow.xaml.bin.h"
#include "MainMenu.xaml.bin.h"
#include "SettingsMenu.xaml.bin.h"
#include "StartMenu.xaml.bin.h"
#include "OptionSelector.xaml.bin.h"
#include "BackClouds.png.bin.h"
#include "FrontClouds.png.bin.h"
#include "FrontTrees.png.bin.h"
#include "LakeAndMountains.png.bin.h"
#include "SkyAndSun.jpg.bin.h"
#include "weblysleekuisb.ttf.bin.h"
#include "weblysleekuisl.ttf.bin.h"
#include "SoundTrack.mp3.bin.h"
#include "WaterDropBig.mp3.bin.h"
#include "WaterDropSmall.mp3.bin.h"

#include <NsCore/EnumConverter.h>
#include "ViewModel.h"


using namespace Menu3D;
using namespace Noesis;
using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        RegisterComponent<Menu3D::App>();
        RegisterComponent<Menu3D::MainWindow>();
        RegisterComponent<Menu3D::MenuDescription>();
        RegisterComponent<Menu3D::MainMenu>();
        RegisterComponent<Menu3D::StartMenu>();
        RegisterComponent<Menu3D::SettingsMenu>();
        RegisterComponent<Menu3D::OptionSelector>();
        RegisterComponent<EnumConverter<Menu3D::State>>();
        RegisterComponent<MultiplierConverter>();
    }

    Noesis::Ptr<XamlProvider> GetXamlProvider() const override
    {
        EmbeddedXaml xamls[] = 
        {
            { "App.xaml", App_xaml },
            { "MenuResources.xaml", MenuResources_xaml },
            { "MainWindow.xaml", MainWindow_xaml },
            { "MenuDescription.xaml", MenuDescription_xaml },
            { "MainMenu.xaml", MainMenu_xaml },
            { "StartMenu.xaml", StartMenu_xaml },
            { "SettingsMenu.xaml", SettingsMenu_xaml },
            { "OptionSelector.xaml", OptionSelector_xaml },
            { "Sounds/SoundTrack.mp3", SoundTrack_mp3 },
            { "Sounds/WaterDropBig.mp3", WaterDropBig_mp3 },
            { "Sounds/WaterDropSmall.mp3", WaterDropSmall_mp3 }
        };

        return *new EmbeddedXamlProvider(xamls);
    }

    Noesis::Ptr<FontProvider> GetFontProvider() const override
    {
        EmbeddedFont fonts[] = 
        {
            { "Fonts", weblysleekuisb_ttf },
            { "Fonts", weblysleekuisl_ttf }
        };

        return *new EmbeddedFontProvider(fonts);
    }

    Noesis::Ptr<TextureProvider> GetTextureProvider() const override
    {
        EmbeddedTexture textures[] = 
        {
            { "Images/BackClouds.png", BackClouds_png },
            { "Images/FrontClouds.png", FrontClouds_png },
            { "Images/FrontTrees.png", FrontTrees_png },
            { "Images/LakeAndMountains.png", LakeAndMountains_png },
            { "Images/SkyAndSun.jpg", SkyAndSun_jpg }
        };

        return *new EmbeddedTextureProvider(textures);
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
