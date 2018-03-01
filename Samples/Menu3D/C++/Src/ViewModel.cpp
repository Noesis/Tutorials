////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "ViewModel.h"
#include "DelegateCommand.h"

#include <NsCore/ReflectionImplement.h>
#include <NsCore/ReflectionImplementEnum.h>
#include <NsCore/Log.h>
#include <NsGui/UIElement.h>
#include <NsApp/Application.h>


using namespace Menu3D;
using namespace Noesis;


////////////////////////////////////////////////////////////////////////////////////////////////////
ViewModel::ViewModel()
{
    _start = *new DelegateCommand(MakeDelegate(this, &ViewModel::OnStart));
    _startCasual = *new DelegateCommand(MakeDelegate(this, &ViewModel::OnStartCasual));
    _startNormal = *new DelegateCommand(MakeDelegate(this, &ViewModel::OnStartNormal));
    _startVeteran = *new DelegateCommand(MakeDelegate(this, &ViewModel::OnStartVeteran));
    _settings = *new DelegateCommand(MakeDelegate(this, &ViewModel::OnSettings));
    _exit = *new DelegateCommand(MakeDelegate(this, &ViewModel::OnExit));
    _back = *new DelegateCommand(MakeDelegate(this, &ViewModel::OnBack));
    _fadeInCompleted = *new DelegateCommand(MakeDelegate(this, &ViewModel::OnFadeInCompleted));

    _state = State::Main;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
DelegateCommand* ViewModel::GetStart() const
{
    return _start;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
DelegateCommand* ViewModel::GetStartCasual() const
{
    return _startCasual;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
DelegateCommand* ViewModel::GetStartNormal() const
{
    return _startNormal;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
DelegateCommand* ViewModel::GetStartVeteran() const
{
    return _startVeteran;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
DelegateCommand* ViewModel::GetSettings() const
{
    return _settings;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
DelegateCommand* ViewModel::GetExit() const
{
    return _exit;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
DelegateCommand* ViewModel::GetBack() const
{
    return _back;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
DelegateCommand* ViewModel::GetFadeInCompleted() const
{
    return _fadeInCompleted;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::OnStart(BaseComponent*)
{
    SetState(State::Start);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::OnStartCasual(BaseComponent*)
{
    NS_LOG_INFO("Start Casual");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::OnStartNormal(BaseComponent*)
{
    NS_LOG_INFO("Start Normal");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::OnStartVeteran(BaseComponent*)
{
    NS_LOG_INFO("Start Veteran");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::OnSettings(BaseComponent*)
{
    SetState(State::Settings);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::OnExit(BaseComponent*)
{
    NS_LOG_INFO("Exiting game");
    NoesisApp::Application::Current()->Shutdown();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::OnBack(BaseComponent*)
{
    switch (_state)
    {
        case State::Main:
        {
            OnExit(nullptr);
            break;
        }
        case State::Start:
        case State::Settings:
        {
            SetState(State::Main);
            break;
        }
        default:
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::OnFadeInCompleted(BaseComponent* param)
{
    UIElement* target = (UIElement*)param;
    target->Focus();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
State ViewModel::GetState() const
{
    return _state;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::SetState(State value)
{
    if (_state != value)
    {
        _state = value;
        OnPropertyChanged("State");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_IMPLEMENT_REFLECTION(ViewModel)
{
    NsProp("Start", &ViewModel::GetStart);
    NsProp("StartCasual", &ViewModel::GetStartCasual);
    NsProp("StartNormal", &ViewModel::GetStartNormal);
    NsProp("StartVeteran", &ViewModel::GetStartVeteran);
    NsProp("Settings", &ViewModel::GetSettings);
    NsProp("Exit", &ViewModel::GetExit);
    NsProp("Back", &ViewModel::GetBack);
    NsProp("FadeInCompleted", &ViewModel::GetFadeInCompleted);
    NsProp("State", &ViewModel::GetState, &ViewModel::SetState);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_IMPLEMENT_REFLECTION_ENUM(State)
{
    NsVal("Main", State::Main);
    NsVal("Start", State::Start);
    NsVal("Settings", State::Settings);
}
