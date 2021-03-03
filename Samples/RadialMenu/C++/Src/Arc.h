////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __RADIALMENU_ARC_H__
#define __RADIALMENU_ARC_H__


#include <NsCore/Noesis.h>
#include <NsGui/Decorator.h>


namespace Noesis
{
class Brush;
class Path;
}

namespace RadialMenu
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class Arc: public Noesis::Decorator
{
public:
    Arc();
    ~Arc();

    /// Gets or set the center X coordinate of the circle from which this arc piece is cut
    //@{
    float GetCenterX() const;
    void SetCenterX(float value);
    //@}

    /// Gets or set the center Y coordinate of the circle from which this arc piece is cut
    //@{
    float GetCenterY() const;
    void SetCenterY(float value);
    //@}

    /// Gets or sets the inner radius of this arc piece
    //@{
    float GetInnerRadius() const;
    void SetInnerRadius(float value);
    //@}

    /// Gets or set the outer radius of this arc piece
    //@{
    float GetOuterRadius() const;
    void SetOuterRadius(float value);
    //@}

    /// Gets or set the distance to translate this arc piece out from the center
    //@{
    float GetOffset() const;
    void SetOffset(float value);
    //@}

    /// Gets or sets the start angle from the Y axis vector of this arc piece in degrees
    //@{
    float GetAngleStart() const;
    void SetAngleStart(float value);
    //@}

    /// Gets or sets the angle delta from the Y axis vector of this arc piece in degrees
    //@{
    float GetAngleDelta() const;
    void SetAngleDelta(float value);
    //@}

    /// Gets or sets the padding around this arc piece
    //@{
    float GetPadding() const;
    void SetPadding(float value);
    //@}

    /// Gets or sets the brush that fills the arc
    //@{
    Noesis::Brush* GetFill() const;
    void SetFill(Noesis::Brush* value);
    //@}

    /// Gets or sets the brush used to stroke the arc
    //@{
    Noesis::Brush* GetStroke() const;
    void SetStroke(Noesis::Brush* value);
    //@}

    /// Gets or sets the thickness of the stroke applied to the arc
    //@{
    float GetStrokeThickness() const;
    void SetStrokeThickness(float value);
    //@}

public:
    static const Noesis::DependencyProperty* CenterXProperty;
    static const Noesis::DependencyProperty* CenterYProperty;
    static const Noesis::DependencyProperty* InnerRadiusProperty;
    static const Noesis::DependencyProperty* OuterRadiusProperty;
    static const Noesis::DependencyProperty* OffsetProperty;
    static const Noesis::DependencyProperty* AngleStartProperty;
    static const Noesis::DependencyProperty* AngleDeltaProperty;
    static const Noesis::DependencyProperty* PaddingProperty;
    static const Noesis::DependencyProperty* FillProperty;
    static const Noesis::DependencyProperty* StrokeProperty;
    static const Noesis::DependencyProperty* StrokeThicknessProperty;

protected:
    // From FrameworkElement
    //@{
    Noesis::Size MeasureOverride(const Noesis::Size& availableSize) override;
    //@}

private:
    void BuildArcGeometry();
    void EnsurePath();

    NS_DECLARE_REFLECTION(Arc, Noesis::Decorator)
};

}


#endif
