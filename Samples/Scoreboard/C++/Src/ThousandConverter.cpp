////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "ThousandConverter.h"

#include <NsCore/ReflectionImplement.h>
#include <NsCore/Boxing.h>
#include <NsCore/StringUtils.h>


using namespace Scoreboard;
using namespace Noesis;


////////////////////////////////////////////////////////////////////////////////////////////////////
bool ThousandConverter::TryConvert(BaseComponent* value, const Type* targetType,
    BaseComponent* parameter, Ptr<BaseComponent>& result)
{
    NS_UNUSED(targetType, parameter);

    if (Boxing::CanUnbox<int>(value))
    {
        char str[16];
        int v = Boxing::Unbox<int>(value);
        String::FormatBuffer(str, sizeof(str), "%.2f K", (float)v / 1000.0f);
        result = Boxing::Box(str);
        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_IMPLEMENT_REFLECTION(Scoreboard::ThousandConverter)
{
    NsMeta<TypeId>("Scoreboard.ThousandConverter");
}