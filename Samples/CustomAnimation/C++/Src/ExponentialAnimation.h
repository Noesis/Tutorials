////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CUSTOMANIMATION_EXPONENTIALANIMATION_H__
#define __CUSTOMANIMATION_EXPONENTIALANIMATION_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsGui/DoubleAnimationBase.h>


namespace CustomAnimation
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class ExponentialAnimation final: public Noesis::DoubleAnimationBase
{
public:
    enum class EdgeBehaviorEnum
    {
        EaseIn,
        EaseOut,
        EaseInOut
    };

    /// Specifies which side of the transition gets the "bounce" effect
    //@{
    EdgeBehaviorEnum GetEdgeBehavior() const;
    void SetEdgeBehavior(EdgeBehaviorEnum value);
    //@}

    /// Exponential rate of growth
    //@{
    float GetPower() const;
    void SetPower(float value);
    //@}

    /// Specifies the starting value of the animation
    //@{
    Noesis::Nullable<float> GetFrom() const;
    void SetFrom(Noesis::Nullable<float> value);
    //@}

    /// Specifies the ending value of the animation
    //@{
    Noesis::Nullable<float> GetTo() const;
    void SetTo(Noesis::Nullable<float> value);
    //@}

public:
    static const Noesis::DependencyProperty* EdgeBehaviorProperty;
    static const Noesis::DependencyProperty* PowerProperty;
    static const Noesis::DependencyProperty* FromProperty;
    static const Noesis::DependencyProperty* ToProperty;

private:
    float GetCurrentValueCore(float defaultOrigin, float defaultDestination,
        Noesis::AnimationClock* clock) override;
    Noesis::Ptr<Freezable> CreateInstanceCore() const override;

private:
    NS_DECLARE_REFLECTION(ExponentialAnimation, DoubleAnimationBase)
};

}

NS_DECLARE_REFLECTION_ENUM(CustomAnimation::ExponentialAnimation::EdgeBehaviorEnum)

#endif
