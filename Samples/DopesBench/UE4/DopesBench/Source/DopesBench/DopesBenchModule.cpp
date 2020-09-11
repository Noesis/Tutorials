// Copyright Epic Games, Inc. All Rights Reserved.

#include "DopesBenchModule.h"

#include "Modules/ModuleManager.h"

#include "NsCore/Package.h"

#include "MainWindow.h"

class DopesBenchModule: public FDefaultGameModuleImpl
{
    virtual void StartupModule() override
    {
        Noesis::RegisterComponent<DopesBench::MainWindow>();
    }

    virtual void ShutdownModule() override
    {
        Noesis::UnregisterComponent<DopesBench::MainWindow>();
    }
};

IMPLEMENT_PRIMARY_GAME_MODULE(DopesBenchModule, DopesBenchModule, "DopesBenchModule");
