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

#include "NotifyPropertyChangedBase.h"


namespace Login
{

class DelegateCommand;

////////////////////////////////////////////////////////////////////////////////////////////////////
class ViewModel final: public NotifyPropertyChangedBase
{
public:
    ViewModel();

private:
    void SetMessage(const char* value); 
    const char* GetMessage() const;

    void SetNotifyMessage(bool value);
    bool GetNotifyMessage() const;

    DelegateCommand* GetLoginCommand() const;

    void Login(BaseComponent* param);
    bool CheckCredentials(Noesis::PasswordBox* passwordBox);
    void OnNotifyMessage(const char* message);

private:
    NsString _accountName;
    NsString _message;
    bool _notifyMessage;
    Noesis::Ptr<DelegateCommand> _loginCommand;

    NS_DECLARE_REFLECTION(ViewModel, NotifyPropertyChangedBase)
};

}


#endif
