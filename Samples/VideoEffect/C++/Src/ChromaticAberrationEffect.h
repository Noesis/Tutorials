////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __VIDEOEFFECT_CHROMATICABERRATIONEFFECT_H__
#define __VIDEOEFFECT_CHROMATICABERRATIONEFFECT_H__


#include <NsGui/ShaderEffect.h>


namespace Noesis { class DependencyProperty; }

namespace VideoEffect
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Creates a chromatic distortion simulating a lens failure to focus all colors to the same point
////////////////////////////////////////////////////////////////////////////////////////////////////
class ChromaticAberrationEffect final: public Noesis::ShaderEffect
{
public:
    ChromaticAberrationEffect();

    /// Gets or Sets the amount of distortion
    //@{
    float GetAmount() const;
    void SetAmount(float value);
    //@}

public:
    static const Noesis::DependencyProperty* AmountProperty;
    static void* Shader;

private:
    struct Constants
    {
        float amount = 0.0f;
    };

    Constants mConstants;

    NS_DECLARE_REFLECTION(ChromaticAberrationEffect, ShaderEffect)
};

}

#endif
