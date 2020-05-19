////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionImplementEmpty.h>
#include <NsCore/RegisterComponent.h>
#include <NsGui/BaseValueConverter.h>
#include <NsDrawing/Color.h>
#include <NsApp/ApplicationLauncher.h>
#include <NsApp/EmbeddedXamlProvider.h>
#include <NsApp/EmbeddedFontProvider.h>
#include <NsApp/EmbeddedTextureProvider.h>
#include <NsApp/EntryPoint.h>

#include "MainWindow.xaml.h"
#include "App.xaml.h"

#include "App.xaml.bin.h"
#include "MainWindow.xaml.bin.h"
#include "Resources.xaml.bin.h"
#include "Language-en.xaml.bin.h"
#include "Language-fr.xaml.bin.h"
#include "Language-jp.xaml.bin.h"
#include "Flag-en.png.bin.h"
#include "Flag-fr.png.bin.h"
#include "Flag-jp.png.bin.h"
#include "Oxygen-Regular.ttf.bin.h"
#include "FontopoNIHONGO.otf.bin.h"


using namespace Localization;
using namespace Noesis;
using namespace NoesisApp;


namespace Localization
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class LevelToColorConverter: public BaseValueConverter
{
public:
    bool TryConvert(BaseComponent* value, const Type* targetType, BaseComponent*,
        Noesis::Ptr<BaseComponent>& result)
    {
        if (targetType == TypeOf<Color>() && Boxing::CanUnbox<float>(value))
        {
            float level = Boxing::Unbox<float>(value);
            float perc = level / 100.0f;
            int red = (int)(255 * Min(1.0f, 0.4f + 1.0f - perc));
            int green = (int)(255 * Min(1.0f, 0.4f + perc));
            result = Boxing::Box(Color(red, green, 0));
            return true;
        }

        return false;
    }

private:
    NS_IMPLEMENT_INLINE_REFLECTION_(LevelToColorConverter, BaseValueConverter, "Localization.LevelToColorConverter")
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        RegisterComponent<Localization::LevelToColorConverter>();
        RegisterComponent<Localization::MainWindow>();
        RegisterComponent<Localization::App>();
    }

    Noesis::Ptr<XamlProvider> GetXamlProvider() const override
    {
        EmbeddedXaml xamls[] = 
        {
            { "App.xaml", App_xaml },
            { "MainWindow.xaml", MainWindow_xaml },
            { "Resources.xaml", Resources_xaml },
            { "Language-en.xaml", Language_en_xaml },
            { "Language-fr.xaml", Language_fr_xaml },
            { "Language-jp.xaml", Language_jp_xaml }
        };

        return *new EmbeddedXamlProvider(xamls);
    }

    Noesis::Ptr<TextureProvider> GetTextureProvider() const override
    {
        EmbeddedTexture textures[] =
        {
            { "Flag-en.png", Flag_en_png },
            { "Flag-fr.png", Flag_fr_png },
            { "Flag-jp.png", Flag_jp_png }
        };

        return *new EmbeddedTextureProvider(textures);
    }

    Noesis::Ptr<FontProvider> GetFontProvider() const override
    {
        EmbeddedFont fonts[] = 
        {
            { "", FontopoNIHONGO_otf },
            { "", Oxygen_Regular_ttf }
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
