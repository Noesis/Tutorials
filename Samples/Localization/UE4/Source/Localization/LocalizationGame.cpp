////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "LocalizationGame.h"
#include "MainWindow.h"
#include "LevelToColorConverter.h"

DEFINE_LOG_CATEGORY(LogNoesisLocalization)

class LocalizationGameModule : public FDefaultGameModuleImpl
{
    virtual void StartupModule() override
    {
        NsRegisterComponent<Localization::LevelToColorConverter>();
        NsRegisterComponent<Localization::MainWindow>();
    }

    virtual void ShutdownModule() override
    {
        NsUnregisterComponent<Localization::LevelToColorConverter>();
        NsUnregisterComponent<Localization::MainWindow>();
    }
};

IMPLEMENT_PRIMARY_GAME_MODULE(LocalizationGameModule, LocalizationGame, "LocalizationGame" );
