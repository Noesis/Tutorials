////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __BUTTONS_VIEWMODEL_H__
#define __BUTTONS_VIEWMODEL_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/Ptr.h>


namespace Buttons
{

class DelegateCommand;

////////////////////////////////////////////////////////////////////////////////////////////////////
class ViewModel final: public Noesis::BaseComponent
{
public:
    ViewModel();

private:
    DelegateCommand* GetStartCommand() const;
    DelegateCommand* GetSettingsCommand() const;
    DelegateCommand* GetExitCommand() const;

    void Start(BaseComponent* param);
    void Settings(BaseComponent* param);
    void Exit(BaseComponent* param);

private:
    Noesis::Ptr<DelegateCommand> _startCommand;
    Noesis::Ptr<DelegateCommand> _settingsCommand;
    Noesis::Ptr<DelegateCommand> _exitCommand;

    NS_DECLARE_REFLECTION(ViewModel, BaseComponent)
};

}


#endif
