////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/RegisterComponent.h>
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
    NS_IMPLEMENT_INLINE_REFLECTION_(App, Application, "DataBinding.App")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class MainWindow final: public Window
{
    NS_IMPLEMENT_INLINE_REFLECTION_(MainWindow, Window, "DataBinding.MainWindow")
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
    String _name;
    float _orbit;
    float _diameter;
    String _details;
    Noesis::Ptr<ImageSource> _image;

private:
    NS_IMPLEMENT_INLINE_REFLECTION(SolarSystemObject, BaseComponent, "DataBinding.SolarSystemObject")
    {
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

        Noesis::Ptr<SolarSystemObject> sun = *new SolarSystemObject("Sun", 0, 1380000,
            "Images/sun.jpg",
            "The yellow dwarf star in the center of our solar system.");
        _solarSystemObjects->Add(sun);

        Noesis::Ptr<SolarSystemObject> mercury = *new SolarSystemObject("Mercury", 0.38f, 4880,
            "Images/merglobe.jpg",
            "The small and rocky planet Mercury is the closest planet to the Sun.");
        _solarSystemObjects->Add(mercury);

        Noesis::Ptr<SolarSystemObject> venus = *new SolarSystemObject("Venus", 0.72f, 12103.6f,
            "Images/venglobe.jpg",
            "At first glance, if Earth had a twin, it would be Venus.");
        _solarSystemObjects->Add(venus);

        Noesis::Ptr<SolarSystemObject> earth = *new SolarSystemObject("Earth", 1, 12756.3f,
            "Images/earglobe.jpg",
            "Earth, our home planet, is the only planet in our solar system known to harbor life.");
        _solarSystemObjects->Add(earth);

        Noesis::Ptr<SolarSystemObject> mars = *new SolarSystemObject("Mars", 1.52f, 6794,
            "Images/marglobe.jpg",
            "The red planet Mars has inspired wild flights of imagination over the centuries.");
        _solarSystemObjects->Add(mars);

        Noesis::Ptr<SolarSystemObject> jupiter = *new SolarSystemObject("Jupiter", 5.20f, 142984,
            "Images/jupglobe.jpg",
            "With its numerous moons and several rings, the Jupiter system is a \"mini-solar system.\"");
        _solarSystemObjects->Add(jupiter);

        Noesis::Ptr<SolarSystemObject> saturn = *new SolarSystemObject("Saturn", 9.54f, 120536,
            "Images/moons_2.jpg",
            "Saturn is the most distant of the five planets known to ancient stargazers.");
        _solarSystemObjects->Add(saturn);

        Noesis::Ptr<SolarSystemObject> uranus = *new SolarSystemObject("Uranus", 19.218f, 51118,
            "Images/uraglobe.jpg",
            "Uranus gets its blue-green color from methane gas above the deeper cloud layers.");
        _solarSystemObjects->Add(uranus);

        Noesis::Ptr<SolarSystemObject> neptune = *new SolarSystemObject("Neptune", 30.06f, 49532,
            "Images/nepglobe.jpg",
            "Neptune was the first planet located through mathematical predictions.");
        _solarSystemObjects->Add(neptune);

        Noesis::Ptr<SolarSystemObject> pluto = *new SolarSystemObject("Pluto", 39.5f, 2274,
            "Images/plutoch_2.jpg",
            "Long considered to be the smallest, coldest, and most distant planet from the Sun.");
        _solarSystemObjects->Add(pluto);
    }

private:
    Noesis::Ptr<ObservableCollection<SolarSystemObject>> _solarSystemObjects;

    NS_IMPLEMENT_INLINE_REFLECTION(SolarSystem, BaseComponent, "DataBinding.SolarSystem")
    {
        NsProp("SolarSystemObjects", &SolarSystem::_solarSystemObjects);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class OrbitConverter: public BaseValueConverter
{
public:
    bool TryConvert(BaseComponent* value, const Type* targetType, BaseComponent* parameter,
        Noesis::Ptr<BaseComponent>& result)
    {
        if (targetType == TypeOf<float>() && Boxing::CanUnbox<float>(value))
        {
            float orbit = Boxing::Unbox<float>(value);
            float factor = (float)atof(Boxing::Unbox<String>(parameter).Str());
            result = Boxing::Box(powf(orbit / 40, 0.4f) * 770.0f * factor);
            return true;
        }

        return false;
    }

private:
    NS_IMPLEMENT_INLINE_REFLECTION_(OrbitConverter, BaseValueConverter, "DataBinding.OrbitConverter")
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        RegisterComponent<DataBinding::App>();
        RegisterComponent<DataBinding::MainWindow>();
        RegisterComponent<DataBinding::SolarSystem>();
        RegisterComponent<DataBinding::OrbitConverter>();
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
            { "", Roboto_Regular_ttf },
            { "", Roboto_Bold_ttf }
        };

        return *new EmbeddedFontProvider(fonts);
    }

    Noesis::Ptr<TextureProvider> GetTextureProvider() const override
    {
        EmbeddedTexture textures[] = 
        {
            { "Images/sun.jpg", sun_jpg },
            { "Images/merglobe.jpg", merglobe_jpg },
            { "Images/venglobe.jpg", venglobe_jpg },
            { "Images/earglobe.jpg", earglobe_jpg },
            { "Images/marglobe.jpg", marglobe_jpg },
            { "Images/jupglobe.jpg", jupglobe_jpg },
            { "Images/moons_2.jpg", moons_2_jpg },
            { "Images/uraglobe.jpg", uraglobe_jpg },
            { "Images/nepglobe.jpg", nepglobe_jpg },
            { "Images/plutoch_2.jpg", plutoch_2_jpg }
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
