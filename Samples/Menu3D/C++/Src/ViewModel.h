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
#include <NsApp/DelegateCommand.h>
#include <NsApp/NotifyPropertyChangedBase.h>


namespace Menu3D
{

enum class State
{
    Main,
    Start,
    Settings
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class ViewModel final: public NoesisApp::NotifyPropertyChangedBase
{
public:
    ViewModel();

private:
    const NoesisApp::DelegateCommand* GetStart() const;
    const NoesisApp::DelegateCommand* GetStartCasual() const;
    const NoesisApp::DelegateCommand* GetStartNormal() const;
    const NoesisApp::DelegateCommand* GetStartExpert() const;
    const NoesisApp::DelegateCommand* GetSettings() const;
    const NoesisApp::DelegateCommand* GetExit() const;
    const NoesisApp::DelegateCommand* GetBack() const;
    const NoesisApp::DelegateCommand* GetFadeInCompleted() const;

    const char* GetPlatform() const;

    void OnStart(BaseComponent* param);
    void OnStartCasual(BaseComponent* param);
    void OnStartNormal(BaseComponent* param);
    void OnStartExpert(BaseComponent* param);
    void OnSettings(BaseComponent* param);
    void OnExit(BaseComponent* param);
    void OnBack(BaseComponent* param);
    void OnFadeInCompleted(BaseComponent* params);

    State GetState() const;
    void SetState(State value);

private:
    NoesisApp::DelegateCommand _start;
    NoesisApp::DelegateCommand _startCasual;
    NoesisApp::DelegateCommand _startNormal;
    NoesisApp::DelegateCommand _startExpert;
    NoesisApp::DelegateCommand _settings;
    NoesisApp::DelegateCommand _exit;
    NoesisApp::DelegateCommand _back;
    NoesisApp::DelegateCommand _fadeInCompleted;

    State _state;

    NS_DECLARE_REFLECTION(ViewModel, NotifyPropertyChangedBase)
};

}

NS_DECLARE_REFLECTION_ENUM(Menu3D::State)


#endif
