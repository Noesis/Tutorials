////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionImplementEmpty.h>
#include <NsCore/RegisterComponent.h>
#include <NsCore/Boxing.h>
#include <NsApp/EntryPoint.h>
#include <NsApp/Application.h>
#include <NsApp/EmbeddedXamlProvider.h>
#include <NsApp/EmbeddedFontProvider.h>
#include <NsApp/EmbeddedTextureProvider.h>
#include <NsApp/ApplicationLauncher.h>
#include <NsApp/Window.h>
#include <NsGui/BaseValueConverter.h>

#include "NineSliceImage.h"

#include "App.xaml.bin.h"
#include "MainWindow.xaml.bin.h"
#include "Another.ttf.bin.h"
#include "Sign.png.bin.h"


using namespace Noesis;
using namespace NoesisApp;


namespace NineSlice
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class App final: public Application
{
    NS_IMPLEMENT_INLINE_REFLECTION_(App, Application, "NineSlice.App")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class MainWindow final: public Window
{
    NS_IMPLEMENT_INLINE_REFLECTION_(MainWindow, Window, "NineSlice.MainWindow")
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        RegisterComponent<NineSlice::App>();
        RegisterComponent<NineSlice::MainWindow>();
        RegisterComponent<NineSlice::NineSliceImage>();
    }

    Noesis::Ptr<XamlProvider> GetXamlProvider() const override
    {
        EmbeddedXaml xamls[] = 
        {
            { "App.xaml", App_xaml },
            { "MainWindow.xaml", MainWindow_xaml },
        };

        return *new EmbeddedXamlProvider(xamls);
    }

    Noesis::Ptr<FontProvider> GetFontProvider() const override
    {
        EmbeddedFont fonts[] =
        {
            { "", Another_ttf }
        };

        return *new EmbeddedFontProvider(fonts);
    }

    Noesis::Ptr<TextureProvider> GetTextureProvider() const override
    {
        EmbeddedTexture textures[] =
        {
            { "Sign.png", Sign_png }
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
