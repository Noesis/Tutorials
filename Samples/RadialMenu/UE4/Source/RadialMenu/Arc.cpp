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
Noesis::Brush* Arc::GetFill() const
{
    return GetValue<Noesis::Ptr<Noesis::Brush>>(FillProperty);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Arc::SetFill(Noesis::Brush* value)
{
    SetValue<Noesis::Ptr<Noesis::Brush>>(FillProperty, value);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Brush* Arc::GetStroke() const
{
    return GetValue<Noesis::Ptr<Noesis::Brush>>(StrokeProperty);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Arc::SetStroke(Noesis::Brush* value)
{
    SetValue<Noesis::Ptr<Noesis::Brush>>(StrokeProperty, value);
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
Noesis::Size Arc::MeasureOverride(const Noesis::Size& availableSize)
{
    BuildArcGeometry();
    return ParentClass::MeasureOverride(availableSize);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static Noesis::Point RadialPoint(Noesis::Point center, float angle, float radius)
{
    float radiansAngle = (angle - 90.0f) * Noesis::DegToRad;
    float x = radius * cosf(radiansAngle);
    float y = radius * sinf(radiansAngle);
    return Noesis::Point(x + center.x, y + center.y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Arc::BuildArcGeometry()
{
    EnsurePath();

    Noesis::Path* path = (Noesis::Path*)GetChild();
    Noesis::StreamGeometry* geometry = (Noesis::StreamGeometry*)path->GetData();
    Noesis::StreamGeometryContext geo = geometry->Open();

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
        Noesis::Point center(GetCenterX(), GetCenterY());
        Noesis::Size outerSize(outerRadius, outerRadius);
        Noesis::Size innerSize(innerRadius, innerRadius);

        // If we have to draw a full-circle, we do it with two semi-circles, because 'ArcTo()' can
        // not draw a full-circle
        if (angleDelta >= 360.0f && padding <= 0.0f)
        {
            Noesis::Point outerTop = RadialPoint(center, outerStartAngle, outerRadius + offset);
            Noesis::Point outerBottom = RadialPoint(center, outerStartAngle + 180.0f, outerRadius + offset);
            Noesis::Point innerTop = RadialPoint(center, innerStartAngle, innerRadius + offset);
            Noesis::Point innerBottom = RadialPoint(center, innerStartAngle + 180.0f, innerRadius + offset);

            geo.BeginFigure(innerTop, true);
            geo.LineTo(outerTop);
            geo.ArcTo(outerBottom, outerSize, 0.0f, false, Noesis::SweepDirection_Clockwise);
            geo.ArcTo(outerTop, outerSize, 0.0f, false, Noesis::SweepDirection_Clockwise);
            geo.LineTo(innerTop);
            geo.ArcTo(innerBottom, innerSize, 0.0f, false, Noesis::SweepDirection_Counterclockwise);
            geo.ArcTo(innerTop, innerSize, 0.0f, false, Noesis::SweepDirection_Counterclockwise);
        }
        else
        {
            if (padding > FLT_EPSILON)
            {
                // Offsets the angle by the padding
                float outerAngleVariation = (180.0f * (padding / outerRadius)) / Noesis::Pi;
                float innerAngleVariation = (180.0f * (padding / innerRadius)) / Noesis::Pi;

                outerStartAngle += outerAngleVariation;
                outerAngleDelta -= outerAngleVariation * 2.0f;
                innerStartAngle += innerAngleVariation;
                innerAngleDelta -= innerAngleVariation * 2.0f;
            }

            Noesis::Point outerStart = RadialPoint(center, outerStartAngle, outerRadius + offset);
            Noesis::Point outerEnd = RadialPoint(center, outerStartAngle + outerAngleDelta, outerRadius + offset);
            Noesis::Point innerStart = RadialPoint(center, innerStartAngle, innerRadius + offset);
            Noesis::Point innerEnd = RadialPoint(center, innerStartAngle + innerAngleDelta, innerRadius + offset);

            bool largeArcOuter = outerAngleDelta > 180.0f;
            bool largeArcInner = innerAngleDelta > 180.0f;

            geo.BeginFigure(innerStart, true);
            geo.LineTo(outerStart);
            geo.ArcTo(outerEnd, outerSize, 0.0f, largeArcOuter, Noesis::SweepDirection_Clockwise);
            geo.LineTo(innerEnd);
            geo.ArcTo(innerStart, innerSize, 0.0f, largeArcInner, Noesis::SweepDirection_Counterclockwise);
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
        Noesis::Ptr<Noesis::StreamGeometry> geometry = *new Noesis::StreamGeometry();
        geometry->SetFillRule(Noesis::FillRule_EvenOdd);

        Noesis::Ptr<Noesis::Path> path = *new Noesis::Path();
        path->SetData(geometry);

        path->SetBinding(Noesis::Shape::FillProperty, Noesis::MakePtr<Noesis::Binding>(FillProperty, this));
        path->SetBinding(Noesis::Shape::StrokeProperty, Noesis::MakePtr<Noesis::Binding>(StrokeProperty, this));
        path->SetBinding(Noesis::Shape::StrokeThicknessProperty, Noesis::MakePtr<Noesis::Binding>(StrokeThicknessProperty,
            this));

        SetChild(path);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(Arc, "RadialMenu.Arc")
{
    Noesis::UIElementData* data = NsMeta<Noesis::UIElementData>(Noesis::TypeOf<SelfClass>());

    auto onShapePropertyChanged = [](Noesis::DependencyObject* d, const Noesis::DependencyPropertyChangedEventArgs&)
    {
        ((Arc*)d)->InvalidateMeasure();
    };

    data->RegisterProperty<float>(CenterXProperty, "CenterX",
        Noesis::FrameworkPropertyMetadata::Create(0.0f, Noesis::PropertyChangedCallback(onShapePropertyChanged)));
    data->RegisterProperty<float>(CenterYProperty, "CenterY",
        Noesis::FrameworkPropertyMetadata::Create(0.0f, Noesis::PropertyChangedCallback(onShapePropertyChanged)));
    data->RegisterProperty<float>(InnerRadiusProperty, "InnerRadius",
        Noesis::FrameworkPropertyMetadata::Create(0.0f, Noesis::PropertyChangedCallback(onShapePropertyChanged)));
    data->RegisterProperty<float>(OuterRadiusProperty, "OuterRadius",
        Noesis::FrameworkPropertyMetadata::Create(0.0f, Noesis::PropertyChangedCallback(onShapePropertyChanged)));
    data->RegisterProperty<float>(OffsetProperty, "Offset",
        Noesis::FrameworkPropertyMetadata::Create(0.0f, Noesis::PropertyChangedCallback(onShapePropertyChanged)));
    data->RegisterProperty<float>(AngleStartProperty, "AngleStart",
        Noesis::FrameworkPropertyMetadata::Create(0.0f, Noesis::PropertyChangedCallback(onShapePropertyChanged)));
    data->RegisterProperty<float>(AngleDeltaProperty, "AngleDelta",
        Noesis::FrameworkPropertyMetadata::Create(0.0f, Noesis::PropertyChangedCallback(onShapePropertyChanged)));
    data->RegisterProperty<float>(PaddingProperty, "Padding",
        Noesis::FrameworkPropertyMetadata::Create(0.0f, Noesis::PropertyChangedCallback(onShapePropertyChanged)));
    data->RegisterProperty<Noesis::Ptr<Noesis::Brush>>(FillProperty, "Fill",
        Noesis::FrameworkPropertyMetadata::Create(Noesis::Ptr<Noesis::Brush>()));
    data->RegisterProperty<Noesis::Ptr<Noesis::Brush>>(StrokeProperty, "Stroke",
        Noesis::FrameworkPropertyMetadata::Create(Noesis::Ptr<Noesis::Brush>()));
    data->RegisterProperty<float>(StrokeThicknessProperty, "StrokeThickness",
        Noesis::FrameworkPropertyMetadata::Create(1.0f));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* Arc::CenterXProperty;
const Noesis::DependencyProperty* Arc::CenterYProperty;
const Noesis::DependencyProperty* Arc::InnerRadiusProperty;
const Noesis::DependencyProperty* Arc::OuterRadiusProperty;
const Noesis::DependencyProperty* Arc::OffsetProperty;
const Noesis::DependencyProperty* Arc::AngleStartProperty;
const Noesis::DependencyProperty* Arc::AngleDeltaProperty;
const Noesis::DependencyProperty* Arc::PaddingProperty;
const Noesis::DependencyProperty* Arc::FillProperty;
const Noesis::DependencyProperty* Arc::StrokeProperty;
const Noesis::DependencyProperty* Arc::StrokeThicknessProperty;

