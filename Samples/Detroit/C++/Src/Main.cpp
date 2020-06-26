////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/RegisterComponent.h>
#include <NsApp/ApplicationLauncher.h>
#include <NsApp/EmbeddedXamlProvider.h>
#include <NsApp/EmbeddedFontProvider.h>
#include <NsApp/EmbeddedTextureProvider.h>
#include <NsApp/EntryPoint.h>

#include "MainWindow.xaml.h"
#include "App.xaml.h"

#include "App.xaml.bin.h"
#include "MainWindow.xaml.bin.h"
#include "Larke Neue Regular.ttf.bin.h"
#include "Larke Neue Bold.ttf.bin.h"
#include "Larke Neue Thin.ttf.bin.h"
#include "HomeBg.jpg.bin.h"
#include "HomeBg2.jpg.bin.h"
#include "StartBg.jpg.bin.h"
#include "Logo.png.bin.h"
#include "Chapter1.jpg.bin.h"
#include "Chapter2.jpg.bin.h"
#include "Chapter3.jpg.bin.h"
#include "Chapter4.jpg.bin.h"
#include "Chapter5.jpg.bin.h"
#include "Chapter6.jpg.bin.h"


using namespace Detroit;
using namespace Noesis;
using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        RegisterComponent<Detroit::MainWindow>();
        RegisterComponent<Detroit::App>();
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
            { "Fonts", Larke_Neue_Regular_ttf },
            { "Fonts", Larke_Neue_Bold_ttf },
            { "Fonts", Larke_Neue_Thin_ttf }
        };

        return *new EmbeddedFontProvider(fonts);
    }

    Noesis::Ptr<TextureProvider> GetTextureProvider() const override
    {
        EmbeddedTexture textures[] =
        {
            { "Images/HomeBg.jpg", HomeBg_jpg },
            { "Images/HomeBg2.jpg", HomeBg2_jpg },
            { "Images/StartBg.jpg", StartBg_jpg },
            { "Images/Logo.png", Logo_png },
            { "Images/Chapter1.jpg", Chapter1_jpg },
            { "Images/Chapter2.jpg", Chapter2_jpg },
            { "Images/Chapter3.jpg", Chapter3_jpg },
            { "Images/Chapter4.jpg", Chapter4_jpg },
            { "Images/Chapter5.jpg", Chapter5_jpg },
            { "Images/Chapter6.jpg", Chapter6_jpg }
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
