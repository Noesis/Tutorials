////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CUSTOMANIMATION_CIRCLEANIMATION_H__
#define __CUSTOMANIMATION_CIRCLEANIMATION_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsGui/DoubleAnimationBase.h>


namespace CustomAnimation
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class CircleAnimation final: public Noesis::DoubleAnimationBase
{
public:
    enum class DirectionEnum
    {
        XDirection,
        YDirection,
    };

    /// Specifies which side of the transition gets the "bounce" effect
    //@{
    DirectionEnum GetDirection() const;
    void SetDirection(DirectionEnum value);
    //@}

    /// Exponential rate of growth
    //@{
    float GetRadius() const;
    void SetRadius(float value);
    //@}

public:
    static const Noesis::DependencyProperty* DirectionEnumProperty;
    static const Noesis::DependencyProperty* RadiusProperty;

private:
    float GetCurrentValueCore(float defaultOrigin, float defaultDestination,
        Noesis::AnimationClock* clock) override;
    Noesis::Ptr<Freezable> CreateInstanceCore() const override;

private:
    NS_DECLARE_REFLECTION(CircleAnimation, DoubleAnimationBase)
};

}

NS_DECLARE_REFLECTION_ENUM(CustomAnimation::CircleAnimation::DirectionEnum)

#endif
