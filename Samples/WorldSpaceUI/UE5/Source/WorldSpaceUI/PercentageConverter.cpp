////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "PercentageConverter.h"
#include "NoesisSDK.h"


using namespace WorldSpaceUI;


////////////////////////////////////////////////////////////////////////////////////////////////////
bool PercentageConverter::TryConvert(Noesis::BaseComponent* value, const Noesis::Type* targetType,
    Noesis::BaseComponent* parameter, Noesis::Ptr<Noesis::BaseComponent>& result)
{
    float f = 0.0f;
    if (Noesis::Boxing::CanUnbox<float>(value)) f = Noesis::Boxing::Unbox<float>(value);
    else if (Noesis::Boxing::CanUnbox<double>(value)) f = (float)Noesis::Boxing::Unbox<double>(value);

    float perc = Noesis::Clip(f * 100.0f, 0.0f, 100.0f);

    result = Noesis::Boxing::Box(Noesis::FixedString<64>(Noesis::FixedString<64>::VarArgs(),
        "%.0f %%", perc).Str());

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION_(PercentageConverter, "WorldSpaceUI.PercentageConverter")

NS_END_COLD_REGION