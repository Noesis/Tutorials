////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __LOGIN_VIEWMODEL_H__
#define __LOGIN_VIEWMODEL_H__


#include <NsCore/Noesis.h>
#include <NsCore/Ptr.h>
#include <NsCore/String.h>
#include <NsGui/PasswordBox.h>
#include <NsApp/DelegateCommand.h>
#include <NsApp/NotifyPropertyChangedBase.h>


namespace Login
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class ViewModel final: public NoesisApp::NotifyPropertyChangedBase
{
public:
    ViewModel();

private:
    void SetAccountName(const char* value); 
    const char* GetAccountName() const;

    void SetMessage(const char* value); 
    const char* GetMessage() const;

    const NoesisApp::DelegateCommand* GetLoginCommand() const;

    void Login(BaseComponent* param);
    bool CheckCredentials(Noesis::PasswordBox* passwordBox);

private:
    char _accountName[256];
    char _message[256];
    NoesisApp::DelegateCommand _loginCommand;

    NS_DECLARE_REFLECTION(ViewModel, NotifyPropertyChangedBase)
};

}


#endif
