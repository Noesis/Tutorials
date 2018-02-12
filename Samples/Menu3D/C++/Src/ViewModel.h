////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __MENU3D_VIEWMODEL_H__
#define __MENU3D_VIEWMODEL_H__


#include <NsCore/Noesis.h>
#include <NsCore/Ptr.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/ReflectionDeclareEnum.h>

#include "NotifyPropertyChangedBase.h"


namespace Menu3D
{

class DelegateCommand;

enum class State
{
    Main,
    Start,
    Settings
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class ViewModel final: public NotifyPropertyChangedBase
{
public:
    ViewModel();

private:
    DelegateCommand* GetStart() const;
    DelegateCommand* GetStartCasual() const;
    DelegateCommand* GetStartNormal() const;
    DelegateCommand* GetStartVeteran() const;
    DelegateCommand* GetSettings() const;
    DelegateCommand* GetExit() const;
    DelegateCommand* GetBack() const;
    DelegateCommand* GetFadeInCompleted() const;

    void OnStart(BaseComponent* param);
    void OnStartCasual(BaseComponent* param);
    void OnStartNormal(BaseComponent* param);
    void OnStartVeteran(BaseComponent* param);
    void OnSettings(BaseComponent* param);
    void OnExit(BaseComponent* param);
    void OnBack(BaseComponent* param);
    void OnFadeInCompleted(BaseComponent* params);

    State GetState() const;
    void SetState(State value);

private:
    Noesis::Ptr<DelegateCommand> _start;
    Noesis::Ptr<DelegateCommand> _startCasual;
    Noesis::Ptr<DelegateCommand> _startNormal;
    Noesis::Ptr<DelegateCommand> _startVeteran;
    Noesis::Ptr<DelegateCommand> _settings;
    Noesis::Ptr<DelegateCommand> _exit;
    Noesis::Ptr<DelegateCommand> _back;
    Noesis::Ptr<DelegateCommand> _fadeInCompleted;

    State _state;

    NS_DECLARE_REFLECTION(ViewModel, NotifyPropertyChangedBase)
};

}

NS_DECLARE_REFLECTION_ENUM(Menu3D::State)


#endif
