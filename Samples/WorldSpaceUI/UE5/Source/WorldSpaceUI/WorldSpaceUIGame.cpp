// Copyright Epic Games, Inc. All Rights Reserved.

#include "WorldSpaceUIGame.h"
#include "Modules/ModuleManager.h"

#include "PercentageConverter.h"
#include "NsCore/Package.h"

class WorldSpaceUIModule: public FDefaultGameModuleImpl
{
    virtual void StartupModule() override
    {
        Noesis::RegisterComponent<WorldSpaceUI::PercentageConverter>();
    }

    virtual void ShutdownModule() override
    {
        Noesis::UnregisterComponent<WorldSpaceUI::PercentageConverter>();
    }
};

IMPLEMENT_PRIMARY_GAME_MODULE(WorldSpaceUIModule, WorldSpaceUIModule, "WorldSpaceUI");