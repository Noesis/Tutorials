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
#include "ElementExtensions.h"
#include "MainWindow.xaml.h"
#include "MainMenu.xaml.h"
#include "StartMenu.xaml.h"
#include "SettingsMenu.xaml.h"
#include "OptionSelector.xaml.h"

#include "App.xaml.bin.h"
#include "MenuResources.xaml.bin.h"
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
        NsRegisterComponent<Menu3D::App>();
        NsRegisterComponent<Menu3D::MainWindow>();
        NsRegisterComponent<Menu3D::ElementExtensions>();
        NsRegisterComponent<Menu3D::MainMenu>();
        NsRegisterComponent<Menu3D::StartMenu>();
        NsRegisterComponent<Menu3D::SettingsMenu>();
        NsRegisterComponent<Menu3D::OptionSelector>();
        NsRegisterComponent<EnumConverter<Menu3D::State>>();
    }

    Ptr<XamlProvider> GetXamlProvider() const override
    {
        EmbeddedXaml xamls[] = 
        {
            { "App.xaml", App_xaml, sizeof(App_xaml) },
            { "MenuResources.xaml", MenuResources_xaml, sizeof(MenuResources_xaml) },
            { "MainWindow.xaml", MainWindow_xaml, sizeof(MainWindow_xaml) },
            { "MainMenu.xaml", MainMenu_xaml, sizeof(MainMenu_xaml) },
            { "StartMenu.xaml", StartMenu_xaml, sizeof(StartMenu_xaml) },
            { "SettingsMenu.xaml", SettingsMenu_xaml, sizeof(SettingsMenu_xaml) },
            { "OptionSelector.xaml", OptionSelector_xaml, sizeof(OptionSelector_xaml) }
        };

        return *new EmbeddedXamlProvider(xamls, NS_COUNTOF(xamls));
    }

    Ptr<FontProvider> GetFontProvider() const override
    {
        EmbeddedFont fonts[] = 
        {
            { "Fonts", weblysleekuisb_ttf, sizeof(weblysleekuisb_ttf) },
            { "Fonts", weblysleekuisl_ttf, sizeof(weblysleekuisl_ttf) }
        };

        return *new EmbeddedFontProvider(fonts, NS_COUNTOF(fonts));
    }

    Ptr<TextureProvider> GetTextureProvider() const override
    {
        EmbeddedTexture textures[] = 
        {
            { "Images/BackClouds.png", BackClouds_png, sizeof(BackClouds_png) },
            { "Images/FrontClouds.png", FrontClouds_png, sizeof(FrontClouds_png) },
            { "Images/FrontTrees.png", FrontTrees_png, sizeof(FrontTrees_png) },
            { "Images/LakeAndMountains.png", LakeAndMountains_png, sizeof(LakeAndMountains_png) },
            { "Images/SkyAndSun.jpg", SkyAndSun_jpg, sizeof(SkyAndSun_jpg) }
        };

        return *new EmbeddedTextureProvider(textures, NS_COUNTOF(textures));
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
