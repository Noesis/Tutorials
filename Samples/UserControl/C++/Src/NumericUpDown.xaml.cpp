////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionImplement.h>
#include <NsGui/Button.h>
#include <NsGui/UIElementData.h>
#include <NsGui/IntegrationAPI.h>
#include <NsGui/FrameworkPropertyMetadata.h>

#include "NumericUpDown.h"


using namespace Noesis;
using namespace UserControl;


////////////////////////////////////////////////////////////////////////////////////////////////////
NumericUpDown::NumericUpDown()
{
    InitializeComponent();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int NumericUpDown::GetValue() const
{
    return DependencyObject::GetValue<int>(ValueProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NumericUpDown::SetValue(int value)
{
    DependencyObject::SetValue<int>(ValueProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
UIElement::RoutedEvent_<RoutedPropertyChangedEventHandler<int>::Handler> NumericUpDown::ValueChanged()
{
    return RoutedEvent_<RoutedPropertyChangedEventHandler<int>::Handler>(this, ValueChangedEvent);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NumericUpDown::OnValueChanged(const Noesis::RoutedPropertyChangedEventArgs<int>& args)
{
    RaiseEvent(args);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NumericUpDown::OnPropertyChanged(const Noesis::DependencyPropertyChangedEventArgs& args)
{
    bool handled = ParentClass::OnPropertyChanged(args);

    if (!handled)
    {
        if (args.prop == ValueProperty)
        {
            int oldValue = *static_cast<const int*>(args.oldValue);
            int newValue = *static_cast<const int*>(args.newValue);

            RoutedPropertyChangedEventArgs<int> e(this, ValueChangedEvent, oldValue, newValue);
            OnValueChanged(e);
            return true;
        }
    }

    return handled;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NumericUpDown::InitializeComponent()
{
    GUI::LoadComponent(this, "NumericUpDown.xaml");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NumericUpDown::ConnectEvent(BaseComponent* source, const char* event, const char* handler)
{
    NS_CONNECT_EVENT(Button, Click, UpButton_Click);
    NS_CONNECT_EVENT(Button, Click, DownButton_Click);
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NumericUpDown::UpButton_Click(BaseComponent*, const Noesis::RoutedEventArgs&)
{
    int step = DependencyObject::GetValue<int>(StepValueProperty);
    SetValue(GetValue() + step);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NumericUpDown::DownButton_Click(BaseComponent*, const Noesis::RoutedEventArgs&)
{
    int step = DependencyObject::GetValue<int>(StepValueProperty);
    SetValue(GetValue() - step);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NumericUpDown::CoerceValue(const DependencyObject* object, const void* value, void* coercedValue)
{
    int maxValue = object->GetValue<int>(MaxValueProperty);
    int minValue = object->GetValue<int>(MinValueProperty);
    
    int newValue = *static_cast<const int*>(value);
    int& coerced = *static_cast<int*>(coercedValue);

    coerced = Clip(newValue, minValue, maxValue);
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_IMPLEMENT_REFLECTION(NumericUpDown)
{
    NsMeta<TypeId>("UserControl.NumericUpDown");

    Ptr<UIElementData> data = NsMeta<UIElementData>(TypeOf<SelfClass>());
    data->RegisterProperty<int>(ValueProperty, "Value",
        FrameworkPropertyMetadata::Create(int(0), &CoerceValue));
    data->RegisterProperty<int>(MaxValueProperty, "MaxValue",
        FrameworkPropertyMetadata::Create(int(255), FrameworkOptions_None));
    data->RegisterProperty<int>(MinValueProperty, "MinValue",
        FrameworkPropertyMetadata::Create(int(0), FrameworkOptions_None));
    data->RegisterProperty<int>(StepValueProperty, "StepValue",
        FrameworkPropertyMetadata::Create(int(1), FrameworkOptions_None));

    data->RegisterEvent(ValueChangedEvent, "ValueChanged", RoutingStrategy_Bubbling);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const DependencyProperty* NumericUpDown::ValueProperty;
const DependencyProperty* NumericUpDown::MaxValueProperty;
const DependencyProperty* NumericUpDown::MinValueProperty;
const DependencyProperty* NumericUpDown::StepValueProperty;
const RoutedEvent* NumericUpDown::ValueChangedEvent;
