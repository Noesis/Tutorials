////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "LoginGame.h"
#include "MainWindow.h"

DEFINE_LOG_CATEGORY(LogNoesisLogin)

class LoginGameModule : public FDefaultGameModuleImpl
{
    virtual void StartupModule() override
    {
        NsRegisterComponent<Login::MainWindow>();
    }

    virtual void ShutdownModule() override
    {
        NsUnregisterComponent<Login::MainWindow>();
    }
};

IMPLEMENT_PRIMARY_GAME_MODULE(LoginGameModule, Login, "Login" );
