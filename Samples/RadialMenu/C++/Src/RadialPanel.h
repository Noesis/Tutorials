////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __RADIALMENU_RADIALPANEL_H__
#define __RADIALMENU_RADIALPANEL_H__


#include <NsCore/Noesis.h>
#include <NsGui/Panel.h>


namespace Noesis
{
class Brush;
class Pen;
class StreamGeometry;
}

namespace RadialMenu
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class RadialPanel: public Noesis::Panel
{
public:
    RadialPanel();
    ~RadialPanel();

    /// Gets or sets the arc angle covered by the children. A value between 0 and 360 degrees
    //@{
    float GetAngle() const;
    void SetAngle(float value);
    //@}

    /// Gets or sets the angle offset where children start to be positioned
    //@{
    float GetAngleOffset() const;
    void SetAngleOffset(float value);
    //@}

    /// Gets or sets a value that indicates if children are positioned clockwise
    //@{
    bool GetIsClockwise() const;
    void SetIsClockwise(bool value);
    //@}

    /// Gets center X-coordinate for the specified child
    static float GetCenterX(const Noesis::UIElement* child);
    /// Sets center X-coordinate for the specified child
    static void SetCenterX(Noesis::UIElement* child, float value);

    /// Gets center Y-coordinate for the specified child
    static float GetCenterY(const Noesis::UIElement* child);
    /// Sets center Y-coordinate for the specified child
    static void SetCenterY(Noesis::UIElement* child, float value);

    /// Gets angle start for the specified child
    static float GetAngleStart(const Noesis::UIElement* child);
    /// Sets angle start in the specified child
    static void SetAngleStart(Noesis::UIElement* child, float value);

    /// Gets angle delta for the specified child
    static float GetAngleDelta(const Noesis::UIElement* child);
    /// Sets angle delta in the specified child
    static void SetAngleDelta(Noesis::UIElement* child, float value);

public:
    static const Noesis::DependencyProperty* AngleProperty;
    static const Noesis::DependencyProperty* AngleOffsetProperty;
    static const Noesis::DependencyProperty* IsClockwiseProperty;
    static const Noesis::DependencyProperty* CenterXProperty; // attached
    static const Noesis::DependencyProperty* CenterYProperty; // attached
    static const Noesis::DependencyProperty* AngleStartProperty; // attached
    static const Noesis::DependencyProperty* AngleDeltaProperty; // attached

protected:
    // From FrameworkElement
    //@{
    Noesis::Size MeasureOverride(const Noesis::Size& availableSize) override;
    Noesis::Size ArrangeOverride(const Noesis::Size& finalSize) override;
    //@}

    NS_DECLARE_REFLECTION(RadialPanel, Noesis::Panel)
};

}


#endif
