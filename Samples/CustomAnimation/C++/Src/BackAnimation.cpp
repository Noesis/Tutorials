////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "BackAnimation.h"

#include <NsCore/ReflectionImplement.h>
#include <NsCore/ReflectionImplementEnum.h>
#include <NsCore/Nullable.h>
#include <NsGui/UIElementData.h>
#include <NsGui/PropertyMetadata.h>
#include <NsGui/AnimationClock.h>


using namespace CustomAnimation;
using namespace Noesis;


static constexpr float Frequency = 0.5f;


////////////////////////////////////////////////////////////////////////////////////////////////////
static float EaseOut(float t, float start, float delta, float amplitude, float suppression)
{
    float val = powf(t, suppression) * amplitude * sinf(TwoPi * t * Frequency) + t;
    val *= delta;
    val += start;
    return val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static float EaseIn(float t, float start, float delta, float amplitude, float suppression)
{
    float val = t - powf(1.0f - t, suppression) * amplitude *  sinf(TwoPi * t * Frequency);
    val *= delta;
    val += start;
    return val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static float EaseInOut(float t, float start, float delta, float amplitude, float suppression)
{
    float val;

    if (t <= 0.5f)
    {
        val = EaseIn(t * 2.0f, start, delta * 0.5f, amplitude, suppression);
    }
    else
    {
        val = EaseOut((t - 0.5f) * 2.0f, start, delta * 0.5f, amplitude, suppression);
        val += delta * 0.5f;
    }

    return val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
BackAnimation::EdgeBehaviorEnum BackAnimation::GetEdgeBehavior() const
{
    return GetValue<EdgeBehaviorEnum>(EdgeBehaviorProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void BackAnimation::SetEdgeBehavior(EdgeBehaviorEnum value)
{
    SetValue<EdgeBehaviorEnum>(EdgeBehaviorProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float BackAnimation::GetAmplitude() const
{
    return GetValue<float>(AmplitudeProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void BackAnimation::SetAmplitude(float value)
{
    SetValue<float>(AmplitudeProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float BackAnimation::GetSuppression() const
{
    return GetValue<float>(SuppressionProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void BackAnimation::SetSuppression(float value)
{
    SetValue<float>(SuppressionProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Nullable<float> BackAnimation::GetFrom() const
{
    return GetValue<Nullable<float>>(FromProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void BackAnimation::SetFrom(Nullable<float> value)
{
    SetValue<Nullable<float>>(FromProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Nullable<float> BackAnimation::GetTo() const
{
    return GetValue<Nullable<float>>(ToProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void BackAnimation::SetTo(Nullable<float> value)
{
    SetValue<Nullable<float>>(ToProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float BackAnimation::GetCurrentValueCore(float defaultOrigin, float, AnimationClock* clock)
{
    float start = GetFrom().HasValue() ? GetFrom().GetValue() : defaultOrigin;
    float delta = GetTo().HasValue() ? GetTo().GetValue() - start : defaultOrigin - start;
    float amplitude = GetAmplitude();
    float supression = GetSuppression();

    switch (GetEdgeBehavior())
    {
        case EdgeBehaviorEnum::EaseIn:
        {
            return EaseIn(clock->GetCurrentProgress(), start, delta, amplitude, supression);
        }
        case EdgeBehaviorEnum::EaseOut:
        {
            return EaseOut(clock->GetCurrentProgress(), start, delta, amplitude, supression);
        }
        case EdgeBehaviorEnum::EaseInOut:
        {
            return EaseInOut(clock->GetCurrentProgress(), start, delta, amplitude, supression);
        }
        default:
            NS_ASSERT_UNREACHABLE;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Ptr<Freezable> BackAnimation::CreateInstanceCore() const
{
    return *new BackAnimation();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION_ENUM(CustomAnimation::BackAnimation::EdgeBehaviorEnum)
{
    NsVal("EaseIn", BackAnimation::EdgeBehaviorEnum::EaseIn);
    NsVal("EaseOut", BackAnimation::EdgeBehaviorEnum::EaseOut);
    NsVal("EaseInOut", BackAnimation::EdgeBehaviorEnum::EaseInOut);
}

NS_IMPLEMENT_REFLECTION(CustomAnimation::BackAnimation, "CustomAnimation.BackAnimation")
{
    UIElementData* data = NsMeta<UIElementData>(TypeOf<SelfClass>());

    data->RegisterProperty<BackAnimation::EdgeBehaviorEnum>(EdgeBehaviorProperty, "EdgeBehavior",
        PropertyMetadata::Create(BackAnimation::EdgeBehaviorEnum::EaseIn));

    data->RegisterProperty<float>(AmplitudeProperty, "Amplitude", PropertyMetadata::Create(4.0f));
    data->RegisterProperty<float>(SuppressionProperty, "Suppression", PropertyMetadata::Create(2.0f));

    data->RegisterProperty<Nullable<float>>(FromProperty, "From", PropertyMetadata::Create(Nullable<float>()));
    data->RegisterProperty<Nullable<float>>(ToProperty, "To", PropertyMetadata::Create(Nullable<float>()));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const DependencyProperty* BackAnimation::EdgeBehaviorProperty;
const DependencyProperty* BackAnimation::AmplitudeProperty;
const DependencyProperty* BackAnimation::SuppressionProperty;
const DependencyProperty* BackAnimation::FromProperty;
const DependencyProperty* BackAnimation::ToProperty;
