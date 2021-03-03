////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "RadialItem.h"

#include <NsCore/ReflectionImplement.h>
#include <NsGui/UIElementData.h>
#include <NsGui/FrameworkPropertyMetadata.h>


using namespace Noesis;
using namespace RadialMenu;


////////////////////////////////////////////////////////////////////////////////////////////////////
RadialItem::RadialItem()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
RadialItem::~RadialItem()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialItem::GetCenterX() const
{
    return GetValue<float>(CenterXProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialItem::SetCenterX(float value)
{
    SetValue<float>(CenterXProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialItem::GetCenterY() const
{
    return GetValue<float>(CenterYProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialItem::SetCenterY(float value)
{
    SetValue<float>(CenterYProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialItem::GetRadius() const
{
    return GetValue<float>(RadiusProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialItem::SetRadius(float value)
{
    SetValue<float>(RadiusProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialItem::GetOffset() const
{
    return GetValue<float>(OffsetProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialItem::SetOffset(float value)
{
    SetValue<float>(OffsetProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialItem::GetAngleStart() const
{
    return GetValue<float>(AngleStartProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialItem::SetAngleStart(float value)
{
    SetValue<float>(AngleStartProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialItem::GetAngleDelta() const
{
    return GetValue<float>(AngleDeltaProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialItem::SetAngleDelta(float value)
{
    SetValue<float>(AngleDeltaProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static Point RadialPoint(const Point& center, float angle, float radius)
{
    float radiansAngle = (angle - 90.0f) * DegToRad;
    float x = radius * cosf(radiansAngle);
    float y = radius * sinf(radiansAngle);
    return Point(center.x + x, center.y + y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Size RadialItem::ArrangeOverride(const Size& finalSize)
{
    UIElement* child = GetChild();
    if (child != nullptr)
    {
        float angleStart = GetAngleStart();
        float angleDelta = GetAngleDelta();
        float radius = GetRadius();
        Point center(GetCenterX(), GetCenterY());
        Point point = RadialPoint(center, angleStart + angleDelta * 0.5f, radius);

        const Size& childSize = child->GetDesiredSize();
        float halfChildWidth = childSize.width / 2.0f;
        float halfChildHeight = childSize.height / 2.0f;

        Point p0(point.x - halfChildWidth, point.y - halfChildHeight);
        Point p1(point.x + halfChildWidth, point.y + halfChildHeight);
        Rect childRect;
        childRect.SetLocation(p0);
        childRect.Expand(p1);

        child->Arrange(childRect);
    }

    return finalSize;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(RadialItem, "RadialMenu.RadialItem")
{
    UIElementData* data = NsMeta<UIElementData>(TypeOf<SelfClass>());

    data->RegisterProperty<float>(CenterXProperty, "CenterX",
        FrameworkPropertyMetadata::Create(0.0f,
            FrameworkPropertyMetadataOptions_AffectsArrange));
    data->RegisterProperty<float>(CenterYProperty, "CenterY",
        FrameworkPropertyMetadata::Create(0.0f,
            FrameworkPropertyMetadataOptions_AffectsArrange));
    data->RegisterProperty<float>(RadiusProperty, "Radius",
        FrameworkPropertyMetadata::Create(0.0f,
            FrameworkPropertyMetadataOptions_AffectsArrange));
    data->RegisterProperty<float>(OffsetProperty, "Offset",
        FrameworkPropertyMetadata::Create(0.0f,
            FrameworkPropertyMetadataOptions_AffectsArrange));
    data->RegisterProperty<float>(AngleStartProperty, "AngleStart",
        FrameworkPropertyMetadata::Create(0.0f,
            FrameworkPropertyMetadataOptions_AffectsArrange));
    data->RegisterProperty<float>(AngleDeltaProperty, "AngleDelta",
        FrameworkPropertyMetadata::Create(0.0f,
            FrameworkPropertyMetadataOptions_AffectsArrange));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const DependencyProperty* RadialItem::CenterXProperty;
const DependencyProperty* RadialItem::CenterYProperty;
const DependencyProperty* RadialItem::RadiusProperty;
const DependencyProperty* RadialItem::OffsetProperty;
const DependencyProperty* RadialItem::AngleStartProperty;
const DependencyProperty* RadialItem::AngleDeltaProperty;
