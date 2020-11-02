////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __NINESLICE_NINESLICEIMAGE_H__
#define __NINESLICE_NINESLICEIMAGE_H__


#include <NsCore/Noesis.h>
#include <NsGui/ContentControl.h>


namespace Noesis
{
class ImageSource;
struct Thickness;
}

namespace NineSlice
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class NineSliceImage: public Noesis::ContentControl
{
public:
    /// Gets or sets image source
    //@{
    Noesis::ImageSource* GetImageSource() const;
    void SetImageSource(Noesis::ImageSource* value);
    //@}

    /// Gets or sets slices dimensions
    //@{
    const Noesis::Thickness& GetSlices() const;
    void SetSlices(const Noesis::Thickness& value);
    //@}

public:
    static const Noesis::DependencyProperty* ImageSourceProperty;
    static const Noesis::DependencyProperty* SlicesProperty;

    static const Noesis::DependencyProperty* TopLeftViewboxProperty;
    static const Noesis::DependencyProperty* TopCenterViewboxProperty;
    static const Noesis::DependencyProperty* TopRightViewboxProperty;
    static const Noesis::DependencyProperty* CenterLeftViewboxProperty;
    static const Noesis::DependencyProperty* CenterViewboxProperty;
    static const Noesis::DependencyProperty* CenterRightViewboxProperty;
    static const Noesis::DependencyProperty* BottomLeftViewboxProperty;
    static const Noesis::DependencyProperty* BottomCenterViewboxProperty;
    static const Noesis::DependencyProperty* BottomRightViewboxProperty;

    NS_DECLARE_REFLECTION(NineSliceImage, ContentControl)
};

}


#endif
