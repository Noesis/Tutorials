////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __INWORLD_PERCENTAGECONVERTER_H__
#define __INWORLD_PERCENTAGECONVERTER_H__


#include <NsCore/Noesis.h>
#include <NsGui/BaseValueConverter.h>


namespace WorldSpaceUI
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class PercentageConverter final: public Noesis::BaseValueConverter
{
public:
    bool TryConvert(Noesis::BaseComponent* value, const Noesis::Type* targetType,
        Noesis::BaseComponent* parameter, Noesis::Ptr<Noesis::BaseComponent>& result) override;

    NS_DECLARE_REFLECTION(PercentageConverter, Noesis::BaseValueConverter)
};

}


#endif
