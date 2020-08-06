////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "LocalizationGame.h"
#include "LevelToColorConverter.h"

DEFINE_LOG_CATEGORY(LogNoesisLocalization)

class LocalizationModule : public FDefaultGameModuleImpl
{
    virtual void StartupModule() override
    {
        Noesis::RegisterComponent<Localization::LevelToColorConverter>();
    }

    virtual void ShutdownModule() override
    {
        Noesis::UnregisterComponent<Localization::LevelToColorConverter>();
    }
};

IMPLEMENT_MODULE(LocalizationModule, LocalizationModule);
