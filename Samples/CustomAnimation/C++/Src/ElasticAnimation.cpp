////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "ElasticAnimation.h"

#include <NsCore/ReflectionImplement.h>
#include <NsCore/ReflectionImplementEnum.h>
#include <NsCore/Nullable.h>
#include <NsGui/UIElementData.h>
#include <NsGui/PropertyMetadata.h>
#include <NsGui/AnimationClock.h>


using namespace CustomAnimation;
using namespace Noesis;


////////////////////////////////////////////////////////////////////////////////////////////////////
static float EaseOut(float t, float start, float delta, float springiness, float oscillations)
{
    float val = powf(1.0f - t, springiness) * cosf(TwoPi * t * oscillations);
    val = delta - val * delta;
    val += start;
    return val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static float EaseIn(float t, float start, float delta, float springiness, float oscillations)
{
    float val = powf(t, springiness) * cosf(TwoPi * t * oscillations);
    val = val * delta;
    val += start;
    return val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static float EaseInOut(float t, float start, float delta, float springiness, float oscillations)
{
    float val;

    if (t <= 0.5f)
    {
        val = EaseIn(t * 2.0f, start, delta * 0.5f, springiness, oscillations);
    }
    else
    {
        val = EaseOut((t - 0.5f) * 2.0f, start, delta * 0.5f, springiness, oscillations);
        val += delta * 0.5f;
    }

    return val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ElasticAnimation::EdgeBehaviorEnum ElasticAnimation::GetEdgeBehavior() const
{
    return GetValue<EdgeBehaviorEnum>(EdgeBehaviorProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ElasticAnimation::SetEdgeBehavior(EdgeBehaviorEnum value)
{
    SetValue<EdgeBehaviorEnum>(EdgeBehaviorProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float ElasticAnimation::GetSpringiness() const
{
    return GetValue<float>(SpringinessProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ElasticAnimation::SetSpringiness(float value)
{
    SetValue<float>(SpringinessProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float ElasticAnimation::GetOscillations() const
{
    return GetValue<float>(OscillationsProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ElasticAnimation::SetOscillations(float value)
{
    SetValue<float>(OscillationsProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Nullable<float> ElasticAnimation::GetFrom() const
{
    return GetValue<Nullable<float>>(FromProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ElasticAnimation::SetFrom(Nullable<float> value)
{
    SetValue<Nullable<float>>(FromProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Nullable<float> ElasticAnimation::GetTo() const
{
    return GetValue<Nullable<float>>(ToProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ElasticAnimation::SetTo(Nullable<float> value)
{
    SetValue<Nullable<float>>(ToProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float ElasticAnimation::GetCurrentValueCore(float defaultOrigin, float, AnimationClock* clock)
{
    float start = GetFrom().HasValue() ? GetFrom().GetValue() : defaultOrigin;
    float delta = GetTo().HasValue() ? GetTo().GetValue() - start : defaultOrigin - start;
    float springiness = GetSpringiness();
    float oscillations = GetOscillations();

    switch (GetEdgeBehavior())
    {
        case EdgeBehaviorEnum::EaseIn:
        {
            return EaseIn(clock->GetCurrentProgress(), start, delta, springiness, oscillations);
        }
        case EdgeBehaviorEnum::EaseOut:
        {
            return EaseOut(clock->GetCurrentProgress(), start, delta, springiness, oscillations);
        }
        case EdgeBehaviorEnum::EaseInOut:
        {
            return EaseInOut(clock->GetCurrentProgress(), start, delta, springiness, oscillations);
        }
        default:
            NS_ASSERT_UNREACHABLE;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Ptr<Freezable> ElasticAnimation::CreateInstanceCore() const
{
    return *new ElasticAnimation();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION_ENUM(CustomAnimation::ElasticAnimation::EdgeBehaviorEnum)
{
    NsVal("EaseIn", ElasticAnimation::EdgeBehaviorEnum::EaseIn);
    NsVal("EaseOut", ElasticAnimation::EdgeBehaviorEnum::EaseOut);
    NsVal("EaseInOut", ElasticAnimation::EdgeBehaviorEnum::EaseInOut);
}

NS_IMPLEMENT_REFLECTION(CustomAnimation::ElasticAnimation, "CustomAnimation.ElasticAnimation")
{
    UIElementData* data = NsMeta<UIElementData>(TypeOf<SelfClass>());

    data->RegisterProperty<ElasticAnimation::EdgeBehaviorEnum>(EdgeBehaviorProperty, "EdgeBehavior",
        PropertyMetadata::Create(ElasticAnimation::EdgeBehaviorEnum::EaseIn));

    data->RegisterProperty<float>(SpringinessProperty, "Springiness", PropertyMetadata::Create(3.0f));
    data->RegisterProperty<float>(OscillationsProperty, "Oscillations", PropertyMetadata::Create(10.0f));

    data->RegisterProperty<Nullable<float>>(FromProperty, "From", PropertyMetadata::Create(Nullable<float>()));
    data->RegisterProperty<Nullable<float>>(ToProperty, "To", PropertyMetadata::Create(Nullable<float>()));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const DependencyProperty* ElasticAnimation::EdgeBehaviorProperty;
const DependencyProperty* ElasticAnimation::SpringinessProperty;
const DependencyProperty* ElasticAnimation::OscillationsProperty;
const DependencyProperty* ElasticAnimation::FromProperty;
const DependencyProperty* ElasticAnimation::ToProperty;
