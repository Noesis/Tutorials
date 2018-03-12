////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "HelloWorldGame.h"
#include "MainWindow.h"

DEFINE_LOG_CATEGORY(LogNoesisHelloWorld)

class HelloWorldGameModule : public FDefaultGameModuleImpl
{
	virtual void StartupModule() override
	{
		NsRegisterComponent<HelloWorld::MainWindow>();
	}

	virtual void ShutdownModule() override
	{
		NsUnregisterComponent<HelloWorld::MainWindow>();
	}
};

IMPLEMENT_PRIMARY_GAME_MODULE(HelloWorldGameModule, HelloWorld, "HelloWorld" );
