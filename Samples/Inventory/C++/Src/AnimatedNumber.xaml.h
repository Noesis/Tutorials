////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __INVENTORY_ANIMATEDNUMBER_H__
#define __INVENTORY_ANIMATEDNUMBER_H__


#include <NsCore/Noesis.h>
#include <NsGui/UserControl.h>


namespace Noesis
{
class TimeSpan;
}

namespace Inventory
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class AnimatedNumber final: public Noesis::UserControl
{
public:
    AnimatedNumber();

    const Noesis::TimeSpan& GetAnimationDuration() const;
    void SetAnimationDuration(const Noesis::TimeSpan& duration);

    int GetNumber() const;
    void SetNumber(int number);

public:
    static const Noesis::DependencyProperty* AnimationDurationProperty;
    static const Noesis::DependencyProperty* NumberProperty;

private:
    void InitializeComponent();
    void OnNumberChanged(int oldValue, int newValue);
    static void OnNumberChanged(Noesis::DependencyObject* d,
        const Noesis::DependencyPropertyChangedEventArgs& e);

private:
    static const Noesis::DependencyProperty* AnimatedNumberProperty;

    NS_DECLARE_REFLECTION(AnimatedNumber, Noesis::UserControl)
};


}


#endif
