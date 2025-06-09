////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GALLERY_MAINWINDOW_H__
#define __GALLERY_MAINWINDOW_H__


#include <NsCore/Noesis.h>
#include <NsCore/Hash.h>
#include <NsCore/String.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsApp/Window.h>
#include <NsGui/Collection.h>
#include <NsDrawing/Color.h>


namespace Noesis
{
class Panel;
class ToggleButton;
class ResourceDictionary;
}

namespace Gallery
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Sample definition
////////////////////////////////////////////////////////////////////////////////////////////////////
struct Sample: public Noesis::BaseComponent
{
    Sample(const char* name_, const char* icon_);

    Noesis::String name;
    Noesis::String icon;

    NS_DECLARE_REFLECTION(Sample, BaseComponent)
};

typedef Noesis::Collection<Sample> SampleCollection;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Category definition
////////////////////////////////////////////////////////////////////////////////////////////////////
struct Category: public Noesis::BaseComponent
{
    Category(const char* name_);

    const SampleCollection* GetSamples() const;

    SampleCollection samples;
    Noesis::String name;

    NS_DECLARE_REFLECTION(Category, BaseComponent)
};

typedef Noesis::Collection<Category> CategoryCollection;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Color item definition
////////////////////////////////////////////////////////////////////////////////////////////////////
struct ColorItem: public Noesis::BaseComponent
{
    ColorItem(const char* name_, const Noesis::Color& color_);

    Noesis::String name;
    Noesis::Color color;

    NS_DECLARE_REFLECTION(ColorItem, BaseComponent);
};

typedef Noesis::Collection<ColorItem> ColorItemCollection;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Control Gallery Main Window code behind
////////////////////////////////////////////////////////////////////////////////////////////////////
class MainWindow final: public NoesisApp::Window
{
public:
    MainWindow();

    const CategoryCollection* GetCategories() const;

    Sample* GetSelectedSample() const;
    void SetSelectedSample(Sample* value);

    const ColorItemCollection* GetThemeColors() const;
    const ColorItemCollection* GetThemeAccents() const;

    ColorItem* GetSelectedThemeColor() const;
    void SetSelectedThemeColor(ColorItem* value);

    ColorItem* GetSelectedThemeAccent() const;
    void SetSelectedThemeAccent(ColorItem* value);

private:
    void InitializeComponent();
    bool ConnectField(BaseComponent* object, const char* name) override;
    void UpdateSample();
    void UpdateTheme();
    Noesis::ResourceDictionary* GetTheme(const char* color, const char* accent);

private:
    CategoryCollection mCategories;
    Sample* mSelectedSample;

    ColorItemCollection mThemeColors;
    ColorItemCollection mThemeAccents;
    ColorItem* mSelectedThemeColor;
    ColorItem* mSelectedThemeAccent;

    Noesis::Panel* mLayoutRoot;
    Noesis::Panel* mWindowContent;

    Noesis::Panel* mSamplePanel;
    Noesis::ContentControl* mSampleContainer1;
    Noesis::ContentControl* mSampleContainer2;

    Noesis::FrameworkElement* mSampleOffset;
    Noesis::FrameworkElement* mSelectorBar;
    Noesis::ToggleButton* mSelectorExpanderButton;

    typedef Noesis::HashMap<Noesis::String, Noesis::Ptr<Noesis::ResourceDictionary>>
        ThemeDictionaries;
    ThemeDictionaries mThemeDictionaries;

    NS_DECLARE_REFLECTION(MainWindow, Window)
};

}


#endif
