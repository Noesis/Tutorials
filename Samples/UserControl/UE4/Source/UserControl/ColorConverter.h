////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <NsDrawing/Color.h>

namespace UserControls
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class ColorConverter final: public Noesis::BaseMultiValueConverter
{
public:
    bool TryConvert(Noesis::ArrayRef<Noesis::BaseComponent*> values, const Noesis::Type*, Noesis::BaseComponent*,
        Noesis::Ptr<Noesis::BaseComponent>& result) override
    {
        NS_ASSERT(values.Size() == 3);
        int r = Noesis::Boxing::Unbox<int>(values[0]);
        int g = Noesis::Boxing::Unbox<int>(values[1]);
        int b = Noesis::Boxing::Unbox<int>(values[2]);

        result = Noesis::Boxing::Box(Noesis::Color(r, g, b));
        return true;
    }

    NS_IMPLEMENT_INLINE_REFLECTION_(ColorConverter, BaseMultiValueConverter,
        "UserControls.ColorConverter");
};

}
