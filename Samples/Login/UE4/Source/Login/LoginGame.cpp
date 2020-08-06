////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "LoginGame.h"

DEFINE_LOG_CATEGORY(LogNoesisLogin)

class LoginModule : public FDefaultGameModuleImpl
{
    virtual void StartupModule() override
    {
    }

    virtual void ShutdownModule() override
    {
    }
};

IMPLEMENT_MODULE(LoginModule, LoginModule);
