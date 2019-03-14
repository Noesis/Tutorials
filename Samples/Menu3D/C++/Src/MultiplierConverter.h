////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __MENU3D_MULTIPLIERCONVERTER_H__
#define __MENU3D_MULTIPLIERCONVERTER_H__


#include <NsCore/Noesis.h>
#include <NsGui/BaseValueConverter.h>


namespace Menu3D
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class MultiplierConverter final: public Noesis::BaseValueConverter
{
public:
    bool TryConvert(Noesis::BaseComponent* value, const Noesis::Type* targetType,
        Noesis::BaseComponent* parameter, Noesis::Ptr<Noesis::BaseComponent>& result) final;

    NS_DECLARE_REFLECTION(MultiplierConverter, BaseValueConverter)
};

}


#endif
