////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/RegisterComponent.h>
#include <NsCore/ReflectionImplementEmpty.h>
#include <NsApp/ApplicationLauncher.h>
#include <NsApp/EmbeddedXamlProvider.h>
#include <NsApp/EmbeddedTextureProvider.h>
#include <NsApp/EntryPoint.h>
#include <NsApp/Application.h>
#include <NsApp/Window.h>
#include <NsApp/DelegateCommand.h>
#include <NsApp/NotifyPropertyChangedBase.h>
#include <NsGui/IntegrationAPI.h>
#include <NsGui/UserControl.h>

#include "App.xaml.bin.h"
#include "MainPage.xaml.bin.h"
#include "HUDView.xaml.bin.h"
#include "MenuView.xaml.bin.h"
#include "bg.png.bin.h"


using namespace Noesis;
using namespace NoesisApp;


namespace LayeredUI
{
////////////////////////////////////////////////////////////////////////////////////////////////////
class HUDViewModel: public BaseComponent
{
    NS_IMPLEMENT_INLINE_REFLECTION_(HUDViewModel, BaseComponent, "LayeredUI.HUDViewModel")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class MenuViewModel: public BaseComponent
{
    NS_IMPLEMENT_INLINE_REFLECTION_(MenuViewModel, BaseComponent, "LayeredUI.MenuViewModel")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class MainViewModel: public NotifyPropertyChangedBase
{
public:
    MainViewModel()
    {
        mHUD = MakePtr<HUDViewModel>();
        mToggleMenu = MakePtr<DelegateCommand>(MakeDelegate(this, &MainViewModel::OnToggleMenu));
    }

    HUDViewModel* GetHUD() const { return mHUD; }
    MenuViewModel* GetMenu() const { return mMenu; }
    DelegateCommand* GetToggleMenu() const { return mToggleMenu; }

private:
    void OnToggleMenu(BaseComponent*)
    {
        mMenu = mMenu == nullptr ? MakePtr<MenuViewModel>() : nullptr;
        OnPropertyChanged("Menu");
    }

private:
    Ptr<HUDViewModel> mHUD;
    Ptr<MenuViewModel> mMenu;
    Ptr<DelegateCommand> mToggleMenu;

    NS_IMPLEMENT_INLINE_REFLECTION(MainViewModel, NotifyPropertyChangedBase)
    {
        NsProp("HUD", &MainViewModel::GetHUD);
        NsProp("Menu", &MainViewModel::GetMenu);
        NsProp("ToggleMenu", &MainViewModel::GetToggleMenu);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class App final: public Application
{
    NS_IMPLEMENT_INLINE_REFLECTION_(App, Application, "LayeredUI.App")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class MainPage final: public Window
{
public:
    MainPage()
    {
        InitializeComponent();

        SetDataContext(MakePtr<MainViewModel>());
    }

private:
    void InitializeComponent()
    {
        GUI::LoadComponent(this, "MainPage.xaml");
    }

    NS_IMPLEMENT_INLINE_REFLECTION_(MainPage, Window, "LayeredUI.MainPage")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class HUDView final: public UserControl
{
public:
    HUDView()
    {
        InitializeComponent();
    }

private:
    void InitializeComponent()
    {
        GUI::LoadComponent(this, "HUDView.xaml");
    }

    NS_IMPLEMENT_INLINE_REFLECTION_(HUDView, UserControl, "LayeredUI.HUDView")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class MenuView final: public UserControl
{
public:
    MenuView()
    {
        InitializeComponent();
    }

private:
    void InitializeComponent()
    {
        GUI::LoadComponent(this, "MenuView.xaml");
    }

    NS_IMPLEMENT_INLINE_REFLECTION_(MenuView, UserControl, "LayeredUI.MenuView")
};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        TypeOf<LayeredUI::HUDViewModel>();
        TypeOf<LayeredUI::MenuViewModel>();

        RegisterComponent<LayeredUI::App>();
        RegisterComponent<LayeredUI::MainPage>();
        RegisterComponent<LayeredUI::HUDView>();
        RegisterComponent<LayeredUI::MenuView>();
    }

    Noesis::Ptr<XamlProvider> GetXamlProvider() const override
    {
        EmbeddedXaml xamls[] = 
        {
            { "App.xaml", App_xaml },
            { "MainPage.xaml", MainPage_xaml },
            { "HUDView.xaml", HUDView_xaml },
            { "MenuView.xaml", MenuView_xaml }
        };

        return *new EmbeddedXamlProvider(xamls);
    }

    Noesis::Ptr<TextureProvider> GetTextureProvider() const override
    {
        EmbeddedTexture textures[] = 
        {
            { "bg.png", bg_png }
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
