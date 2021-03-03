////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __RADIALMENU_RADIALITEM_H__
#define __RADIALMENU_RADIALITEM_H__


#include <NsCore/Noesis.h>
#include <NsGui/Decorator.h>


namespace Noesis
{
}

namespace RadialMenu
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class RadialItem: public Noesis::Decorator
{
public:
    RadialItem();
    ~RadialItem();

    /// Gets or set the center X coordinate of the circle from which this element is positioned
    //@{
    float GetCenterX() const;
    void SetCenterX(float value);
    //@}

    /// Gets or set the center Y coordinate of the circle from which this element is positioned
    //@{
    float GetCenterY() const;
    void SetCenterY(float value);
    //@}

    /// Gets or set the radius where this element is positioned
    //@{
    float GetRadius() const;
    void SetRadius(float value);
    //@}

    /// Gets or set the distance to translate this element out from the center
    //@{
    float GetOffset() const;
    void SetOffset(float value);
    //@}

    /// Gets or sets the start angle from the Y axis vector of this element in degrees
    //@{
    float GetAngleStart() const;
    void SetAngleStart(float value);
    //@}

    /// Gets or sets the angle delta from the Y axis vector of this element in degrees
    //@{
    float GetAngleDelta() const;
    void SetAngleDelta(float value);
    //@}

public:
    static const Noesis::DependencyProperty* CenterXProperty;
    static const Noesis::DependencyProperty* CenterYProperty;
    static const Noesis::DependencyProperty* RadiusProperty;
    static const Noesis::DependencyProperty* OffsetProperty;
    static const Noesis::DependencyProperty* AngleStartProperty;
    static const Noesis::DependencyProperty* AngleDeltaProperty;

protected:
    // From FrameworkElement
    //@{
    Noesis::Size ArrangeOverride(const Noesis::Size& finalSize) override;
    //@}

    NS_DECLARE_REFLECTION(RadialItem, Noesis::Decorator)
};

}


#endif
