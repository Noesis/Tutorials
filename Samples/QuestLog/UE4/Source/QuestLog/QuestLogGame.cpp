////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "QuestLogGame.h"
#include "ElementExtensions.h"
#include "MainWindow.h"

DEFINE_LOG_CATEGORY(LogNoesisQuestLog)

class QuestLogGameModule : public FDefaultGameModuleImpl
{
	virtual void StartupModule() override
	{
		NsRegisterComponent<QuestLog::ElementExtensions>();
		NsRegisterComponent<QuestLog::MainWindow>();
	}

	virtual void ShutdownModule() override
	{
		NsUnregisterComponent<QuestLog::ElementExtensions>();
		NsUnregisterComponent<QuestLog::MainWindow>();
	}
};

IMPLEMENT_PRIMARY_GAME_MODULE(QuestLogGameModule, QuestLog, "QuestLog" );
