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

    float wl = Noesis::Min(slices.left, width);
    float wc = Noesis::Max(width - slices.left - slices.right, 0.0f);
    float wr = Noesis::Min(slices.right, width);
    float ht = Noesis::Min(slices.top, height);
    float hc = Noesis::Max(height - slices.top - slices.bottom, 0.0f);
    float hb = Noesis::Min(slices.bottom, height);

    image->SetValue<Noesis::Rect>(NineSliceImage::TopLeftViewboxProperty, Noesis::Rect(0.0f, 0.0f, wl, ht));
    image->SetValue<Noesis::Rect>(NineSliceImage::TopCenterViewboxProperty, Noesis::Rect(wl, 0.0f, wl + wc, ht));
    image->SetValue<Noesis::Rect>(NineSliceImage::TopRightViewboxProperty, Noesis::Rect(wl + wc, 0.0f, wl + wc + wr, ht));

    image->SetValue<Noesis::Rect>(NineSliceImage::CenterLeftViewboxProperty, Noesis::Rect(0.0f, ht, wl, ht + hc));
    image->SetValue<Noesis::Rect>(NineSliceImage::CenterViewboxProperty, Noesis::Rect(wl, ht, wl + wc, ht + hc));
    image->SetValue<Noesis::Rect>(NineSliceImage::CenterRightViewboxProperty, Noesis::Rect(wl + wc, ht, wl + wc + wr, ht + hc));

    image->SetValue<Noesis::Rect>(NineSliceImage::BottomLeftViewboxProperty, Noesis::Rect(0.0f, ht + hc, wl, ht + hc + hb));
    image->SetValue<Noesis::Rect>(NineSliceImage::BottomCenterViewboxProperty, Noesis::Rect(wl, ht + hc, wl + wc, ht + hc + hb));
    image->SetValue<Noesis::Rect>(NineSliceImage::BottomRightViewboxProperty, Noesis::Rect(wl + wc, ht + hc, wl + wc + wr, ht + hc + hb));
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

    data->RegisterProperty<Noesis::Rect>(TopLeftViewboxProperty, "TopLeftViewbox",
        Noesis::PropertyMetadata::Create(Noesis::Rect()));
    data->RegisterProperty<Noesis::Rect>(TopCenterViewboxProperty, "TopCenterViewbox",
        Noesis::PropertyMetadata::Create(Noesis::Rect()));
    data->RegisterProperty<Noesis::Rect>(TopRightViewboxProperty, "TopRightViewbox",
        Noesis::PropertyMetadata::Create(Noesis::Rect()));
    data->RegisterProperty<Noesis::Rect>(CenterLeftViewboxProperty, "CenterLeftViewbox",
        Noesis::PropertyMetadata::Create(Noesis::Rect()));
    data->RegisterProperty<Noesis::Rect>(CenterViewboxProperty, "CenterViewbox",
        Noesis::PropertyMetadata::Create(Noesis::Rect()));
    data->RegisterProperty<Noesis::Rect>(CenterRightViewboxProperty, "CenterRightViewbox",
        Noesis::PropertyMetadata::Create(Noesis::Rect()));
    data->RegisterProperty<Noesis::Rect>(BottomLeftViewboxProperty, "BottomLeftViewbox",
        Noesis::PropertyMetadata::Create(Noesis::Rect()));
    data->RegisterProperty<Noesis::Rect>(BottomCenterViewboxProperty, "BottomCenterViewbox",
        Noesis::PropertyMetadata::Create(Noesis::Rect()));
    data->RegisterProperty<Noesis::Rect>(BottomRightViewboxProperty, "BottomRightViewbox",
        Noesis::PropertyMetadata::Create(Noesis::Rect()));
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