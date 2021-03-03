////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "Arc.h"

#include <NsCore/ReflectionImplement.h>
#include <NsGui/UIElementData.h>
#include <NsGui/FrameworkPropertyMetadata.h>
#include <NsGui/Brush.h>
#include <NsGui/Path.h>
#include <NsGui/StreamGeometry.h>
#include <NsGui/StreamGeometryContext.h>
#include <NsGui/Binding.h>


using namespace Noesis;
using namespace RadialMenu;


////////////////////////////////////////////////////////////////////////////////////////////////////
Arc::Arc()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Arc::~Arc()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float Arc::GetCenterX() const
{
    return GetValue<float>(CenterXProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Arc::SetCenterX(float value)
{
    SetValue<float>(CenterXProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float Arc::GetCenterY() const
{
    return GetValue<float>(CenterYProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Arc::SetCenterY(float value)
{
    SetValue<float>(CenterYProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float Arc::GetInnerRadius() const
{
    return GetValue<float>(InnerRadiusProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Arc::SetInnerRadius(float value)
{
    SetValue<float>(InnerRadiusProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float Arc::GetOuterRadius() const
{
    return GetValue<float>(OuterRadiusProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Arc::SetOuterRadius(float value)
{
    SetValue<float>(OuterRadiusProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float Arc::GetOffset() const
{
    return GetValue<float>(OffsetProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Arc::SetOffset(float value)
{
    SetValue<float>(OffsetProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float Arc::GetAngleStart() const
{
    return GetValue<float>(AngleStartProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Arc::SetAngleStart(float value)
{
    SetValue<float>(AngleStartProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float Arc::GetAngleDelta() const
{
    return GetValue<float>(AngleDeltaProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Arc::SetAngleDelta(float value)
{
    SetValue<float>(AngleDeltaProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float Arc::GetPadding() const
{
    return GetValue<float>(PaddingProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Arc::SetPadding(float value)
{
    SetValue<float>(PaddingProperty, value);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
Brush* Arc::GetFill() const
{
    return GetValue<Ptr<Brush>>(FillProperty);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Arc::SetFill(Brush* value)
{
    SetValue<Ptr<Brush>>(FillProperty, value);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
Brush* Arc::GetStroke() const
{
    return GetValue<Ptr<Brush>>(StrokeProperty);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Arc::SetStroke(Brush* value)
{
    SetValue<Ptr<Brush>>(StrokeProperty, value);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
float Arc::GetStrokeThickness() const
{
    return GetValue<float>(StrokeThicknessProperty);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Arc::SetStrokeThickness(float value)
{
    SetValue<float>(StrokeThicknessProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Size Arc::MeasureOverride(const Size& availableSize)
{
    BuildArcGeometry();
    return ParentClass::MeasureOverride(availableSize);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static Point RadialPoint(Point center, float angle, float radius)
{
    float radiansAngle = (angle - 90.0f) * DegToRad;
    float x = radius * cosf(radiansAngle);
    float y = radius * sinf(radiansAngle);
    return Point(x + center.x, y + center.y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Arc::BuildArcGeometry()
{
    EnsurePath();

    Path* path = (Path*)GetChild();
    StreamGeometry* geometry = (StreamGeometry*)path->GetData();
    StreamGeometryContext geo = geometry->Open();

    float angleDelta = GetAngleDelta();
    float outerRadius = GetOuterRadius();
    float innerRadius = GetInnerRadius();
    if (angleDelta > 0 && fabsf(outerRadius - innerRadius) > FLT_EPSILON)
    {
        float angleStart = GetAngleStart();
        float outerStartAngle = angleStart;
        float outerAngleDelta = angleDelta;
        float innerStartAngle = angleStart;
        float innerAngleDelta = angleDelta;
        float offset = GetOffset();
        float padding = GetPadding();
        Point center(GetCenterX(), GetCenterY());
        Size outerSize(outerRadius, outerRadius);
        Size innerSize(innerRadius, innerRadius);

        // If we have to draw a full-circle, we do it with two semi-circles, because 'ArcTo()' can
        // not draw a full-circle
        if (angleDelta >= 360.0f && padding <= 0.0f)
        {
            Point outerTop = RadialPoint(center, outerStartAngle, outerRadius + offset);
            Point outerBottom = RadialPoint(center, outerStartAngle + 180.0f, outerRadius + offset);
            Point innerTop = RadialPoint(center, innerStartAngle, innerRadius + offset);
            Point innerBottom = RadialPoint(center, innerStartAngle + 180.0f, innerRadius + offset);

            geo.BeginFigure(innerTop, true);
            geo.LineTo(outerTop);
            geo.ArcTo(outerBottom, outerSize, 0.0f, false, SweepDirection_Clockwise);
            geo.ArcTo(outerTop, outerSize, 0.0f, false, SweepDirection_Clockwise);
            geo.LineTo(innerTop);
            geo.ArcTo(innerBottom, innerSize, 0.0f, false, SweepDirection_Counterclockwise);
            geo.ArcTo(innerTop, innerSize, 0.0f, false, SweepDirection_Counterclockwise);
        }
        else
        {
            if (padding > FLT_EPSILON)
            {
                // Offsets the angle by the padding
                float outerAngleVariation = (180.0f * (padding / outerRadius)) / Pi;
                float innerAngleVariation = (180.0f * (padding / innerRadius)) / Pi;

                outerStartAngle += outerAngleVariation;
                outerAngleDelta -= outerAngleVariation * 2.0f;
                innerStartAngle += innerAngleVariation;
                innerAngleDelta -= innerAngleVariation * 2.0f;
            }

            Point outerStart = RadialPoint(center, outerStartAngle, outerRadius + offset);
            Point outerEnd = RadialPoint(center, outerStartAngle + outerAngleDelta, outerRadius + offset);
            Point innerStart = RadialPoint(center, innerStartAngle, innerRadius + offset);
            Point innerEnd = RadialPoint(center, innerStartAngle + innerAngleDelta, innerRadius + offset);

            bool largeArcOuter = outerAngleDelta > 180.0f;
            bool largeArcInner = innerAngleDelta > 180.0f;

            geo.BeginFigure(innerStart, true);
            geo.LineTo(outerStart);
            geo.ArcTo(outerEnd, outerSize, 0.0f, largeArcOuter, SweepDirection_Clockwise);
            geo.LineTo(innerEnd);
            geo.ArcTo(innerStart, innerSize, 0.0f, largeArcInner, SweepDirection_Counterclockwise);
        }
    }

    geo.Close();

    path->InvalidateMeasure();
    path->InvalidateVisual();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Arc::EnsurePath()
{
    if (GetChild() == nullptr)
    {
        Ptr<StreamGeometry> geometry = *new StreamGeometry();
        geometry->SetFillRule(FillRule_EvenOdd);

        Ptr<Path> path = *new Path();
        path->SetData(geometry);

        path->SetBinding(Shape::FillProperty, MakePtr<Binding>(FillProperty, this));
        path->SetBinding(Shape::StrokeProperty, MakePtr<Binding>(StrokeProperty, this));
        path->SetBinding(Shape::StrokeThicknessProperty, MakePtr<Binding>(StrokeThicknessProperty,
            this));

        SetChild(path);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(Arc, "RadialMenu.Arc")
{
    UIElementData* data = NsMeta<UIElementData>(TypeOf<SelfClass>());

    auto onShapePropertyChanged = [](DependencyObject* d, const DependencyPropertyChangedEventArgs&)
    {
        ((Arc*)d)->InvalidateMeasure();
    };

    data->RegisterProperty<float>(CenterXProperty, "CenterX",
        FrameworkPropertyMetadata::Create(0.0f, PropertyChangedCallback(onShapePropertyChanged)));
    data->RegisterProperty<float>(CenterYProperty, "CenterY",
        FrameworkPropertyMetadata::Create(0.0f, PropertyChangedCallback(onShapePropertyChanged)));
    data->RegisterProperty<float>(InnerRadiusProperty, "InnerRadius",
        FrameworkPropertyMetadata::Create(0.0f, PropertyChangedCallback(onShapePropertyChanged)));
    data->RegisterProperty<float>(OuterRadiusProperty, "OuterRadius",
        FrameworkPropertyMetadata::Create(0.0f, PropertyChangedCallback(onShapePropertyChanged)));
    data->RegisterProperty<float>(OffsetProperty, "Offset",
        FrameworkPropertyMetadata::Create(0.0f, PropertyChangedCallback(onShapePropertyChanged)));
    data->RegisterProperty<float>(AngleStartProperty, "AngleStart",
        FrameworkPropertyMetadata::Create(0.0f, PropertyChangedCallback(onShapePropertyChanged)));
    data->RegisterProperty<float>(AngleDeltaProperty, "AngleDelta",
        FrameworkPropertyMetadata::Create(0.0f, PropertyChangedCallback(onShapePropertyChanged)));
    data->RegisterProperty<float>(PaddingProperty, "Padding",
        FrameworkPropertyMetadata::Create(0.0f, PropertyChangedCallback(onShapePropertyChanged)));
    data->RegisterProperty<Ptr<Brush>>(FillProperty, "Fill",
        FrameworkPropertyMetadata::Create(Ptr<Brush>()));
    data->RegisterProperty<Ptr<Brush>>(StrokeProperty, "Stroke",
        FrameworkPropertyMetadata::Create(Ptr<Brush>()));
    data->RegisterProperty<float>(StrokeThicknessProperty, "StrokeThickness",
        FrameworkPropertyMetadata::Create(1.0f));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const DependencyProperty* Arc::CenterXProperty;
const DependencyProperty* Arc::CenterYProperty;
const DependencyProperty* Arc::InnerRadiusProperty;
const DependencyProperty* Arc::OuterRadiusProperty;
const DependencyProperty* Arc::OffsetProperty;
const DependencyProperty* Arc::AngleStartProperty;
const DependencyProperty* Arc::AngleDeltaProperty;
const DependencyProperty* Arc::PaddingProperty;
const DependencyProperty* Arc::FillProperty;
const DependencyProperty* Arc::StrokeProperty;
const DependencyProperty* Arc::StrokeThicknessProperty;

