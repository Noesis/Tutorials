////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "ExponentialAnimation.h"

#include <NsCore/ReflectionImplement.h>
#include <NsCore/ReflectionImplementEnum.h>
#include <NsCore/Nullable.h>
#include <NsGui/UIElementData.h>
#include <NsGui/PropertyMetadata.h>
#include <NsGui/AnimationClock.h>


using namespace CustomAnimation;
using namespace Noesis;


////////////////////////////////////////////////////////////////////////////////////////////////////
static float EaseOut(float t, float start, float delta, float power)
{
    float val = powf(t, 1.0f / power);
    val *= delta;
    val += start;
    return val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static float EaseIn(float t, float start, float delta, float power)
{
    float val = powf(t, power);
    val *= delta;
    val += start;
    return val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static float EaseInOut(float t, float start, float delta, float power)
{
    float val;

    if (t <= 0.5f)
    {
        val = EaseOut(t * 2.0f, start, delta * 0.5f, power);
    }
    else
    {
        val = EaseIn((t - 0.5f) * 2.0f, start, delta * 0.5f, power);
        val += delta * 0.5f;
    }

    return val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ExponentialAnimation::EdgeBehaviorEnum ExponentialAnimation::GetEdgeBehavior() const
{
    return GetValue<EdgeBehaviorEnum>(EdgeBehaviorProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ExponentialAnimation::SetEdgeBehavior(EdgeBehaviorEnum value)
{
    SetValue<EdgeBehaviorEnum>(EdgeBehaviorProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float ExponentialAnimation::GetPower() const
{
    return GetValue<float>(PowerProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ExponentialAnimation::SetPower(float value)
{
    SetValue<float>(PowerProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Nullable<float> ExponentialAnimation::GetFrom() const
{
    return GetValue<Nullable<float>>(FromProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ExponentialAnimation::SetFrom(Nullable<float> value)
{
    SetValue<Nullable<float>>(FromProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Nullable<float> ExponentialAnimation::GetTo() const
{
    return GetValue<Nullable<float>>(ToProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ExponentialAnimation::SetTo(Nullable<float> value)
{
    SetValue<Nullable<float>>(ToProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float ExponentialAnimation::GetCurrentValueCore(float defaultOrigin, float, AnimationClock* clock)
{
    float start = GetFrom().HasValue() ? GetFrom().GetValue() : defaultOrigin;
    float delta = GetTo().HasValue() ? GetTo().GetValue() - start : defaultOrigin - start;
    float power = GetPower();

    switch (GetEdgeBehavior())
    {
        case EdgeBehaviorEnum::EaseIn:
        {
            return EaseIn(clock->GetCurrentProgress(), start, delta, power);
        }
        case EdgeBehaviorEnum::EaseOut:
        {
            return EaseOut(clock->GetCurrentProgress(), start, delta, power);
        }
        case EdgeBehaviorEnum::EaseInOut:
        {
            return EaseInOut(clock->GetCurrentProgress(), start, delta, power);
        }
        default:
            NS_ASSERT_UNREACHABLE;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Ptr<Freezable> ExponentialAnimation::CreateInstanceCore() const
{
    return *new ExponentialAnimation();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION_ENUM(CustomAnimation::ExponentialAnimation::EdgeBehaviorEnum)
{
    NsVal("EaseIn", ExponentialAnimation::EdgeBehaviorEnum::EaseIn);
    NsVal("EaseOut", ExponentialAnimation::EdgeBehaviorEnum::EaseOut);
    NsVal("EaseInOut", ExponentialAnimation::EdgeBehaviorEnum::EaseInOut);
}

NS_IMPLEMENT_REFLECTION(CustomAnimation::ExponentialAnimation, "CustomAnimation.ExponentialAnimation")
{
    UIElementData* data = NsMeta<UIElementData>(TypeOf<SelfClass>());

    data->RegisterProperty<ExponentialAnimation::EdgeBehaviorEnum>(EdgeBehaviorProperty, "EdgeBehavior",
        PropertyMetadata::Create(ExponentialAnimation::EdgeBehaviorEnum::EaseIn));

    data->RegisterProperty<float>(PowerProperty, "Power", PropertyMetadata::Create(2.0f));

    data->RegisterProperty<Nullable<float>>(FromProperty, "From", PropertyMetadata::Create(Nullable<float>()));
    data->RegisterProperty<Nullable<float>>(ToProperty, "To", PropertyMetadata::Create(Nullable<float>()));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const DependencyProperty* ExponentialAnimation::EdgeBehaviorProperty;
const DependencyProperty* ExponentialAnimation::PowerProperty;
const DependencyProperty* ExponentialAnimation::FromProperty;
const DependencyProperty* ExponentialAnimation::ToProperty;
