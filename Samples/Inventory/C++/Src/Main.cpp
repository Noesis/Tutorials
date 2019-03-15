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
#include "AnimatedNumber.xaml.h"
#include "DragItemBehavior.h"
#include "DropItemBehavior.h"
#include "DragAdornerBehavior.h"

#include "App.xaml.bin.h"
#include "MainWindow.xaml.bin.h"
#include "Resources.xaml.bin.h"
#include "AnimatedNumber.xaml.bin.h"
#include "Gidole-Regular.ttf.bin.h"
#include "Sequel_Demo.ttf.bin.h"
#include "Background.jpg.bin.h"
#include "Character.png.bin.h"
#include "InventoryAtlas.png.bin.h"


using namespace Inventory;
using namespace Noesis;
using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        NsRegisterComponent<Inventory::App>();
        NsRegisterComponent<Inventory::MainWindow>();
        NsRegisterComponent<Inventory::AnimatedNumber>();
        NsRegisterComponent<Inventory::DragItemBehavior>();
        NsRegisterComponent<Inventory::DropItemBehavior>();
        NsRegisterComponent<Inventory::DragAdornerBehavior>();
    }

    Ptr<XamlProvider> GetXamlProvider() const override
    {
        EmbeddedXaml xamls[] = 
        {
            { "App.xaml", App_xaml, sizeof(App_xaml) },
            { "MainWindow.xaml", MainWindow_xaml, sizeof(MainWindow_xaml) },
            { "Resources.xaml", Resources_xaml, sizeof(Resources_xaml) },
            { "AnimatedNumber.xaml", AnimatedNumber_xaml, sizeof(AnimatedNumber_xaml) }
        };

        return *new EmbeddedXamlProvider(xamls, NS_COUNTOF(xamls));
    }

    Ptr<FontProvider> GetFontProvider() const override
    {
        EmbeddedFont fonts[] = 
        {
            { "Fonts", Gidole_Regular_ttf, sizeof(Gidole_Regular_ttf) },
            { "Fonts", Sequel_Demo_ttf, sizeof(Sequel_Demo_ttf) }
        };

        return *new EmbeddedFontProvider(fonts, NS_COUNTOF(fonts));
    }

    Ptr<TextureProvider> GetTextureProvider() const override
    {
        EmbeddedTexture textures[] = 
        {
            { "Images/Background.jpg", Background_jpg, sizeof(Background_jpg) },
            { "Images/Character.png", Character_png, sizeof(Character_png) },
            { "Images/InventoryAtlas.png", InventoryAtlas_png, sizeof(InventoryAtlas_png) }
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
