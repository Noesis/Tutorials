////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "NineSliceImage.h"

#include <NsCore/ReflectionImplement.h>
#include <NsGui/UIElementData.h>
#include <NsGui/PropertyMetadata.h>
#include <NsGui/ImageSource.h>
#include <NsDrawing/Thickness.h>


using namespace NineSlice;


////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::ImageSource* NineSliceImage::GetImageSource() const
{
    return GetValue<Noesis::Ptr<Noesis::ImageSource>>(ImageSourceProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NineSliceImage::SetImageSource(Noesis::ImageSource* value)
{
    SetValue<Noesis::Ptr<Noesis::ImageSource>>(ImageSourceProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::Thickness& NineSliceImage::GetSlices() const
{
    return GetValue<Noesis::Thickness>(SlicesProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NineSliceImage::SetSlices(const Noesis::Thickness& value)
{
    SetValue<Noesis::Thickness>(SlicesProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnSlicesChanged(Noesis::DependencyObject* d, const Noesis::DependencyPropertyChangedEventArgs&)
{
    NineSliceImage* image = (NineSliceImage*)d;

    float width = 0;
    float height = 0;

    Noesis::ImageSource* imageSource = image->GetImageSource();
    if (imageSource != nullptr)
    {
        width = imageSource->GetWidth();
        height = imageSource->GetHeight();
    }

    const Noesis::Thickness& slices = image->GetSlices();

    int wl = (int)Noesis::Min(slices.left, width);
    int wc = (int)Noesis::Max(width - slices.left - slices.right, 0.0f);
    int wr = (int)Noesis::Min(slices.right, width);
    int ht = (int)Noesis::Min(slices.top, height);
    int hc = (int)Noesis::Max(height - slices.top - slices.bottom, 0.0f);
    int hb = (int)Noesis::Min(slices.bottom, height);

    image->SetValue<Noesis::Int32Rect>(NineSliceImage::TopLeftViewboxProperty, Noesis::Int32Rect(0, 0, wl, ht));
    image->SetValue<Noesis::Int32Rect>(NineSliceImage::TopCenterViewboxProperty, Noesis::Int32Rect(wl, 0, wc, ht));
    image->SetValue<Noesis::Int32Rect>(NineSliceImage::TopRightViewboxProperty, Noesis::Int32Rect(wl + wc, 0, wr, ht));

    image->SetValue<Noesis::Int32Rect>(NineSliceImage::CenterLeftViewboxProperty, Noesis::Int32Rect(0, ht, wl, hc));
    image->SetValue<Noesis::Int32Rect>(NineSliceImage::CenterViewboxProperty, Noesis::Int32Rect(wl, ht, wc, hc));
    image->SetValue<Noesis::Int32Rect>(NineSliceImage::CenterRightViewboxProperty, Noesis::Int32Rect(wl + wc, ht, wr, hc));

    image->SetValue<Noesis::Int32Rect>(NineSliceImage::BottomLeftViewboxProperty, Noesis::Int32Rect(0, ht + hc, wl, hb));
    image->SetValue<Noesis::Int32Rect>(NineSliceImage::BottomCenterViewboxProperty, Noesis::Int32Rect(wl, ht + hc, wc, hb));
    image->SetValue<Noesis::Int32Rect>(NineSliceImage::BottomRightViewboxProperty, Noesis::Int32Rect(wl + wc, ht + hc, wr, hb));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(NineSliceImage, "NineSlice.NineSliceImage")
{
    Noesis::UIElementData* data = NsMeta<Noesis::UIElementData>(Noesis::TypeOf<SelfClass>());

    data->RegisterProperty<Noesis::Ptr<Noesis::ImageSource>>(ImageSourceProperty, "ImageSource",
        Noesis::PropertyMetadata::Create(Noesis::Ptr<Noesis::ImageSource>(), OnSlicesChanged));
    data->RegisterProperty<Noesis::Thickness>(SlicesProperty, "Slices",
        Noesis::PropertyMetadata::Create(Noesis::Thickness(), OnSlicesChanged));

    data->RegisterProperty<Noesis::Int32Rect>(TopLeftViewboxProperty, "TopLeftViewbox",
        Noesis::PropertyMetadata::Create(Noesis::Int32Rect()));
    data->RegisterProperty<Noesis::Int32Rect>(TopCenterViewboxProperty, "TopCenterViewbox",
        Noesis::PropertyMetadata::Create(Noesis::Int32Rect()));
    data->RegisterProperty<Noesis::Int32Rect>(TopRightViewboxProperty, "TopRightViewbox",
        Noesis::PropertyMetadata::Create(Noesis::Int32Rect()));
    data->RegisterProperty<Noesis::Int32Rect>(CenterLeftViewboxProperty, "CenterLeftViewbox",
        Noesis::PropertyMetadata::Create(Noesis::Int32Rect()));
    data->RegisterProperty<Noesis::Int32Rect>(CenterViewboxProperty, "CenterViewbox",
        Noesis::PropertyMetadata::Create(Noesis::Int32Rect()));
    data->RegisterProperty<Noesis::Int32Rect>(CenterRightViewboxProperty, "CenterRightViewbox",
        Noesis::PropertyMetadata::Create(Noesis::Int32Rect()));
    data->RegisterProperty<Noesis::Int32Rect>(BottomLeftViewboxProperty, "BottomLeftViewbox",
        Noesis::PropertyMetadata::Create(Noesis::Int32Rect()));
    data->RegisterProperty<Noesis::Int32Rect>(BottomCenterViewboxProperty, "BottomCenterViewbox",
        Noesis::PropertyMetadata::Create(Noesis::Int32Rect()));
    data->RegisterProperty<Noesis::Int32Rect>(BottomRightViewboxProperty, "BottomRightViewbox",
        Noesis::PropertyMetadata::Create(Noesis::Int32Rect()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* NineSliceImage::ImageSourceProperty;
const Noesis::DependencyProperty* NineSliceImage::SlicesProperty;
const Noesis::DependencyProperty* NineSliceImage::TopLeftViewboxProperty;
const Noesis::DependencyProperty* NineSliceImage::TopCenterViewboxProperty;
const Noesis::DependencyProperty* NineSliceImage::TopRightViewboxProperty;
const Noesis::DependencyProperty* NineSliceImage::CenterLeftViewboxProperty;
const Noesis::DependencyProperty* NineSliceImage::CenterViewboxProperty;
const Noesis::DependencyProperty* NineSliceImage::CenterRightViewboxProperty;
const Noesis::DependencyProperty* NineSliceImage::BottomLeftViewboxProperty;
const Noesis::DependencyProperty* NineSliceImage::BottomCenterViewboxProperty;
const Noesis::DependencyProperty* NineSliceImage::BottomRightViewboxProperty;