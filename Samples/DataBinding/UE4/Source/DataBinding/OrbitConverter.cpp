////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "OrbitConverter.h"


using namespace DataBinding;
using namespace Noesis;


////////////////////////////////////////////////////////////////////////////////////////////////////
bool OrbitConverter::TryConvert(BaseComponent* value, const Type* targetType,
    BaseComponent* parameter, Noesis::Ptr<BaseComponent>& result)
{
    if (Boxing::CanUnbox<float>(value) && Boxing::CanUnbox<String>(parameter))
    {
        float orbit = Boxing::Unbox<float>(value);
        float factor = (float)atof(Boxing::Unbox<String>(parameter).Str());
        result = Boxing::Box(powf(orbit / 40, 0.4f) * 770.0f * factor);
        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION_(OrbitConverter, "DataBinding.OrbitConverter")
