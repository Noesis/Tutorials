////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "CircleAnimation.h"

#include <NsCore/ReflectionImplement.h>
#include <NsCore/ReflectionImplementEnum.h>
#include <NsCore/Nullable.h>
#include <NsGui/UIElementData.h>
#include <NsGui/PropertyMetadata.h>
#include <NsGui/AnimationClock.h>


using namespace CustomAnimation;
using namespace Noesis;


////////////////////////////////////////////////////////////////////////////////////////////////////
CircleAnimation::DirectionEnum CircleAnimation::GetDirection() const
{
    return GetValue<DirectionEnum>(DirectionEnumProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CircleAnimation::SetDirection(DirectionEnum value)
{
    SetValue<DirectionEnum>(DirectionEnumProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float CircleAnimation::GetRadius() const
{
    return GetValue<float>(RadiusProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CircleAnimation::SetRadius(float value)
{
    SetValue<float>(RadiusProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float CircleAnimation::GetCurrentValueCore(float defaultOrigin, float, AnimationClock* clock)
{
    float t = clock->GetCurrentProgress();
    float val = GetDirection() == DirectionEnum::XDirection ? 1 - cosf(TwoPi * t) : -sinf(TwoPi * t);
    return val * GetRadius() + defaultOrigin;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Ptr<Freezable> CircleAnimation::CreateInstanceCore() const
{
    return *new CircleAnimation();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION_ENUM(CustomAnimation::CircleAnimation::DirectionEnum)
{
    NsVal("XDirection", CircleAnimation::DirectionEnum::XDirection);
    NsVal("YDirection", CircleAnimation::DirectionEnum::YDirection);
}

NS_IMPLEMENT_REFLECTION(CustomAnimation::CircleAnimation, "CustomAnimation.CircleAnimation")
{
    UIElementData* data = NsMeta<UIElementData>(TypeOf<SelfClass>());

    data->RegisterProperty<CircleAnimation::DirectionEnum>(DirectionEnumProperty, "Direction",
        PropertyMetadata::Create(CircleAnimation::DirectionEnum::XDirection));

    data->RegisterProperty<float>(RadiusProperty, "Radius", PropertyMetadata::Create(10.0f));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const DependencyProperty* CircleAnimation::DirectionEnumProperty;
const DependencyProperty* CircleAnimation::RadiusProperty;
