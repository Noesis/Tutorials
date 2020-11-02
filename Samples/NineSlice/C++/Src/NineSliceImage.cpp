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


using namespace Noesis;
using namespace NineSlice;


////////////////////////////////////////////////////////////////////////////////////////////////////
ImageSource* NineSliceImage::GetImageSource() const
{
    return GetValue<Ptr<ImageSource>>(ImageSourceProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NineSliceImage::SetImageSource(ImageSource* value)
{
    SetValue<Ptr<ImageSource>>(ImageSourceProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const Thickness& NineSliceImage::GetSlices() const
{
    return GetValue<Thickness>(SlicesProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NineSliceImage::SetSlices(const Thickness& value)
{
    SetValue<Thickness>(SlicesProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnSlicesChanged(DependencyObject* d, const DependencyPropertyChangedEventArgs&)
{
    NineSliceImage* image = (NineSliceImage*)d;

    float width = 0;
    float height = 0;

    ImageSource* imageSource = image->GetImageSource();
    if (imageSource != nullptr)
    {
        width = imageSource->GetWidth();
        height = imageSource->GetHeight();
    }

    const Thickness& slices = image->GetSlices();

    float wl = Min(slices.left, width);
    float wc = Max(width - slices.left - slices.right, 0.0f);
    float wr = Min(slices.right, width);
    float ht = Min(slices.top, height);
    float hc = Max(height - slices.top - slices.bottom, 0.0f);
    float hb = Min(slices.bottom, height);

    image->SetValue<Rect>(NineSliceImage::TopLeftViewboxProperty, Rect(0.0f, 0.0f, wl, ht));
    image->SetValue<Rect>(NineSliceImage::TopCenterViewboxProperty, Rect(wl, 0.0f, wl + wc, ht));
    image->SetValue<Rect>(NineSliceImage::TopRightViewboxProperty, Rect(wl + wc, 0.0f, wl + wc + wr, ht));

    image->SetValue<Rect>(NineSliceImage::CenterLeftViewboxProperty, Rect(0.0f, ht, wl, ht + hc));
    image->SetValue<Rect>(NineSliceImage::CenterViewboxProperty, Rect(wl, ht, wl + wc, ht + hc));
    image->SetValue<Rect>(NineSliceImage::CenterRightViewboxProperty, Rect(wl + wc, ht, wl + wc + wr, ht + hc));

    image->SetValue<Rect>(NineSliceImage::BottomLeftViewboxProperty, Rect(0.0f, ht + hc, wl, ht + hc + hb));
    image->SetValue<Rect>(NineSliceImage::BottomCenterViewboxProperty, Rect(wl, ht + hc, wl + wc, ht + hc + hb));
    image->SetValue<Rect>(NineSliceImage::BottomRightViewboxProperty, Rect(wl + wc, ht + hc, wl + wc + wr, ht + hc + hb));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(NineSliceImage, "NineSlice.NineSliceImage")
{
    UIElementData* data = NsMeta<UIElementData>(TypeOf<SelfClass>());

    data->RegisterProperty<Ptr<ImageSource>>(ImageSourceProperty, "ImageSource",
        PropertyMetadata::Create(Ptr<ImageSource>(), OnSlicesChanged));
    data->RegisterProperty<Thickness>(SlicesProperty, "Slices",
        PropertyMetadata::Create(Thickness(), OnSlicesChanged));

    data->RegisterProperty<Rect>(TopLeftViewboxProperty, "TopLeftViewbox",
        PropertyMetadata::Create(Rect()));
    data->RegisterProperty<Rect>(TopCenterViewboxProperty, "TopCenterViewbox",
        PropertyMetadata::Create(Rect()));
    data->RegisterProperty<Rect>(TopRightViewboxProperty, "TopRightViewbox",
        PropertyMetadata::Create(Rect()));
    data->RegisterProperty<Rect>(CenterLeftViewboxProperty, "CenterLeftViewbox",
        PropertyMetadata::Create(Rect()));
    data->RegisterProperty<Rect>(CenterViewboxProperty, "CenterViewbox",
        PropertyMetadata::Create(Rect()));
    data->RegisterProperty<Rect>(CenterRightViewboxProperty, "CenterRightViewbox",
        PropertyMetadata::Create(Rect()));
    data->RegisterProperty<Rect>(BottomLeftViewboxProperty, "BottomLeftViewbox",
        PropertyMetadata::Create(Rect()));
    data->RegisterProperty<Rect>(BottomCenterViewboxProperty, "BottomCenterViewbox",
        PropertyMetadata::Create(Rect()));
    data->RegisterProperty<Rect>(BottomRightViewboxProperty, "BottomRightViewbox",
        PropertyMetadata::Create(Rect()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const DependencyProperty* NineSliceImage::ImageSourceProperty;
const DependencyProperty* NineSliceImage::SlicesProperty;
const DependencyProperty* NineSliceImage::TopLeftViewboxProperty;
const DependencyProperty* NineSliceImage::TopCenterViewboxProperty;
const DependencyProperty* NineSliceImage::TopRightViewboxProperty;
const DependencyProperty* NineSliceImage::CenterLeftViewboxProperty;
const DependencyProperty* NineSliceImage::CenterViewboxProperty;
const DependencyProperty* NineSliceImage::CenterRightViewboxProperty;
const DependencyProperty* NineSliceImage::BottomLeftViewboxProperty;
const DependencyProperty* NineSliceImage::BottomCenterViewboxProperty;
const DependencyProperty* NineSliceImage::BottomRightViewboxProperty;