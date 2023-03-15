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
#include "ViewModel.h"

#include "App.xaml.bin.h"
#include "Resources.xaml.bin.h"
#include "MainWindow.xaml.bin.h"
#include "Dungeon.ttf.bin.h"
#include "GentiumBookBasic.ttf.bin.h"
#include "Background.png.bin.h"
#include "Image0.png.bin.h"
#include "Image1.png.bin.h"
#include "Image2.png.bin.h"
#include "WaterDropSmall.mp3.bin.h"


using namespace QuestLog;
using namespace Noesis;
using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        RegisterComponent<QuestLog::MainWindow>();
        RegisterComponent<QuestLog::App>();
        RegisterComponent<EnumConverter<QuestLog::QuestDifficulty>>();
    }

    Noesis::Ptr<XamlProvider> GetXamlProvider() const override
    {
        EmbeddedXaml xamls[] = 
        {
            { "App.xaml", App_xaml },
            { "Resources.xaml", Resources_xaml },
            { "MainWindow.xaml", MainWindow_xaml },
            { "Sounds/WaterDropSmall.mp3", WaterDropSmall_mp3 }
        };

        return *new EmbeddedXamlProvider(xamls);
    }

    Noesis::Ptr<FontProvider> GetFontProvider() const override
    {
        EmbeddedFont fonts[] = 
        {
            { "", Dungeon_ttf },
            { "", GentiumBookBasic_ttf }
        };

        return *new EmbeddedFontProvider(fonts);
    }

    Noesis::Ptr<TextureProvider> GetTextureProvider() const override
    {
        EmbeddedTexture textures[] = 
        {
            { "Images/Background.png", Background_png },
            { "Images/Image0.png", Image0_png },
            { "Images/Image1.png", Image1_png },
            { "Images/Image2.png", Image2_png }
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
