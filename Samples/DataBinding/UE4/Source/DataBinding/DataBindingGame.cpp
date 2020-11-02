////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "DataBindingGame.h"
#include "Modules/ModuleManager.h"

#include "OrbitConverter.h"

class DataBindingModule : public FDefaultGameModuleImpl
{
    virtual void StartupModule() override
    {
        Noesis::RegisterComponent<DataBinding::OrbitConverter>();
    }

    virtual void ShutdownModule() override
    {
        Noesis::UnregisterComponent<DataBinding::OrbitConverter>();
    }
};

IMPLEMENT_MODULE(DataBindingModule, DataBindingModule);
