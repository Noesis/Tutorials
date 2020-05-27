////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "AnimatedNumber.h"

#include <NsGui/IntegrationAPI.h>
#include <NsGui/Storyboard.h>
#include <NsGui/Int32AnimationUsingKeyFrames.h>
#include <NsGui/LinearInt32KeyFrame.h>
#include <NsGui/FreezableCollection.h>
#include <NsGui/PropertyPath.h>
#include <NsGui/TimeSpan.h>
#include <NsGui/KeyTime.h>
#include <NsGui/UIElementData.h>
#include <NsGui/PropertyMetadata.h>
#include <NsCore/ReflectionImplement.h>


using namespace Inventory;
using namespace Noesis;


////////////////////////////////////////////////////////////////////////////////////////////////////
AnimatedNumber::AnimatedNumber()
{
    InitializeComponent();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const TimeSpan& AnimatedNumber::GetAnimationDuration() const
{
    return GetValue<TimeSpan>(AnimationDurationProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimatedNumber::SetAnimationDuration(const TimeSpan& duration)
{
    SetValue<TimeSpan>(AnimationDurationProperty, duration);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int AnimatedNumber::GetNumber() const
{
    return GetValue<int>(NumberProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimatedNumber::SetNumber(int number)
{
    SetValue<int>(NumberProperty, number);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimatedNumber::InitializeComponent()
{
    GUI::LoadComponent(this, "AnimatedNumber.xaml");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimatedNumber::OnNumberChanged(int oldValue, int newValue)
{
    Noesis::Ptr<Int32AnimationUsingKeyFrames> animation = *new Int32AnimationUsingKeyFrames();
    Storyboard::SetTargetName(animation, "Root");
    Storyboard::SetTargetProperty(animation, MakePtr<PropertyPath>(AnimatedNumberProperty));

    Int32KeyFrameCollection* keyframes = animation->GetKeyFrames();

    {
        Noesis::Ptr<LinearInt32KeyFrame> keyframe = *new LinearInt32KeyFrame();
        keyframe->SetValue(oldValue);
        keyframe->SetKeyTime(KeyTime::FromTimeSpan(TimeSpan()));
        keyframes->Add(keyframe);
    }
    {
        Noesis::Ptr<LinearInt32KeyFrame> keyframe = *new LinearInt32KeyFrame();
        keyframe->SetValue(newValue);
        keyframe->SetKeyTime(KeyTime::FromTimeSpan(GetAnimationDuration()));
        keyframes->Add(keyframe);
    }

    Noesis::Ptr<Storyboard> storyboard = *new Storyboard();
    storyboard->GetChildren()->Add(animation);
    storyboard->Begin(this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimatedNumber::OnNumberChanged(DependencyObject* d,
    const DependencyPropertyChangedEventArgs& e)
{
    int oldValue = *static_cast<const int*>(e.oldValue);
    int newValue = *static_cast<const int*>(e.newValue);
    ((AnimatedNumber*)d)->OnNumberChanged(oldValue, newValue);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(AnimatedNumber,"Inventory.AnimatedNumber")
{
    UIElementData* data = NsMeta<UIElementData>(TypeOf<SelfClass>());
    data->RegisterProperty<TimeSpan>(AnimationDurationProperty, "AnimationDuration",
        PropertyMetadata::Create(TimeSpan(0, 0, 0, 0, 500)));
    data->RegisterProperty<int>(NumberProperty, "Number",
        PropertyMetadata::Create(0, &AnimatedNumber::OnNumberChanged));
    data->RegisterProperty<int>(AnimatedNumberProperty, "AnimatedNumber",
        PropertyMetadata::Create(0));
}

const DependencyProperty* AnimatedNumber::AnimationDurationProperty;
const DependencyProperty* AnimatedNumber::NumberProperty;
const DependencyProperty* AnimatedNumber::AnimatedNumberProperty;
