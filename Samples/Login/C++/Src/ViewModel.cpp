////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "ViewModel.h"
#include "DelegateCommand.h"

#include <NsCore/ReflectionImplement.h>
#include <NsGui/PasswordBox.h>


using namespace Login;
using namespace Noesis;


////////////////////////////////////////////////////////////////////////////////////////////////////
ViewModel::ViewModel()
{
    _loginCommand = *new DelegateCommand(MakeDelegate(this, &ViewModel::Login));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::SetMessage(const char* value)
{
    if (_message != value)
    {
        _message = value;
        OnPropertyChanged("Message");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* ViewModel::GetMessage() const
{
    return _message.c_str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::SetNotifyMessage(bool value)
{
    if (_notifyMessage != value)
    {
        _notifyMessage = value;
        OnPropertyChanged("NotifyMessage");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool ViewModel::GetNotifyMessage() const
{
    return _notifyMessage;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
DelegateCommand* ViewModel::GetLoginCommand() const
{
    return _loginCommand;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::Login(BaseComponent* param)
{
    PasswordBox* passwordBox = NsDynamicCast<PasswordBox*>(param);
    if (CheckCredentials(passwordBox))
    {
        OnNotifyMessage("LOGIN SUCCESSFUL");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool ViewModel::CheckCredentials(PasswordBox* passwordBox)
{
    const char* password = passwordBox->GetPassword();

    if (_accountName.empty() && !String::IsNullOrEmpty(password))
    {
        OnNotifyMessage("ACCOUNT NAME CANNOT BE EMPTY");
        return false;
    }

    if (_accountName != "NoesisGUI" || !String::Equals(password, "noesis"))
    {
        OnNotifyMessage("ACCOUNT NAME OR PASSWORD IS INCORRECT");
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::OnNotifyMessage(const char* message)
{
    SetMessage(message);

    // Pulse the boolean to laucn the animation
    SetNotifyMessage(true);
    SetNotifyMessage(false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_IMPLEMENT_REFLECTION(ViewModel)
{
    NsProp("AccountName", &ViewModel::_accountName);
    NsProp("Message", &ViewModel::GetMessage, &ViewModel::SetMessage);
    NsProp("NotifyMessage", &ViewModel::GetNotifyMessage, &ViewModel::SetNotifyMessage);
    NsProp("LoginCommand", &ViewModel::GetLoginCommand);
}
