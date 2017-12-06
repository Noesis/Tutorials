////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ButtonsGame.h"
#include "ElementExtensions.h"
#include "MainWindow.h"

DEFINE_LOG_CATEGORY(LogNoesisButtons)

class ButtonsGameModule : public FDefaultGameModuleImpl
{
	virtual void StartupModule() override
	{
		NsRegisterComponent<Buttons::ElementExtensions>();
		NsRegisterComponent<Buttons::MainWindow>();
	}

	virtual void ShutdownModule() override
	{
		NsUnregisterComponent<Buttons::ElementExtensions>();
		NsUnregisterComponent<Buttons::MainWindow>();
	}
};

IMPLEMENT_PRIMARY_GAME_MODULE(ButtonsGameModule, Buttons, "Buttons" );
