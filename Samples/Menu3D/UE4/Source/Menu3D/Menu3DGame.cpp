////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Menu3DGame.h"
#include "ElementExtensions.h"
#include "OptionSelector.h"
#include "MainMenu.h"
#include "StartMenu.h"
#include "SettingsMenu.h"
#include "MainWindow.h"

DEFINE_LOG_CATEGORY(LogNoesisMenu3D)

Noesis::BaseComponent* ButtonCreator(Noesis::Symbol)
{
	return nullptr;
}

class Menu3DGameModule : public FDefaultGameModuleImpl
{
	virtual void StartupModule() override
	{
		NsRegisterComponent<Menu3D::ElementExtensions>();
		NsRegisterComponent<Menu3D::OptionSelector>();
		NsRegisterComponent<Menu3D::MainMenu>();
		NsRegisterComponent<Menu3D::StartMenu>();
		NsRegisterComponent<Menu3D::SettingsMenu>();
		NsRegisterComponent<Menu3D::MainWindow>();
	}

	virtual void ShutdownModule() override
	{
		NsUnregisterComponent<Menu3D::ElementExtensions>();
		NsUnregisterComponent<Menu3D::OptionSelector>();
		NsUnregisterComponent<Menu3D::MainMenu>();
		NsUnregisterComponent<Menu3D::StartMenu>();
		NsUnregisterComponent<Menu3D::SettingsMenu>();
		NsUnregisterComponent<Menu3D::MainWindow>();
	}
};

IMPLEMENT_PRIMARY_GAME_MODULE(Menu3DGameModule, Menu3D, "Menu3D" );
