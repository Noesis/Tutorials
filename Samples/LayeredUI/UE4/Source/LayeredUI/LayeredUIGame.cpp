////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "LayeredUIGame.h"

#include <NsGui/UserControl.h>
#include <NsGui/IntegrationAPI.h>
#include <NsCore/ReflectionImplement.h>

DEFINE_LOG_CATEGORY(LogNoesisLayeredUI)

////////////////////////////////////////////////////////////////////////////////////////////////////
class MainPage : public Noesis::UserControl
{
public:
    MainPage()
    {
        Noesis::GUI::LoadComponent(this, "LayeredUI/MainPage.xaml");
    }

    NS_IMPLEMENT_INLINE_REFLECTION_(MainPage, UserControl, "LayeredUI.MainPage")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class HUDView : public Noesis::UserControl
{
public:
    HUDView()
    {
        Noesis::GUI::LoadComponent(this, "LayeredUI/HUDView.xaml");
    }

    NS_IMPLEMENT_INLINE_REFLECTION_(HUDView, UserControl, "LayeredUI.HUDView")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class MenuView : public Noesis::UserControl
{
public:
    MenuView()
    {
        Noesis::GUI::LoadComponent(this, "LayeredUI/MenuView.xaml");
    }

    NS_IMPLEMENT_INLINE_REFLECTION_(MenuView, UserControl, "LayeredUI.MenuView")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class LayeredUI : public FDefaultGameModuleImpl
{
    virtual void StartupModule() override
    {
        Noesis::RegisterComponent<MainPage>();
        Noesis::RegisterComponent<HUDView>();
        Noesis::RegisterComponent<MenuView>();
    }

    virtual void ShutdownModule() override
    {
        Noesis::UnregisterComponent<MainPage>();
        Noesis::UnregisterComponent<HUDView>();
        Noesis::UnregisterComponent<MenuView>();
    }
};

IMPLEMENT_MODULE(LayeredUI, LayeredUI);
