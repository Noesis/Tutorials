////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Menu3DGame.h"
#include "OptionSelector.h"
#include "MainMenu.h"
#include "StartMenu.h"
#include "SettingsMenu.h"
#include "MainWindow.h"
#include "MenuDescription.h"
#include "MultiplierConverter.h"

DEFINE_LOG_CATEGORY(LogNoesisMenu3D)

Noesis::BaseComponent* ButtonCreator(Noesis::Symbol)
{
    return nullptr;
}

class Menu3DGameModule : public FDefaultGameModuleImpl
{
    virtual void StartupModule() override
    {
        NsRegisterComponent<Menu3D::OptionSelector>();
        NsRegisterComponent<Menu3D::MainMenu>();
        NsRegisterComponent<Menu3D::StartMenu>();
        NsRegisterComponent<Menu3D::SettingsMenu>();
        NsRegisterComponent<Menu3D::MainWindow>();
        NsRegisterComponent<Menu3D::MenuDescription>();
        NsRegisterComponent<Menu3D::MultiplierConverter>();
    }

    virtual void ShutdownModule() override
    {
        NsUnregisterComponent<Menu3D::OptionSelector>();
        NsUnregisterComponent<Menu3D::MainMenu>();
        NsUnregisterComponent<Menu3D::StartMenu>();
        NsUnregisterComponent<Menu3D::SettingsMenu>();
        NsUnregisterComponent<Menu3D::MainWindow>();
        NsUnregisterComponent<Menu3D::MenuDescription>();
        NsUnregisterComponent<Menu3D::MultiplierConverter>();
    }
};

IMPLEMENT_PRIMARY_GAME_MODULE(Menu3DGameModule, Menu3D, "Menu3D" );
