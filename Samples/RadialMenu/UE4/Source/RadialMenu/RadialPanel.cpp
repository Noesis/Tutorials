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
Noesis::Size RadialPanel::MeasureOverride(const Noesis::Size& availableSize)
{
    Noesis::Size desiredSize;

    Noesis::UIElementCollection* children = GetChildren();
    uint32_t numChildren = children->Count();

    for (uint32_t i = 0; i < numChildren; ++i)
    {
        Noesis::UIElement* child = children->Get(i);

        child->Measure(availableSize);

        const Noesis::Size& childSize = child->GetDesiredSize();
        if (desiredSize.width < childSize.width) desiredSize.width = childSize.width;
        if (desiredSize.height < childSize.height) desiredSize.height = childSize.height;
    }

    return desiredSize;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Size RadialPanel::ArrangeOverride(const Noesis::Size& finalSize)
{
    float diameter = Noesis::Min(finalSize.width, finalSize.height);
    float radius = diameter * 0.5f;

    Noesis::Point center(radius, radius);
    Noesis::Size renderSize(diameter, diameter);
    Noesis::Rect childRect(renderSize);

    Noesis::UIElementCollection* children = GetChildren();
    uint32_t numChildren = children->Count();

    float childAngleStart = GetAngleOffset();
    float childAngleDelta = GetAngle() / numChildren;

    for (uint32_t i = 0; i < numChildren; ++i)
    {
        Noesis::UIElement* child = children->Get(i);

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
    Noesis::UIElementData* data = NsMeta<Noesis::UIElementData>(Noesis::TypeOf<SelfClass>());

    data->RegisterProperty<float>(AngleProperty, "Angle",
        Noesis::FrameworkPropertyMetadata::Create(360.0f,
            Noesis::FrameworkPropertyMetadataOptions_AffectsArrange));
    data->RegisterProperty<float>(AngleOffsetProperty, "AngleOffset",
        Noesis::FrameworkPropertyMetadata::Create(0.0f,
            Noesis::FrameworkPropertyMetadataOptions_AffectsArrange));
    data->RegisterProperty<bool>(IsClockwiseProperty, "IsClockwise",
        Noesis::FrameworkPropertyMetadata::Create(true,
            Noesis::FrameworkPropertyMetadataOptions_AffectsArrange));

    data->RegisterProperty<float>(CenterXProperty, "CenterX",
        Noesis::PropertyMetadata::Create(0.0f));
    data->RegisterProperty<float>(CenterYProperty, "CenterY",
        Noesis::PropertyMetadata::Create(0.0f));
    data->RegisterProperty<float>(AngleStartProperty, "AngleStart",
        Noesis::PropertyMetadata::Create(0.0f));
    data->RegisterProperty<float>(AngleDeltaProperty, "AngleDelta",
        Noesis::PropertyMetadata::Create(0.0f));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* RadialPanel::AngleProperty;
const Noesis::DependencyProperty* RadialPanel::AngleOffsetProperty;
const Noesis::DependencyProperty* RadialPanel::IsClockwiseProperty;
const Noesis::DependencyProperty* RadialPanel::CenterXProperty;
const Noesis::DependencyProperty* RadialPanel::CenterYProperty;
const Noesis::DependencyProperty* RadialPanel::AngleStartProperty;
const Noesis::DependencyProperty* RadialPanel::AngleDeltaProperty;
