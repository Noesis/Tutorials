////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __LOGIN_NOTIFYPROPERTYCHANGEDBASE_H__
#define __LOGIN_NOTIFYPROPERTYCHANGEDBASE_H__


#include <NsCore/Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/Delegate.h>
#include <NsGui/INotifyPropertyChanged.h>


namespace Login
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class NotifyPropertyChangedBase: public Noesis::BaseComponent, public Noesis::INotifyPropertyChanged
{
public:
    /// From INotifyPropertyChanged
    //@{
    Noesis::PropertyChangedEventHandler& PropertyChanged() override final;
    //@}

    NS_IMPLEMENT_INTERFACE_FIXUP

protected:
    void OnPropertyChanged(const char* name);

private:
    Noesis::PropertyChangedEventHandler _propertyChanged;

    NS_DECLARE_REFLECTION(NotifyPropertyChangedBase, BaseComponent)
};

}


#endif
