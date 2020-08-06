////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Menu3DGame.h"
#include "OptionSelector.h"
#include "MainMenu.h"
#include "StartMenu.h"
#include "SettingsMenu.h"
#include "MenuDescription.h"
#include "MultiplierConverter.h"

DEFINE_LOG_CATEGORY(LogNoesisMenu3D)

Noesis::BaseComponent* ButtonCreator(Noesis::Symbol)
{
    return nullptr;
}

class Menu3DModule : public FDefaultGameModuleImpl
{
    virtual void StartupModule() override
    {
        Noesis::RegisterComponent<Menu3D::OptionSelector>();
        Noesis::RegisterComponent<Menu3D::MainMenu>();
        Noesis::RegisterComponent<Menu3D::StartMenu>();
        Noesis::RegisterComponent<Menu3D::SettingsMenu>();
        Noesis::RegisterComponent<Menu3D::MenuDescription>();
        Noesis::RegisterComponent<Menu3D::MultiplierConverter>();
    }

    virtual void ShutdownModule() override
    {
        Noesis::UnregisterComponent<Menu3D::OptionSelector>();
        Noesis::UnregisterComponent<Menu3D::MainMenu>();
        Noesis::UnregisterComponent<Menu3D::StartMenu>();
        Noesis::UnregisterComponent<Menu3D::SettingsMenu>();
        Noesis::UnregisterComponent<Menu3D::MenuDescription>();
        Noesis::UnregisterComponent<Menu3D::MultiplierConverter>();
    }
};

IMPLEMENT_MODULE(Menu3DModule, Menu3DModule);
