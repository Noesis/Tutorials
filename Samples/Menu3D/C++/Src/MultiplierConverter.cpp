////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "MultiplierConverter.h"

#include <NsCore/ReflectionImplementEmpty.h>
#include <NsCore/String.h>
#include <NsCore/TypeOf.h>
#include <NsCore/Boxing.h>

#include <math.h>


using namespace Menu3D;
using namespace Noesis;


////////////////////////////////////////////////////////////////////////////////////////////////////
bool MultiplierConverter::TryConvert(BaseComponent* value, const Type* targetType,
    BaseComponent* parameter, Ptr<BaseComponent>& result)
{
    if (targetType == TypeOf<float>() && value != 0 && parameter != 0)
    {
        float input = (float)atof(value->ToString().Str());
        float multiplier = (float)atof(parameter->ToString().Str());
        result.Reset(Boxing::Box(input * multiplier));
        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION_(Menu3D::MultiplierConverter, "Menu3D.MultiplierConverter")

NS_END_COLD_REGION
