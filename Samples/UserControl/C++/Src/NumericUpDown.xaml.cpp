////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionImplement.h>
#include <NsGui/Uri.h>
#include <NsGui/Button.h>
#include <NsGui/UIElementData.h>
#include <NsGui/IntegrationAPI.h>
#include <NsGui/FrameworkPropertyMetadata.h>

#include "NumericUpDown.h"


using namespace Noesis;
using namespace UserControls;


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
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(NumericUpDown, "UserControls.NumericUpDown")
{
    auto onValueChanged = [](DependencyObject* d, const DependencyPropertyChangedEventArgs& e)
    {
        NumericUpDown* control = (NumericUpDown*)d;
        int oldValue = *(const int*)e.oldValue;
        int newValue = *(const int*)e.newValue;

        RoutedPropertyChangedEventArgs<int> args(control, ValueChangedEvent, oldValue, newValue);
        control->OnValueChanged(args);
    };

    auto coerceValue = [](const DependencyObject* object, const void* value, void* coercedValue)
    {
        int maxValue = object->GetValue<int>(MaxValueProperty);
        int minValue = object->GetValue<int>(MinValueProperty);

        int newValue = *(const int*)value;
        int& coerced = *(int*)coercedValue;

        coerced = Clip(newValue, minValue, maxValue);
        return true;
    };

    UIElementData* data = NsMeta<UIElementData>(TypeOf<SelfClass>());
    data->RegisterProperty<int>(ValueProperty, "Value", PropertyMetadata::Create(int(0),
        PropertyChangedCallback(onValueChanged), CoerceValueCallback(coerceValue)));
    data->RegisterProperty<int>(MaxValueProperty, "MaxValue", PropertyMetadata::Create(int(255)));
    data->RegisterProperty<int>(MinValueProperty, "MinValue", PropertyMetadata::Create(int(0)));
    data->RegisterProperty<int>(StepValueProperty, "StepValue", PropertyMetadata::Create(int(1)));

    data->RegisterEvent(ValueChangedEvent, "ValueChanged", RoutingStrategy_Bubble);
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const DependencyProperty* NumericUpDown::ValueProperty;
const DependencyProperty* NumericUpDown::MaxValueProperty;
const DependencyProperty* NumericUpDown::MinValueProperty;
const DependencyProperty* NumericUpDown::StepValueProperty;
const RoutedEvent* NumericUpDown::ValueChangedEvent;
