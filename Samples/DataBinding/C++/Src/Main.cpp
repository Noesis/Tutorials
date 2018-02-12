////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/RegisterComponent.h>
#include <NsCore/TypeId.h>
#include <NsApp/EmbeddedXamlProvider.h>
#include <NsApp/EmbeddedFontProvider.h>
#include <NsApp/EmbeddedTextureProvider.h>
#include <NsApp/ApplicationLauncher.h>
#include <NsApp/EntryPoint.h>
#include <NsApp/Application.h>
#include <NsApp/Window.h>

#include <NsGui/BitmapImage.h>
#include <NsGui/ObservableCollection.h>
#include <NsGui/BaseValueConverter.h>
#include <NsCore/TypeOf.h>

#include "App.xaml.bin.h"
#include "MainWindow.xaml.bin.h"
#include "Roboto-Regular.ttf.bin.h"
#include "Roboto-Bold.ttf.bin.h"
#include "moons_2.jpg.bin.h"
#include "earglobe.jpg.bin.h"
#include "jupglobe.jpg.bin.h"
#include "marglobe.jpg.bin.h"
#include "merglobe.jpg.bin.h"
#include "nepglobe.jpg.bin.h"
#include "plutoch_2.jpg.bin.h"
#include "sun.jpg.bin.h"
#include "uraglobe.jpg.bin.h"
#include "venglobe.jpg.bin.h"


using namespace Noesis;
using namespace NoesisApp;


