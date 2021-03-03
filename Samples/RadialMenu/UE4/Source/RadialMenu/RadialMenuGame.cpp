////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "RadialMenuGame.h"
#include "Arc.h"
#include "RadialItem.h"
#include "RadialPanel.h"

DEFINE_LOG_CATEGORY(LogNoesisRadialMenu)

class RadialMenuModule : public FDefaultGameModuleImpl
{
    virtual void StartupModule() override
    {
        Noesis::RegisterComponent<RadialMenu::Arc>();
        Noesis::RegisterComponent<RadialMenu::RadialItem>();
        Noesis::RegisterComponent<RadialMenu::RadialPanel>();
    }

    virtual void ShutdownModule() override
    {
        Noesis::UnregisterComponent<RadialMenu::Arc>();
        Noesis::UnregisterComponent<RadialMenu::RadialItem>();
        Noesis::UnregisterComponent<RadialMenu::RadialPanel>();
    }
};

IMPLEMENT_MODULE(RadialMenuModule, RadialMenuModule);
