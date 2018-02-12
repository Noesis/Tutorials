////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CUSTOMCONTROL_DATETIME_H__
#define __CUSTOMCONTROL_DATETIME_H__


#include <NsCore/Noesis.h>
#include <NsGui/Control.h>


namespace CustomControl
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class DateTime: public Noesis::Control
{
public:
    /// Gets or sets day
    //@{
    int GetDay() const;
    void SetDay(int day);
    //@}

    /// Gets or sets month
    //@{
    int GetMonth() const;
    void SetMonth(int month);
    //@}

    /// Gets or sets year
    //@{
    int GetYear() const;
    void SetYear(int year);
    //@}

    /// Gets or sets hour
    //@{
    int GetHour() const;
    void SetHour(int hour);
    //@}

    /// Gets or sets minute
    //@{
    int GetMinute() const;
    void SetMinute(int minute);
    //@}

    /// Gets or sets second
    //@{
    int GetSecond() const;
    void SetSecond(int second);
    //@}

public:
    static const Noesis::DependencyProperty* DayProperty;
    static const Noesis::DependencyProperty* MonthProperty;
    static const Noesis::DependencyProperty* YearProperty;
    static const Noesis::DependencyProperty* HourProperty;
    static const Noesis::DependencyProperty* MinuteProperty;
    static const Noesis::DependencyProperty* SecondProperty;

    NS_DECLARE_REFLECTION(DateTime, Control)
};

}


#endif
