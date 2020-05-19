////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "MainWindow.xaml.h"

#include <NsGui/IntegrationAPI.h>
#include <NsGui/Panel.h>
#include <NsGui/ToggleButton.h>
#include <NsGui/ScaleTransform.h>
#include <NsGui/ResourceDictionary.h>
#include <NsGui/UICollection.h>
#include <NsGui/UIElementData.h>
#include <NsGui/PropertyMetadata.h>
#include <NsCore/Nullable.h>
#include <NsApp/Application.h>


using namespace Noesis;
using namespace NoesisApp;
using namespace Gallery;


////////////////////////////////////////////////////////////////////////////////////////////////////
Sample::Sample(const char* name_, const char* icon_) : name(name_), icon(icon_)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_IMPLEMENT_REFLECTION(Gallery::Sample)
{
    NsProp("Name", &Sample::name);
    NsProp("Icon", &Sample::icon);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Category::Category(const char* name_): name(name_)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const SampleCollection* Category::GetSamples() const
{
    return &samples;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_IMPLEMENT_REFLECTION(Gallery::Category)
{
    NsProp("Name", &Category::name);
    NsProp("Samples", &Category::GetSamples);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ColorItem::ColorItem(const char* name_, const Color& color_): name(name_), color(color_)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_IMPLEMENT_REFLECTION(Gallery::ColorItem)
{
    NsProp("Name", &ColorItem::name);
    NsProp("Color", &ColorItem::color);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MainWindow::MainWindow(): mSelectedSample(0), mSelectedThemeColor(0), mSelectedThemeAccent(0),
    mSamplePanel(0), mSampleContainer1(0), mSampleContainer2(0)
{
    InitializeComponent();

    {
        Ptr<Category> category = MakePtr<Category>("Basic Input");
        category->samples.Add(MakePtr<Sample>("Button", "A"));
        category->samples.Add(MakePtr<Sample>("RepeatButton", "B"));
        category->samples.Add(MakePtr<Sample>("ToggleButton", "C"));
        category->samples.Add(MakePtr<Sample>("CheckBox", "D"));
        category->samples.Add(MakePtr<Sample>("RadioButton", "E"));
        category->samples.Add(MakePtr<Sample>("Slider", "F"));
        mCategories.Add(category);
    }
    {
        Ptr<Category> category = MakePtr<Category>("Text");
        category->samples.Add(MakePtr<Sample>("TextBlock", "G"));
        category->samples.Add(MakePtr<Sample>("TextBox", "H"));
        category->samples.Add(MakePtr<Sample>("PasswordBox", "I"));
        category->samples.Add(MakePtr<Sample>("Hyperlink", "J"));
        mCategories.Add(category);
    }
    {
        Ptr<Category> category = MakePtr<Category>("Collections");
        category->samples.Add(MakePtr<Sample>("ItemsControl", "K"));
        category->samples.Add(MakePtr<Sample>("ComboBox", "L"));
        category->samples.Add(MakePtr<Sample>("ListBox", "M"));
        category->samples.Add(MakePtr<Sample>("ListView", "N"));
        category->samples.Add(MakePtr<Sample>("TreeView", "O"));
        category->samples.Add(MakePtr<Sample>("TabControl", "P"));
        mCategories.Add(category);
    }
    {
        Ptr<Category> category = MakePtr<Category>("Layout");
        category->samples.Add(MakePtr<Sample>("Canvas", "Q"));
        category->samples.Add(MakePtr<Sample>("StackPanel", "R"));
        category->samples.Add(MakePtr<Sample>("WrapPanel", "S"));
        category->samples.Add(MakePtr<Sample>("DockPanel", "T"));
        category->samples.Add(MakePtr<Sample>("Grid", "U"));
        category->samples.Add(MakePtr<Sample>("UniformGrid", "V"));
        category->samples.Add(MakePtr<Sample>("GroupBox", "W"));
        category->samples.Add(MakePtr<Sample>("Expander", "X"));
        category->samples.Add(MakePtr<Sample>("ScrollViewer", "Y"));
        mCategories.Add(category);
    }
    {
        Ptr<Category> category = MakePtr<Category>("Menus and Toolbars");
        category->samples.Add(MakePtr<Sample>("Menu", "Z"));
        category->samples.Add(MakePtr<Sample>("ContextMenu", "Z"));
        category->samples.Add(MakePtr<Sample>("ToolBar", "a"));
        mCategories.Add(category);
    }
    {
        Ptr<Category> category = MakePtr<Category>("Status and Info");
        category->samples.Add(MakePtr<Sample>("StatusBar", "b"));
        category->samples.Add(MakePtr<Sample>("ProgressBar", "c"));
        category->samples.Add(MakePtr<Sample>("ToolTip", "d"));
        mCategories.Add(category);
    }
    {
        Ptr<Category> category = MakePtr<Category>("Media");
        category->samples.Add(MakePtr<Sample>("Brushes", "e"));
        category->samples.Add(MakePtr<Sample>("Image", "f"));
        category->samples.Add(MakePtr<Sample>("Effects", "g"));
        category->samples.Add(MakePtr<Sample>("Animation", "h"));
        mCategories.Add(category);
    }

    mThemeColors.Add(MakePtr<ColorItem>("Dark", Color(16, 20, 24)));
    mThemeColors.Add(MakePtr<ColorItem>("Light", Color(246, 247, 248)));

    mThemeAccents.Add(MakePtr<ColorItem>("Red", Color(222, 43, 16)));
    mThemeAccents.Add(MakePtr<ColorItem>("Green", Color(42, 166, 12)));
    mThemeAccents.Add(MakePtr<ColorItem>("Blue", Color(16, 152, 223)));
    mThemeAccents.Add(MakePtr<ColorItem>("Orange", Color(223, 153, 16)));
    mThemeAccents.Add(MakePtr<ColorItem>("Emerald", Color(16, 222, 98)));
    mThemeAccents.Add(MakePtr<ColorItem>("Purple", Color(137, 78, 237)));
    mThemeAccents.Add(MakePtr<ColorItem>("Crimson", Color(222, 16, 67)));
    mThemeAccents.Add(MakePtr<ColorItem>("Lime", Color(153, 223, 16)));
    mThemeAccents.Add(MakePtr<ColorItem>("Aqua", Color(16, 221, 223)));

    mSelectedThemeColor = mThemeColors.Get(1);
    mSelectedThemeAccent = mThemeAccents.Get(2);

    UpdateTheme();

    SetDataContext(this);

    SizeChanged() += [this](BaseComponent*, const SizeChangedEventArgs& e)
    {
        float dpi = GetDisplay()->GetScale();
        float scale;

        if (GetActualWidth() > GetActualHeight())
        {
            mSampleOffset->SetWidth(mSelectorBar->GetWidth());
            mSelectorExpanderButton->SetVisibility(Visibility_Hidden);
            mSelectorExpanderButton->SetIsChecked(false);
            mSelectorExpanderButton->SetIsChecked(true);

            scale = Max(1.0f, e.newSize.width / (1280.0f * dpi)) * dpi;
        }
        else
        {
            mSampleOffset->SetWidth(0.0f);
            mSelectorExpanderButton->SetIsChecked(true);
            mSelectorExpanderButton->SetIsChecked(false);
            mSelectorExpanderButton->SetVisibility(Visibility_Visible);

            scale = Max(1.0f, e.newSize.height / (720.0f * dpi)) * dpi;
        }

        ScaleTransform* rootScale = (ScaleTransform*)mLayoutRoot->GetLayoutTransform();
        rootScale->SetScaleX(scale);
        rootScale->SetScaleY(scale);
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const CategoryCollection* MainWindow::GetCategories() const
{
    return &mCategories;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Sample* MainWindow::GetSelectedSample() const
{
    return mSelectedSample;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::SetSelectedSample(Sample* value)
{
    if (mSelectedSample != value && value != nullptr)
    {
        mSelectedSample = value;
        UpdateSample();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const ColorItemCollection* MainWindow::GetThemeColors() const
{
    return &mThemeColors;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const ColorItemCollection* MainWindow::GetThemeAccents() const
{
    return &mThemeAccents;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ColorItem* MainWindow::GetSelectedThemeColor() const
{
    return mSelectedThemeColor;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::SetSelectedThemeColor(ColorItem* value)
{
    if (mSelectedThemeColor != value)
    {
        mSelectedThemeColor = value;
        UpdateTheme();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ColorItem* MainWindow::GetSelectedThemeAccent() const
{
    return mSelectedThemeAccent;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::SetSelectedThemeAccent(ColorItem* value)
{
    if (mSelectedThemeAccent != value)
    {
        mSelectedThemeAccent = value;
        UpdateTheme();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::InitializeComponent()
{
    GUI::LoadComponent(this, "MainWindow.xaml");

    mLayoutRoot = FindName<Panel>("LayoutRoot");

    mSamplePanel = FindName<Panel>("SamplePanel");
    mSampleContainer1 = FindName<ContentControl>("SampleContainer1");
    mSampleContainer2 = FindName<ContentControl>("SampleContainer2");

    mSampleOffset = FindName<FrameworkElement>("SampleOffset");
    mSelectorBar = FindName<FrameworkElement>("SelectorBar");
    mSelectorExpanderButton = FindName<ToggleButton>("SelectorExpanderButton");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::UpdateSample()
{
    String sampleName(String::VarArgs(), "Samples/%s.xaml", mSelectedSample->name.Str());
    Ptr<FrameworkElement> sample = GUI::LoadXaml<FrameworkElement>(sampleName.Str());

    if (sample != nullptr)
    {
        if (mSampleContainer1->GetContent() == nullptr)
        {
            mSampleContainer1->SetContent(sample);
        }
        else
        {
            mSampleContainer2->SetContent(sample);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::UpdateTheme()
{
    if (mSelectedThemeColor == nullptr || mSelectedThemeAccent == nullptr)
    {
        return;
    }

    const char* color = mSelectedThemeColor->name.Str();
    const char* accent = mSelectedThemeAccent->name.Str();
    ResourceDictionary* theme = GetTheme(color, accent);

    ResourceDictionary* resources = mSamplePanel->GetResources();
    resources->GetMergedDictionaries()->Clear();
    resources->GetMergedDictionaries()->Add(theme);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ResourceDictionary* MainWindow::GetTheme(const char* color, const char* accent)
{
    String themeName(String::VarArgs(), "Theme/NoesisTheme.Brushes.%s%s.xaml", color, accent);
    ThemeDictionaries::Iterator it = mThemeDictionaries.Find(themeName);
    if (it != mThemeDictionaries.End())
    {
        return it->value;
    }

    Ptr<ResourceDictionary> theme = GUI::LoadXaml<ResourceDictionary>(themeName.Str());
    mThemeDictionaries.Insert(themeName, theme);
    return theme;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(Gallery::MainWindow, "Gallery.MainWindow")
{
    NsProp("Categories", &MainWindow::GetCategories);
    NsProp("SelectedSample", &MainWindow::GetSelectedSample, &MainWindow::SetSelectedSample);
    NsProp("ThemeColors", &MainWindow::GetThemeColors);
    NsProp("ThemeAccents", &MainWindow::GetThemeAccents);
    NsProp("SelectedThemeColor", &MainWindow::GetSelectedThemeColor,
        &MainWindow::SetSelectedThemeColor);
    NsProp("SelectedThemeAccent", &MainWindow::GetSelectedThemeAccent,
        &MainWindow::SetSelectedThemeAccent);
}
