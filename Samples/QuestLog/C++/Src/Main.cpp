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

#include "ElementExtensions.h"
#include "MainWindow.xaml.h"
#include "App.xaml.h"
#include "ViewModel.h"

#include "App.xaml.bin.h"
#include "LogoResources.xaml.bin.h"
#include "MainWindow.xaml.bin.h"
#include "Aero Matics Regular.ttf.bin.h"
#include "Image0.png.bin.h"
#include "Image1.png.bin.h"
#include "Image2.png.bin.h"


using namespace QuestLog;
using namespace Noesis;
using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        NsRegisterComponent<QuestLog::ElementExtensions>();
        NsRegisterComponent<QuestLog::MainWindow>();
        NsRegisterComponent<QuestLog::App>();
        NsRegisterComponent<EnumConverter<QuestLog::QuestDifficulty>>();
    }

    Ptr<XamlProvider> GetXamlProvider() const override
    {
        EmbeddedXaml xamls[] = 
        {
            { "App.xaml", App_xaml, sizeof(App_xaml) },
            { "LogoResources.xaml", LogoResources_xaml, sizeof(LogoResources_xaml) },
            { "MainWindow.xaml", MainWindow_xaml, sizeof(MainWindow_xaml) }
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

    Ptr<TextureProvider> GetTextureProvider() const override
    {
        EmbeddedTexture textures[] = 
        {
            { "Images/Image0.png", Image0_png, sizeof(Image0_png) },
            { "Images/Image1.png", Image1_png, sizeof(Image1_png) },
            { "Images/Image2.png", Image2_png, sizeof(Image2_png) }
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
