////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "ChromaticAberrationEffect.h"

#include <NsCore/ReflectionImplement.h>
#include <NsGui/UIElementData.h>
#include <NsGui/UIPropertyMetadata.h>
#include <NsRender/RenderContext.h>
#include <NsRender/RenderDevice.h>

#ifdef NS_PLATFORM_WINDOWS_DESKTOP
typedef unsigned char BYTE;
#include "ChromaticAberration.h"
#endif


using namespace Noesis;
using namespace NoesisApp;
using namespace VideoEffect;

////////////////////////////////////////////////////////////////////////////////////////////////////
ChromaticAberrationEffect::ChromaticAberrationEffect()
{
    if (Shader == nullptr)
    {
        ShaderSource shader = { "Noesis_ChromaticAberrationEffect", Shader::Custom_Effect };

    #if defined(NS_PLATFORM_WINDOWS_DESKTOP)
        shader.hlsl = ChromaticAberration;
    #endif

        RenderContext* context = RenderContext::Current();
        Shader = context->CreatePixelShader(shader);
    }

    SetPixelShader(Shader);
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
void* ChromaticAberrationEffect::Shader;
