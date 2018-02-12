////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __BUTTONS_DELEGATECOMMAND_H__
#define __BUTTONS_DELEGATECOMMAND_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/BaseCommand.h>
#include <NsCore/Delegate.h>


namespace Commands
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class DelegateCommand final: public Noesis::BaseCommand
{
public:
    typedef Noesis::Delegate<void (BaseComponent*)> ExecuteFunc;
    typedef Noesis::Delegate<bool (BaseComponent*)> CanExecuteFunc;

    DelegateCommand(const ExecuteFunc& execute);
    DelegateCommand(const ExecuteFunc& execute, const CanExecuteFunc& canExecute);

    // From BaseCommand
    //@{
    bool CanExecute(BaseComponent* param) const override;
    void Execute(BaseComponent* param) const override;
    //@}

private:
    ExecuteFunc _execute;
    CanExecuteFunc _canExecute;

    NS_DECLARE_REFLECTION(DelegateCommand, BaseCommand)
};

}


#endif
