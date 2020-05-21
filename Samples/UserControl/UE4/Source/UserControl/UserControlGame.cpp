////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "UserControlGame.h"
#include "MainWindow.h"
#include "NumericUpDown.h"

DEFINE_LOG_CATEGORY(LogNoesisUserControl)

class UserControlGameModule : public FDefaultGameModuleImpl
{
    virtual void StartupModule() override
    {
        Noesis::RegisterComponent<UserControl::MainWindow>();
        Noesis::RegisterComponent<UserControl::NumericUpDown>();
    }

    virtual void ShutdownModule() override
    {
        Noesis::UnregisterComponent<UserControl::MainWindow>();
        Noesis::UnregisterComponent<UserControl::NumericUpDown>();
    }
};

IMPLEMENT_PRIMARY_GAME_MODULE(UserControlGameModule, UserControl, "UserControl" );
