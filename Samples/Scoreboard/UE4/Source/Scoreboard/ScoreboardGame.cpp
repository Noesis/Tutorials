////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ScoreboardGame.h"
#include "MainWindow.h"
#include "ThousandConverter.h"

DEFINE_LOG_CATEGORY(LogNoesisScoreboard)

class ScoreboardGameModule : public FDefaultGameModuleImpl
{
	virtual void StartupModule() override
	{
		NsRegisterComponent<Scoreboard::MainWindow>();
		NsRegisterComponent<Scoreboard::ThousandConverter>();
	}

	virtual void ShutdownModule() override
	{
		NsUnregisterComponent<Scoreboard::MainWindow>();
		NsUnregisterComponent<Scoreboard::ThousandConverter>();
	}
};

IMPLEMENT_PRIMARY_GAME_MODULE(ScoreboardGameModule, Scoreboard, "Scoreboard" );
