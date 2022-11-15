////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CUSTOMANIMATION_BACKANIMATION_H__
#define __CUSTOMANIMATION_BACKANIMATION_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsGui/DoubleAnimationBase.h>


namespace CustomAnimation
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class BackAnimation final: public Noesis::DoubleAnimationBase
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

    /// How much backwards motion is there in the effect
    //@{
    float GetAmplitude() const;
    void SetAmplitude(float value);
    //@}

    /// How quickly the effect drops off vs. the entire timeline
    //@{
    float GetSuppression() const;
    void SetSuppression(float value);
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
    static const Noesis::DependencyProperty* AmplitudeProperty;
    static const Noesis::DependencyProperty* SuppressionProperty;
    static const Noesis::DependencyProperty* FromProperty;
    static const Noesis::DependencyProperty* ToProperty;

private:
    float GetCurrentValueCore(float defaultOrigin, float defaultDestination,
        Noesis::AnimationClock* clock) override;
    Noesis::Ptr<Freezable> CreateInstanceCore() const override;

private:
    NS_DECLARE_REFLECTION(BackAnimation, DoubleAnimationBase)
};

}

NS_DECLARE_REFLECTION_ENUM(CustomAnimation::BackAnimation::EdgeBehaviorEnum)

#endif
