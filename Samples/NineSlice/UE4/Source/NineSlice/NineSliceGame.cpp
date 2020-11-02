////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "NineSliceGame.h"
#include "Modules/ModuleManager.h"

#include "NineSliceImage.h"

class NineSliceModule : public FDefaultGameModuleImpl
{
    virtual void StartupModule() override
    {
        Noesis::RegisterComponent<NineSlice::NineSliceImage>();
    }

    virtual void ShutdownModule() override
    {
        Noesis::UnregisterComponent<NineSlice::NineSliceImage>();
    }
};

IMPLEMENT_MODULE(NineSliceModule, NineSliceModule);
