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
#include <NsGui/IntegrationAPI.h>
#include <NsGui/BitmapImage.h>
#include <NsGui/ObservableCollection.h>

#include "RadialPanel.h"
#include "RadialItem.h"
#include "Arc.h"

#include "App.xaml.bin.h"
#include "MainWindow.xaml.bin.h"
#include "Click.mp3.bin.h"
#include "Reload.mp3.bin.h"
#include "Industry Demi.ttf.bin.h"
#include "background.jpg.bin.h"
#include "AK-47.png.bin.h"
#include "AK-47-Icon.png.bin.h"
#include "AUG.png.bin.h"
#include "AUG-Icon.png.bin.h"
#include "FAMAS.png.bin.h"
#include "FAMAS-Icon.png.bin.h"
#include "IDF-Defender.png.bin.h"
#include "IDF-Defender-Icon.png.bin.h"
#include "Krieg-552.png.bin.h"
#include "Krieg-552-Icon.png.bin.h"
#include "M4A1.png.bin.h"
#include "M4A1-Icon.png.bin.h"


using namespace Noesis;
using namespace NoesisApp;


namespace RadialMenu
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class Weapon final: public BaseComponent
{
public:
    Weapon(const char* name, int price, int firepower, int fireRate, int accuracy, int movementRate,
        int ammo, int capacity, const char* special, const char* origin,
        ImageSource* icon, ImageSource* image):
        _name(name), _price(price), _firepower(firepower), _fireRate(fireRate), _accuracy(accuracy),
        _movementRate(movementRate), _ammo(ammo), _capacity(capacity), _special(special),
        _origin(origin), _icon(icon), _image(image)
    {
    }

    const char* GetName() const { return _name.Str(); }
    int GetPrice() const { return _price; }
    int GetFirepower() const { return _firepower; }
    int GetFireRate() const { return _fireRate; }
    int GetAccuracy() const { return _accuracy; }
    int GetMovementRate() const { return _movementRate; }
    int GetAmmo() const { return _ammo; }
    int GetCapacity() const { return _capacity; }
    const char* GetSpecial() const { return _special.Str(); }
    const char* GetOrigin() const { return _origin.Str(); }
    ImageSource* GetIcon() const { return _icon; }
    ImageSource* GetImage() const { return _image; }

private:
    String _name;
    String _special;
    String _origin;
    int _price;
    int _firepower;
    int _fireRate;
    int _accuracy;
    int _movementRate;
    int _ammo;
    int _capacity;
    Ptr<ImageSource> _icon;
    Ptr<ImageSource> _image;

    NS_IMPLEMENT_INLINE_REFLECTION(Weapon, BaseComponent)
    {
        NsProp("Name", &Weapon::GetName);
        NsProp("Price", &Weapon::GetPrice);
        NsProp("Firepower", &Weapon::GetFirepower);
        NsProp("FireRate", &Weapon::GetFireRate);
        NsProp("Accuracy", &Weapon::GetAccuracy);
        NsProp("MovementRate", &Weapon::GetMovementRate);
        NsProp("Ammo", &Weapon::GetAmmo);
        NsProp("Capacity", &Weapon::GetCapacity);
        NsProp("Special", &Weapon::GetSpecial);
        NsProp("Origin", &Weapon::GetOrigin);
        NsProp("Icon", &Weapon::GetIcon);
        NsProp("Image", &Weapon::GetImage);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class ViewModel final: public BaseComponent
{
public:
    ViewModel(): _buyTimeLeft(45), _money(3250), _weapons(MakePtr<ObservableCollection<Weapon>>())
    {
        _weapons->Add(MakePtr<Weapon>(
            "IDF Defender",
            2000, 2, 7, 2, 7, 30, 90, "None", "Israel",
            GetImage("IDF-Defender-Icon"), GetImage("IDF-Defender")));
        _weapons->Add(MakePtr<Weapon>(
            "FAMAS",
            2250, 2, 8, 6, 7, 25, 90, "Burst-fire", "France",
            GetImage("FAMAS-Icon"), GetImage("FAMAS")));
        _weapons->Add(MakePtr<Weapon>(
            "AK-47",
            2500, 3, 6, 3, 7, 30, 90, "None", "Rusia",
            GetImage("AK-47-Icon"), GetImage("AK-47")));
        _weapons->Add(MakePtr<Weapon>(
            "M4A1",
            3100, 2, 7, 5, 8, 30, 90, "Silencer", "U.S.A.",
            GetImage("M4A1-Icon"), GetImage("M4A1")));
        _weapons->Add(MakePtr<Weapon>(
            "AUG",
            3300,
            2, 6, 5, 7, 30, 90, "Silencer", "Austria",
            GetImage("AUG-Icon"), GetImage("AUG")));
        _weapons->Add(MakePtr<Weapon>(
            "Krieg 552",
            3500, 3, 7, 5, 6, 30, 90, "Silencer", "Switzerland",
            GetImage("Krieg-552-Icon"), GetImage("Krieg-552")));
    }

    int GetBuyTimeLeft() const { return _buyTimeLeft; }
    int GetMoney() const { return _money; }
    ObservableCollection<Weapon>* GetWeapons() const { return _weapons; }

private:
    Ptr<ImageSource> GetImage(const char* name) const
    {
        return MakePtr<BitmapImage>(String(String::VarArgs(), "Images/Weapons/%s.png", name).Str());
    }

private:
    int _buyTimeLeft;
    int _money;
    Ptr<ObservableCollection<Weapon>> _weapons;

    NS_IMPLEMENT_INLINE_REFLECTION(ViewModel, BaseComponent)
    {
        NsProp("BuyTimeLeft", &ViewModel::GetBuyTimeLeft);
        NsProp("Money", &ViewModel::GetMoney);
        NsProp("Weapons", &ViewModel::GetWeapons);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class App final: public Application
{
    NS_IMPLEMENT_INLINE_REFLECTION_(App, Application, "RadialMenu.App")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class MainWindow final: public Window
{
public:
    MainWindow()
    {
        GUI::LoadComponent(this, "MainWindow.xaml");

        SetDataContext(MakePtr<ViewModel>());
    }

    NS_IMPLEMENT_INLINE_REFLECTION_(MainWindow, Window, "RadialMenu.MainWindow")
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        RegisterComponent<RadialMenu::App>();
        RegisterComponent<RadialMenu::MainWindow>();
        RegisterComponent<RadialMenu::RadialPanel>();
        RegisterComponent<RadialMenu::RadialItem>();
        RegisterComponent<RadialMenu::Arc>();
    }

    Ptr<XamlProvider> GetXamlProvider() const override
    {
        EmbeddedXaml xamls[] = 
        {
            { "App.xaml", App_xaml },
            { "MainWindow.xaml", MainWindow_xaml },
            { "Sounds/Click.mp3", Click_mp3 },
            { "Sounds/Reload.mp3", Reload_mp3 }
        };

        return *new EmbeddedXamlProvider(xamls);
    }

    Ptr<FontProvider> GetFontProvider() const override
    {
        EmbeddedFont fonts[] =
        {
            { "Fonts", Industry_Demi_ttf }
        };

        return *new EmbeddedFontProvider(fonts);
    }

    Ptr<TextureProvider> GetTextureProvider() const override
    {
        EmbeddedTexture textures[] =
        {
            { "Images/background.jpg", background_jpg },
            { "Images/Weapons/AK-47.png", AK_47_png },
            { "Images/Weapons/AK-47-Icon.png", AK_47_Icon_png },
            { "Images/Weapons/AUG.png", AUG_png },
            { "Images/Weapons/AUG-Icon.png", AUG_Icon_png },
            { "Images/Weapons/FAMAS.png", FAMAS_png },
            { "Images/Weapons/FAMAS-Icon.png", FAMAS_Icon_png },
            { "Images/Weapons/IDF-Defender.png", IDF_Defender_png },
            { "Images/Weapons/IDF-Defender-Icon.png", IDF_Defender_Icon_png },
            { "Images/Weapons/Krieg-552.png", Krieg_552_png },
            { "Images/Weapons/Krieg-552-Icon.png", Krieg_552_Icon_png },
            { "Images/Weapons/M4A1.png", M4A1_png },
            { "Images/Weapons/M4A1-Icon.png", M4A1_Icon_png }
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
