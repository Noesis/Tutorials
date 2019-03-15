////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "MultiplierConverter.h"

#include <NsCore/ReflectionImplement.h>
#include <NsCore/TypeId.h>

#include <math.h>


using namespace Menu3D;
using namespace Noesis;


////////////////////////////////////////////////////////////////////////////////////////////////////
bool MultiplierConverter::TryConvert(BaseComponent* value, const Type* targetType,
    BaseComponent* parameter, Ptr<BaseComponent>& result)
{
    if (targetType == TypeOf<float>() && value != 0 && parameter != 0)
    {
        float input = (float)atof(value->ToString().c_str());
        float multiplier = (float)atof(parameter->ToString().c_str());
        result.Reset(Boxing::Box(input * multiplier));
        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(Menu3D::MultiplierConverter)
{
    NsMeta<TypeId>("Menu3D.MultiplierConverter");
}
