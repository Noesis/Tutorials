////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "DateTime.h"

#include <NsCore/ReflectionImplement.h>
#include <NsGui/ResourceKeyType.h>
#include <NsGui/UIElementData.h>
#include <NsGui/FrameworkPropertyMetadata.h>


using namespace Noesis;
using namespace CustomControl;


////////////////////////////////////////////////////////////////////////////////////////////////////
int DateTime::GetDay() const
{
    return GetValue<int>(DayProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DateTime::SetDay(int day)
{
    SetValue<int>(DayProperty, day);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int DateTime::GetMonth() const
{
    return GetValue<int>(MonthProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DateTime::SetMonth(int month)
{
    SetValue<int>(MonthProperty, month);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int DateTime::GetYear() const
{
    return GetValue<int>(YearProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DateTime::SetYear(int year)
{
    SetValue<int>(YearProperty, year);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int DateTime::GetHour() const
{
    return GetValue<int>(HourProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DateTime::SetHour(int hour)
{
    SetValue<int>(HourProperty, hour);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int DateTime::GetMinute() const
{
    return GetValue<int>(MinuteProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DateTime::SetMinute(int minute)
{
    SetValue<int>(MinuteProperty, minute);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int DateTime::GetSecond() const
{
    return GetValue<int>(SecondProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DateTime::SetSecond(int second)
{
    SetValue<int>(SecondProperty, second);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_IMPLEMENT_REFLECTION(DateTime)
{
    NsMeta<TypeId>("CustomControl.DateTime");

    const TypeClass* type = TypeOf<SelfClass>();
    Ptr<ResourceKeyType> defaultStyleKey = ResourceKeyType::Create(type);

    Ptr<UIElementData> data = NsMeta<UIElementData>(type);
    data->RegisterProperty<int>(DayProperty, "Day",
        FrameworkPropertyMetadata::Create(int(1), FrameworkOptions_None));
    data->RegisterProperty<int>(MonthProperty, "Month",
        FrameworkPropertyMetadata::Create(int(1), FrameworkOptions_None));
    data->RegisterProperty<int>(YearProperty, "Year",
        FrameworkPropertyMetadata::Create(int(2000), FrameworkOptions_None));
    data->RegisterProperty<int>(HourProperty, "Hour",
        FrameworkPropertyMetadata::Create(int(0), FrameworkOptions_None));
    data->RegisterProperty<int>(MinuteProperty, "Minute",
        FrameworkPropertyMetadata::Create(int(0), FrameworkOptions_None));
    data->RegisterProperty<int>(SecondProperty, "Second",
        FrameworkPropertyMetadata::Create(int(0), FrameworkOptions_None));
    data->OverrideMetadata<Ptr<ResourceKeyType>>(FrameworkElement::DefaultStyleKeyProperty,
        "DefaultStyleKey", FrameworkPropertyMetadata::Create(defaultStyleKey,
        FrameworkOptions_None));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const DependencyProperty* DateTime::DayProperty;
const DependencyProperty* DateTime::MonthProperty;
const DependencyProperty* DateTime::YearProperty;
const DependencyProperty* DateTime::HourProperty;
const DependencyProperty* DateTime::MinuteProperty;
const DependencyProperty* DateTime::SecondProperty;
