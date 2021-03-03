////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "RadialPanel.h"

#include <NsCore/ReflectionImplement.h>
#include <NsGui/UIElementData.h>
#include <NsGui/FrameworkPropertyMetadata.h>
#include <NsGui/Brush.h>
#include <NsGui/Pen.h>
#include <NsGui/StreamGeometry.h>
#include <NsGui/StreamGeometryContext.h>
#include <NsGui/FreezableCollection.h>
#include <NsGui/UIElementCollection.h>
#include <NsGui/DrawingContext.h>


using namespace Noesis;
using namespace RadialMenu;


////////////////////////////////////////////////////////////////////////////////////////////////////
RadialPanel::RadialPanel()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
RadialPanel::~RadialPanel()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialPanel::GetAngle() const
{
    return GetValue<float>(AngleProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialPanel::SetAngle(float value)
{
    SetValue<float>(AngleProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialPanel::GetAngleOffset() const
{
    return GetValue<float>(AngleOffsetProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialPanel::SetAngleOffset(float value)
{
    SetValue<float>(AngleOffsetProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool RadialPanel::GetIsClockwise() const
{
    return GetValue<bool>(IsClockwiseProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialPanel::SetIsClockwise(bool value)
{
    SetValue<bool>(IsClockwiseProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialPanel::GetCenterX(const UIElement* child)
{
    NS_CHECK(child != nullptr, "Child is null");
    return child->GetValue<float>(CenterXProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialPanel::SetCenterX(UIElement* child, float value)
{
    NS_CHECK(child != nullptr, "Child is null");
    child->SetValue<float>(CenterXProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialPanel::GetCenterY(const UIElement* child)
{
    NS_CHECK(child != nullptr, "Child is null");
    return child->GetValue<float>(CenterYProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialPanel::SetCenterY(UIElement* child, float value)
{
    NS_CHECK(child != nullptr, "Child is null");
    child->SetValue<float>(CenterYProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialPanel::GetAngleStart(const UIElement* child)
{
    NS_CHECK(child != nullptr, "Child is null");
    return child->GetValue<float>(AngleStartProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialPanel::SetAngleStart(UIElement* child, float value)
{
    NS_CHECK(child != nullptr, "Child is null");
    child->SetValue<float>(AngleStartProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialPanel::GetAngleDelta(const UIElement* child)
{
    NS_CHECK(child != nullptr, "Child is null");
    return child->GetValue<float>(AngleDeltaProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialPanel::SetAngleDelta(UIElement* child, float value)
{
    NS_CHECK(child != nullptr, "Child is null");
    child->SetValue<float>(AngleDeltaProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Size RadialPanel::MeasureOverride(const Size& availableSize)
{
    Size desiredSize;

    UIElementCollection* children = GetChildren();
    uint32_t numChildren = children->Count();

    for (uint32_t i = 0; i < numChildren; ++i)
    {
        UIElement* child = children->Get(i);

        child->Measure(availableSize);

        const Size& childSize = child->GetDesiredSize();
        if (desiredSize.width < childSize.width) desiredSize.width = childSize.width;
        if (desiredSize.height < childSize.height) desiredSize.height = childSize.height;
    }

    return desiredSize;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Size RadialPanel::ArrangeOverride(const Size& finalSize)
{
    float diameter = Min(finalSize.width, finalSize.height);
    float radius = diameter * 0.5f;

    Point center(radius, radius);
    Size renderSize(diameter, diameter);
    Rect childRect(renderSize);

    UIElementCollection* children = GetChildren();
    uint32_t numChildren = children->Count();

    float childAngleStart = GetAngleOffset();
    float childAngleDelta = GetAngle() / numChildren;

    for (uint32_t i = 0; i < numChildren; ++i)
    {
        UIElement* child = children->Get(i);

        child->Arrange(childRect);

        SetCenterX(child, center.x);
        SetCenterY(child, center.y);
        SetAngleStart(child, childAngleStart);
        SetAngleDelta(child, childAngleDelta);

        childAngleStart += childAngleDelta;
    }

    return renderSize;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(RadialPanel, "RadialMenu.RadialPanel")
{
    UIElementData* data = NsMeta<UIElementData>(TypeOf<SelfClass>());

    data->RegisterProperty<float>(AngleProperty, "Angle",
        FrameworkPropertyMetadata::Create(360.0f, FrameworkPropertyMetadataOptions_AffectsArrange));
    data->RegisterProperty<float>(AngleOffsetProperty, "AngleOffset",
        FrameworkPropertyMetadata::Create(0.0f, FrameworkPropertyMetadataOptions_AffectsArrange));
    data->RegisterProperty<bool>(IsClockwiseProperty, "IsClockwise",
        FrameworkPropertyMetadata::Create(true, FrameworkPropertyMetadataOptions_AffectsArrange));

    data->RegisterProperty<float>(CenterXProperty, "CenterX", PropertyMetadata::Create(0.0f));
    data->RegisterProperty<float>(CenterYProperty, "CenterY", PropertyMetadata::Create(0.0f));
    data->RegisterProperty<float>(AngleStartProperty, "AngleStart", PropertyMetadata::Create(0.0f));
    data->RegisterProperty<float>(AngleDeltaProperty, "AngleDelta", PropertyMetadata::Create(0.0f));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const DependencyProperty* RadialPanel::AngleProperty;
const DependencyProperty* RadialPanel::AngleOffsetProperty;
const DependencyProperty* RadialPanel::IsClockwiseProperty;
const DependencyProperty* RadialPanel::CenterXProperty;
const DependencyProperty* RadialPanel::CenterYProperty;
const DependencyProperty* RadialPanel::AngleStartProperty;
const DependencyProperty* RadialPanel::AngleDeltaProperty;
