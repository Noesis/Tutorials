////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __SCOREBOARD_THOUSANDCONVERTER_H__
#define __SCOREBOARD_THOUSANDCONVERTER_H__


#include <NsCore/Noesis.h>
#include <NsGui/BaseValueConverter.h>


namespace Scoreboard
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class ThousandConverter final: public Noesis::BaseValueConverter
{
public:
    /// From IValueConverter
    //@{
    bool TryConvert(Noesis::BaseComponent* value, const Noesis::Type* targetType,
        Noesis::BaseComponent* parameter, Noesis::Ptr<Noesis::BaseComponent>& result) override;
    //@}

private:
    NS_DECLARE_REFLECTION(ThousandConverter, BaseValueConverter)
};

}


#endif