namespace DataBinding
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class App final: public Application
{
    NS_IMPLEMENT_INLINE_REFLECTION(App, Application)
    {
        NsMeta<TypeId>("DataBinding.App");
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class MainWindow final: public Window
{
    NS_IMPLEMENT_INLINE_REFLECTION(MainWindow, Window)
    {
        NsMeta<TypeId>("DataBinding.MainWindow");
    }
};

NS_WARNING_PUSH
NS_CLANG_WARNING_DISABLE("-Wunused-private-field")

////////////////////////////////////////////////////////////////////////////////////////////////////
class SolarSystemObject: public BaseComponent
{
public:
    SolarSystemObject(const char* name, float orbit, float diameter, const char* image,
        const char* details): _name(name), _orbit(orbit), _diameter(diameter), _details(details),
        _image(*new BitmapImage(image))
    {
    }

private:
    NsString _name;
    float _orbit;
    float _diameter;
    NsString _details;
    Ptr<ImageSource> _image;

private:
    NS_IMPLEMENT_INLINE_REFLECTION(SolarSystemObject, BaseComponent)
    {
        NsMeta<TypeId>("DataBinding.SolarSystemObject");
        NsProp("Name", &SolarSystemObject::_name);
        NsProp("Orbit", &SolarSystemObject::_orbit);
        NsProp("Diameter", &SolarSystemObject::_diameter);
        NsProp("Details", &SolarSystemObject::_details);
        NsProp("Image", &SolarSystemObject::_image);
    }
};

NS_WARNING_POP

////////////////////////////////////////////////////////////////////////////////////////////////////
class SolarSystem: public BaseComponent
{
public:
    SolarSystem()
    {
        _solarSystemObjects = *new ObservableCollection<SolarSystemObject>;

        Ptr<SolarSystemObject> sun = *new SolarSystemObject("Sun", 0, 1380000,
            "Images/sun.jpg",
            "The yellow dwarf star in the center of our solar system.");
        _solarSystemObjects->Add(sun);

        Ptr<SolarSystemObject> mercury = *new SolarSystemObject("Mercury", 0.38f, 4880,
            "Images/merglobe.jpg",
            "The small and rocky planet Mercury is the closest planet to the Sun.");
        _solarSystemObjects->Add(mercury);

        Ptr<SolarSystemObject> venus = *new SolarSystemObject("Venus", 0.72f, 12103.6f,
            "Images/venglobe.jpg",
            "At first glance, if Earth had a twin, it would be Venus.");
        _solarSystemObjects->Add(venus);

        Ptr<SolarSystemObject> earth = *new SolarSystemObject("Earth", 1, 12756.3f,
            "Images/earglobe.jpg",
            "Earth, our home planet, is the only planet in our solar system known to harbor life.");
        _solarSystemObjects->Add(earth);

        Ptr<SolarSystemObject> mars = *new SolarSystemObject("Mars", 1.52f, 6794,
            "Images/marglobe.jpg",
            "The red planet Mars has inspired wild flights of imagination over the centuries.");
        _solarSystemObjects->Add(mars);

        Ptr<SolarSystemObject> jupiter = *new SolarSystemObject("Jupiter", 5.20f, 142984,
            "Images/jupglobe.jpg",
            "With its numerous moons and several rings, the Jupiter system is a \"mini-solar system.\"");
        _solarSystemObjects->Add(jupiter);

        Ptr<SolarSystemObject> saturn = *new SolarSystemObject("Saturn", 9.54f, 120536,
            "Images/moons_2.jpg",
            "Saturn is the most distant of the five planets known to ancient stargazers.");
        _solarSystemObjects->Add(saturn);

        Ptr<SolarSystemObject> uranus = *new SolarSystemObject("Uranus", 19.218f, 51118,
            "Images/uraglobe.jpg",
            "Uranus gets its blue-green color from methane gas above the deeper cloud layers.");
        _solarSystemObjects->Add(uranus);

        Ptr<SolarSystemObject> neptune = *new SolarSystemObject("Neptune", 30.06f, 49532,
            "Images/nepglobe.jpg",
            "Neptune was the first planet located through mathematical predictions.");
        _solarSystemObjects->Add(neptune);

        Ptr<SolarSystemObject> pluto = *new SolarSystemObject("Pluto", 39.5f, 2274,
            "Images/plutoch_2.jpg",
            "Long considered to be the smallest, coldest, and most distant planet from the Sun.");
        _solarSystemObjects->Add(pluto);
    }

private:
    Ptr<ObservableCollection<SolarSystemObject>> _solarSystemObjects;

    NS_IMPLEMENT_INLINE_REFLECTION(SolarSystem, BaseComponent)
    {
        NsMeta<TypeId>("DataBinding.SolarSystem");
        NsProp("SolarSystemObjects", &SolarSystem::_solarSystemObjects);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class ConvertOrbit: public BaseValueConverter
{
public:
    bool TryConvert(BaseComponent* value, const Type* targetType, BaseComponent* parameter,
        Ptr<BaseComponent>& result)
    {
        if (targetType == TypeOf<float>() && Boxing::CanUnbox<float>(value))
        {
            float orbit = Boxing::Unbox<float>(value);
            float factor = (float)atof(Boxing::Unbox<NsString>(parameter).c_str());
            result = Boxing::Box(powf(orbit / 40, 0.4f) * 770.0f * factor);
            return true;
        }

        return false;
    }

private:
    NS_IMPLEMENT_INLINE_REFLECTION(ConvertOrbit, BaseValueConverter)
    {
        NsMeta<TypeId>("DataBinding.ConvertOrbit");
    }
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        NsRegisterComponent<DataBinding::App>();
        NsRegisterComponent<DataBinding::MainWindow>();
        NsRegisterComponent<DataBinding::SolarSystem>();
        NsRegisterComponent<DataBinding::ConvertOrbit>();
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
            { "", Roboto_Regular_ttf, sizeof(Roboto_Regular_ttf) },
            { "", Roboto_Bold_ttf, sizeof(Roboto_Bold_ttf) }
        };

        return *new EmbeddedFontProvider(fonts, NS_COUNTOF(fonts));
    }

    Ptr<TextureProvider> GetTextureProvider() const override
    {
        EmbeddedTexture textures[] = 
        {
            { "Images/sun.jpg", sun_jpg, sizeof(sun_jpg) },
            { "Images/merglobe.jpg", merglobe_jpg, sizeof(merglobe_jpg) },
            { "Images/venglobe.jpg", venglobe_jpg, sizeof(venglobe_jpg) },
            { "Images/earglobe.jpg", earglobe_jpg, sizeof(earglobe_jpg) },
            { "Images/marglobe.jpg", marglobe_jpg, sizeof(marglobe_jpg) },
            { "Images/jupglobe.jpg", jupglobe_jpg, sizeof(jupglobe_jpg) },
            { "Images/moons_2.jpg", moons_2_jpg, sizeof(moons_2_jpg) },
            { "Images/uraglobe.jpg", uraglobe_jpg, sizeof(uraglobe_jpg) },
            { "Images/nepglobe.jpg", nepglobe_jpg, sizeof(nepglobe_jpg) },
            { "Images/plutoch_2.jpg", plutoch_2_jpg, sizeof(plutoch_2_jpg) }
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
