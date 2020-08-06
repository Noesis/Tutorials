////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "UserControlGame.h"
#include "NumericUpDown.h"
#include "ColorCOnverter.h"

DEFINE_LOG_CATEGORY(LogNoesisUserControl)

class UserControlModule : public FDefaultGameModuleImpl
{
    virtual void StartupModule() override
    {
        Noesis::RegisterComponent<UserControls::NumericUpDown>();
        Noesis::RegisterComponent<UserControls::ColorConverter>();
    }

    virtual void ShutdownModule() override
    {
        Noesis::UnregisterComponent<UserControls::NumericUpDown>();
        Noesis::UnregisterComponent<UserControls::ColorConverter>();
    }
};

IMPLEMENT_MODULE(UserControlModule, UserControlModule);
