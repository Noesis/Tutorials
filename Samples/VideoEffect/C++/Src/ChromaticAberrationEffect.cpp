////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "ChromaticAberrationEffect.h"

#include <NsCore/ReflectionImplement.h>
#include <NsGui/UIElementData.h>
#include <NsGui/UIPropertyMetadata.h>

#ifdef HAVE_CUSTOM_SHADERS
#include "ChromaticAberration.bin.h"
#endif


using namespace Noesis;
using namespace NoesisApp;
using namespace VideoEffect;

////////////////////////////////////////////////////////////////////////////////////////////////////
ChromaticAberrationEffect::ChromaticAberrationEffect()
{
  #ifdef HAVE_CUSTOM_SHADERS
    RenderContext::EnsureShaders(Shaders, "ChromaticAberration", ChromaticAberration_bin);
  #endif

    SetPixelShader(Shaders.shaders[0]);
    SetConstantBuffer(&mConstants, sizeof(mConstants));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float ChromaticAberrationEffect::GetAmount() const
{
    return GetValue<float>(AmountProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ChromaticAberrationEffect::SetAmount(float value)
{
    SetValue<float>(AmountProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(ChromaticAberrationEffect, "VideoEffect.ChromaticAberrationEffect")
{
    auto OnAmountChanged = [](DependencyObject* o, const DependencyPropertyChangedEventArgs& args)
    {
        ChromaticAberrationEffect* this_ = (ChromaticAberrationEffect*)o;
        this_->mConstants.amount = args.NewValue<float>();
        this_->InvalidateConstantBuffer();
    };

    UIElementData* data = NsMeta<UIElementData>(TypeOf<SelfClass>());
    data->RegisterProperty<float>(AmountProperty, "Amount", UIPropertyMetadata::Create(
        0.0f, PropertyChangedCallback(OnAmountChanged)));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const DependencyProperty* ChromaticAberrationEffect::AmountProperty;
EffectShaders ChromaticAberrationEffect::Shaders;
