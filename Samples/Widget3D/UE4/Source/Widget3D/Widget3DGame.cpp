////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Widget3DGame.h"
#include "ElementExtensions.h"
#include "MainWindow.h"

DEFINE_LOG_CATEGORY(LogNoesisWidget3D)

class Widget3DGameModule : public FDefaultGameModuleImpl
{
	virtual void StartupModule() override
	{
		NsRegisterComponent<Widget3D::ElementExtensions>();
		NsRegisterComponent<Widget3D::MainWindow>();
	}

	virtual void ShutdownModule() override
	{
		NsUnregisterComponent<Widget3D::ElementExtensions>();
		NsUnregisterComponent<Widget3D::MainWindow>();
	}
};

IMPLEMENT_PRIMARY_GAME_MODULE(Widget3DGameModule, Widget3D, "Widget3D" );
