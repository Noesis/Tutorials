////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __USERCONTROL_NUMERICUPDOWN_H__
#define __USERCONTROL_NUMERICUPDOWN_H__


#include <NsCore/Noesis.h>
#include <NsGui/UserControl.h>


namespace UserControl
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class NumericUpDown: public Noesis::UserControl
{
public:
    NumericUpDown();

    /// Gets or sets numeric spinner value
    //@{
    int GetValue() const;
    void SetValue(int value);
    //@}

    /// Occurs when numeric value changes
    RoutedEvent_<Noesis::RoutedPropertyChangedEventHandler<int>::Handler> ValueChanged();

public:
    static const Noesis::DependencyProperty* ValueProperty;
    static const Noesis::DependencyProperty* MaxValueProperty;
    static const Noesis::DependencyProperty* MinValueProperty;
    static const Noesis::DependencyProperty* StepValueProperty;
    static const Noesis::RoutedEvent* ValueChangedEvent;

protected:
    virtual void OnValueChanged(const Noesis::RoutedPropertyChangedEventArgs<int>& args);
    bool OnPropertyChanged(const Noesis::DependencyPropertyChangedEventArgs& args) override;

private:
    void InitializeComponent();
    bool ConnectEvent(BaseComponent* source, const char* event, const char* handler) override;

    void UpButton_Click(BaseComponent* sender, const Noesis::RoutedEventArgs& e);
    void DownButton_Click(BaseComponent* sender, const Noesis::RoutedEventArgs& e);
    static bool CoerceValue(const DependencyObject* object, const void* value, void* coercedValue);

    NS_DECLARE_REFLECTION(NumericUpDown, UserControl)
};

}


#endif
