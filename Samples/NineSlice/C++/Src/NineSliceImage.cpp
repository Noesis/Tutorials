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
#include <NsDrawing/Int32Rect.h>


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

    int wl = (int)Min(slices.left, width);
    int wc = (int)Max(width - slices.left - slices.right, 0.0f);
    int wr = (int)Min(slices.right, width);
    int ht = (int)Min(slices.top, height);
    int hc = (int)Max(height - slices.top - slices.bottom, 0.0f);
    int hb = (int)Min(slices.bottom, height);

    image->SetValue<Int32Rect>(NineSliceImage::TopLeftViewboxProperty, Int32Rect(0, 0, wl, ht));
    image->SetValue<Int32Rect>(NineSliceImage::TopCenterViewboxProperty, Int32Rect(wl, 0, wc, ht));
    image->SetValue<Int32Rect>(NineSliceImage::TopRightViewboxProperty, Int32Rect(wl + wc, 0, wr, ht));

    image->SetValue<Int32Rect>(NineSliceImage::CenterLeftViewboxProperty, Int32Rect(0, ht, wl, hc));
    image->SetValue<Int32Rect>(NineSliceImage::CenterViewboxProperty, Int32Rect(wl, ht, wc, hc));
    image->SetValue<Int32Rect>(NineSliceImage::CenterRightViewboxProperty, Int32Rect(wl + wc, ht, wr, hc));

    image->SetValue<Int32Rect>(NineSliceImage::BottomLeftViewboxProperty, Int32Rect(0, ht + hc, wl, hb));
    image->SetValue<Int32Rect>(NineSliceImage::BottomCenterViewboxProperty, Int32Rect(wl, ht + hc, wc, hb));
    image->SetValue<Int32Rect>(NineSliceImage::BottomRightViewboxProperty, Int32Rect(wl + wc, ht + hc, wr, hb));
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

    data->RegisterProperty<Int32Rect>(TopLeftViewboxProperty, "TopLeftViewbox",
        PropertyMetadata::Create(Int32Rect()));
    data->RegisterProperty<Int32Rect>(TopCenterViewboxProperty, "TopCenterViewbox",
        PropertyMetadata::Create(Int32Rect()));
    data->RegisterProperty<Int32Rect>(TopRightViewboxProperty, "TopRightViewbox",
        PropertyMetadata::Create(Int32Rect()));
    data->RegisterProperty<Int32Rect>(CenterLeftViewboxProperty, "CenterLeftViewbox",
        PropertyMetadata::Create(Int32Rect()));
    data->RegisterProperty<Int32Rect>(CenterViewboxProperty, "CenterViewbox",
        PropertyMetadata::Create(Int32Rect()));
    data->RegisterProperty<Int32Rect>(CenterRightViewboxProperty, "CenterRightViewbox",
        PropertyMetadata::Create(Int32Rect()));
    data->RegisterProperty<Int32Rect>(BottomLeftViewboxProperty, "BottomLeftViewbox",
        PropertyMetadata::Create(Int32Rect()));
    data->RegisterProperty<Int32Rect>(BottomCenterViewboxProperty, "BottomCenterViewbox",
        PropertyMetadata::Create(Int32Rect()));
    data->RegisterProperty<Int32Rect>(BottomRightViewboxProperty, "BottomRightViewbox",
        PropertyMetadata::Create(Int32Rect()));
}

NS_END_COLD_REGION

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
