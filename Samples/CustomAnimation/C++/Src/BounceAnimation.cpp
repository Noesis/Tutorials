////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "BounceAnimation.h"

#include <NsCore/ReflectionImplement.h>
#include <NsCore/ReflectionImplementEnum.h>
#include <NsCore/Nullable.h>
#include <NsGui/UIElementData.h>
#include <NsGui/PropertyMetadata.h>
#include <NsGui/AnimationClock.h>


using namespace CustomAnimation;
using namespace Noesis;


////////////////////////////////////////////////////////////////////////////////////////////////////
static float EaseOut(float t, float start, float delta, float bounciness, int bounces)
{
    float val = fabsf(powf(1.0f - t, bounciness) * cosf(TwoPi * t * bounces));
    val = delta - val * delta;
    val += start;
    return val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static float EaseIn(float t, float start, float delta, float bounciness, int bounces)
{
    float val = fabsf(powf(t, bounciness) * cosf(TwoPi * t * bounces));
    val = val * delta;
    val += start;
    return val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static float EaseInOut(float t, float start, float delta, float bounciness, int bounces)
{
    float val;

    if (t <= 0.5f)
    {
        val = EaseIn(t * 2.0f, start, delta * 0.5f, bounciness, bounces);
    }
    else
    {
        val = EaseOut((t - 0.5f) * 2.0f, start, delta * 0.5f, bounciness, bounces);
        val += delta * 0.5f;
    }

    return val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
BounceAnimation::EdgeBehaviorEnum BounceAnimation::GetEdgeBehavior() const
{
    return GetValue<EdgeBehaviorEnum>(EdgeBehaviorProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void BounceAnimation::SetEdgeBehavior(EdgeBehaviorEnum value)
{
    SetValue<EdgeBehaviorEnum>(EdgeBehaviorProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int BounceAnimation::GetBounces() const
{
    return GetValue<int>(BouncesProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void BounceAnimation::SetBounces(int value)
{
    SetValue<int>(BouncesProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float BounceAnimation::GetBounciness() const
{
    return GetValue<float>(BouncinessProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void BounceAnimation::SetBounciness(float value)
{
    SetValue<float>(BouncinessProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Nullable<float> BounceAnimation::GetFrom() const
{
    return GetValue<Nullable<float>>(FromProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void BounceAnimation::SetFrom(Nullable<float> value)
{
    SetValue<Nullable<float>>(FromProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Nullable<float> BounceAnimation::GetTo() const
{
    return GetValue<Nullable<float>>(ToProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void BounceAnimation::SetTo(Nullable<float> value)
{
    SetValue<Nullable<float>>(ToProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float BounceAnimation::GetCurrentValueCore(float defaultOrigin, float, AnimationClock* clock)
{
    float start = GetFrom().HasValue() ? GetFrom().GetValue() : defaultOrigin;
    float delta = GetTo().HasValue() ? GetTo().GetValue() - start : defaultOrigin - start;
    float bounciness = GetBounciness();
    int bounces = GetBounces();

    switch (GetEdgeBehavior())
    {
        case EdgeBehaviorEnum::EaseIn:
        {
            return EaseIn(clock->GetCurrentProgress(), start, delta, bounciness, bounces);
        }
        case EdgeBehaviorEnum::EaseOut:
        {
            return EaseOut(clock->GetCurrentProgress(), start, delta, bounciness, bounces);
        }
        case EdgeBehaviorEnum::EaseInOut:
        {
            return EaseInOut(clock->GetCurrentProgress(), start, delta, bounciness, bounces);
        }
        default:
            NS_ASSERT_UNREACHABLE;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Ptr<Freezable> BounceAnimation::CreateInstanceCore() const
{
    return *new BounceAnimation();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION_ENUM(CustomAnimation::BounceAnimation::EdgeBehaviorEnum)
{
    NsVal("EaseIn", BounceAnimation::EdgeBehaviorEnum::EaseIn);
    NsVal("EaseOut", BounceAnimation::EdgeBehaviorEnum::EaseOut);
    NsVal("EaseInOut", BounceAnimation::EdgeBehaviorEnum::EaseInOut);
}

NS_IMPLEMENT_REFLECTION(CustomAnimation::BounceAnimation, "CustomAnimation.BounceAnimation")
{
    UIElementData* data = NsMeta<UIElementData>(TypeOf<SelfClass>());

    data->RegisterProperty<BounceAnimation::EdgeBehaviorEnum>(EdgeBehaviorProperty, "EdgeBehavior",
        PropertyMetadata::Create(BounceAnimation::EdgeBehaviorEnum::EaseInOut));

    data->RegisterProperty<int>(BouncesProperty, "Bounces", PropertyMetadata::Create(5));
    data->RegisterProperty<float>(BouncinessProperty, "Bounciness", PropertyMetadata::Create(3.0f));

    data->RegisterProperty<Nullable<float>>(FromProperty, "From", PropertyMetadata::Create(Nullable<float>()));
    data->RegisterProperty<Nullable<float>>(ToProperty, "To", PropertyMetadata::Create(Nullable<float>()));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const DependencyProperty* BounceAnimation::EdgeBehaviorProperty;
const DependencyProperty* BounceAnimation::BouncesProperty;
const DependencyProperty* BounceAnimation::BouncinessProperty;
const DependencyProperty* BounceAnimation::FromProperty;
const DependencyProperty* BounceAnimation::ToProperty;
