////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "ViewModel.h"

#include <NsCore/ReflectionImplement.h>
#include <NsGui/PasswordBox.h>


using namespace Login;
using namespace Noesis;
using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
ViewModel::ViewModel()
{
    String::Copy(_accountName, sizeof(_accountName), "");
    String::Copy(_message, sizeof(_message), "");
    _loginCommand.SetExecuteFunc(MakeDelegate(this, &ViewModel::Login));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::SetAccountName(const char* value)
{
    if (!String::Equals(_accountName, value))
    {
        String::Copy(_accountName, sizeof(_accountName), value);
        OnPropertyChanged("AccountName");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* ViewModel::GetAccountName() const
{
    return _accountName;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::SetMessage(const char* value)
{
    if (!String::Equals(_message, value))
    {
        String::Copy(_message, sizeof(_message), value);
        OnPropertyChanged("Message");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* ViewModel::GetMessage() const
{
    return _message;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const DelegateCommand* ViewModel::GetLoginCommand() const
{
    return &_loginCommand;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::Login(BaseComponent* param)
{
    if (CheckCredentials(static_cast<PasswordBox*>(param)))
    {
        SetMessage("LOGIN SUCCESSFUL");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool ViewModel::CheckCredentials(PasswordBox* passwordBox)
{
    const char* password = passwordBox->GetPassword();

    if (String::IsNullOrEmpty(_accountName) && !String::IsNullOrEmpty(password))
    {
        SetMessage("ACCOUNT NAME CANNOT BE EMPTY");
        return false;
    }

    if (!String::Equals(_accountName,"noesis") || !String::Equals(password, "12345"))
    {
        SetMessage("ACCOUNT NAME OR PASSWORD IS INCORRECT");
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(ViewModel)
{
    NsProp("AccountName", &ViewModel::GetAccountName, &ViewModel::SetAccountName);
    NsProp("Message", &ViewModel::GetMessage, &ViewModel::SetMessage);
    NsProp("LoginCommand", &ViewModel::GetLoginCommand);
}
