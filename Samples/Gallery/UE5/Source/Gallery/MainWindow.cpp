////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "MainWindow.h"

#include <NsGui/IntegrationAPI.h>
#include <NsGui/Panel.h>
#include <NsGui/ToggleButton.h>
#include <NsGui/ScaleTransform.h>
#include <NsGui/ResourceDictionary.h>
#include <NsGui/UICollection.h>
#include <NsGui/UIElementData.h>
#include <NsGui/PropertyMetadata.h>
#include <NsCore/Nullable.h>


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
ColorItem::ColorItem(const char* name_, const Noesis::Color& color_): name(name_), color(color_)
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
    {
        Noesis::Ptr<Category> category = Noesis::MakePtr<Category>("Basic Input");
        category->samples.Add(Noesis::MakePtr<Sample>("Button", "A"));
        category->samples.Add(Noesis::MakePtr<Sample>("RepeatButton", "B"));
        category->samples.Add(Noesis::MakePtr<Sample>("ToggleButton", "C"));
        category->samples.Add(Noesis::MakePtr<Sample>("CheckBox", "D"));
        category->samples.Add(Noesis::MakePtr<Sample>("RadioButton", "E"));
        category->samples.Add(Noesis::MakePtr<Sample>("Slider", "F"));
        mCategories.Add(category);
    }
    {
        Noesis::Ptr<Category> category = Noesis::MakePtr<Category>("Text");
        category->samples.Add(Noesis::MakePtr<Sample>("TextBlock", "G"));
        category->samples.Add(Noesis::MakePtr<Sample>("TextBox", "H"));
        category->samples.Add(Noesis::MakePtr<Sample>("PasswordBox", "I"));
        category->samples.Add(Noesis::MakePtr<Sample>("Hyperlink", "J"));
        mCategories.Add(category);
    }
    {
        Noesis::Ptr<Category> category = Noesis::MakePtr<Category>("Collections");
        category->samples.Add(Noesis::MakePtr<Sample>("ItemsControl", "K"));
        category->samples.Add(Noesis::MakePtr<Sample>("ComboBox", "L"));
        category->samples.Add(Noesis::MakePtr<Sample>("ListBox", "M"));
        category->samples.Add(Noesis::MakePtr<Sample>("ListView", "N"));
        category->samples.Add(Noesis::MakePtr<Sample>("TreeView", "O"));
        category->samples.Add(Noesis::MakePtr<Sample>("TabControl", "P"));
        mCategories.Add(category);
    }
    {
        Noesis::Ptr<Category> category = Noesis::MakePtr<Category>("Layout");
        category->samples.Add(Noesis::MakePtr<Sample>("Canvas", "Q"));
        category->samples.Add(Noesis::MakePtr<Sample>("StackPanel", "R"));
        category->samples.Add(Noesis::MakePtr<Sample>("WrapPanel", "S"));
        category->samples.Add(Noesis::MakePtr<Sample>("DockPanel", "T"));
        category->samples.Add(Noesis::MakePtr<Sample>("Grid", "U"));
        category->samples.Add(Noesis::MakePtr<Sample>("UniformGrid", "V"));
        category->samples.Add(Noesis::MakePtr<Sample>("GroupBox", "W"));
        category->samples.Add(Noesis::MakePtr<Sample>("Expander", "X"));
        category->samples.Add(Noesis::MakePtr<Sample>("ScrollViewer", "Y"));
        mCategories.Add(category);
    }
    {
        Noesis::Ptr<Category> category = Noesis::MakePtr<Category>("Menus and Toolbars");
        category->samples.Add(Noesis::MakePtr<Sample>("Menu", "Z"));
        category->samples.Add(Noesis::MakePtr<Sample>("ContextMenu", "Z"));
        category->samples.Add(Noesis::MakePtr<Sample>("ToolBar", "a"));
        mCategories.Add(category);
    }
    {
        Noesis::Ptr<Category> category = Noesis::MakePtr<Category>("Status and Info");
        category->samples.Add(Noesis::MakePtr<Sample>("StatusBar", "b"));
        category->samples.Add(Noesis::MakePtr<Sample>("ProgressBar", "c"));
        category->samples.Add(Noesis::MakePtr<Sample>("ToolTip", "d"));
        mCategories.Add(category);
    }
    {
        Noesis::Ptr<Category> category = Noesis::MakePtr<Category>("Media");
        category->samples.Add(Noesis::MakePtr<Sample>("Brushes", "e"));
        category->samples.Add(Noesis::MakePtr<Sample>("Image", "f"));
        category->samples.Add(Noesis::MakePtr<Sample>("Effects", "g"));
        category->samples.Add(Noesis::MakePtr<Sample>("Blending", "w"));
        category->samples.Add(Noesis::MakePtr<Sample>("Animation", "h"));
        mCategories.Add(category);
    }

    mThemeColors.Add(Noesis::MakePtr<ColorItem>("Dark", Noesis::Color(16, 20, 24)));
    mThemeColors.Add(Noesis::MakePtr<ColorItem>("Light", Noesis::Color(246, 247, 248)));

    mThemeAccents.Add(Noesis::MakePtr<ColorItem>("Red", Noesis::Color(222, 43, 16)));
    mThemeAccents.Add(Noesis::MakePtr<ColorItem>("Green", Noesis::Color(42, 166, 12)));
    mThemeAccents.Add(Noesis::MakePtr<ColorItem>("Blue", Noesis::Color(16, 152, 223)));
    mThemeAccents.Add(Noesis::MakePtr<ColorItem>("Orange", Noesis::Color(223, 153, 16)));
    mThemeAccents.Add(Noesis::MakePtr<ColorItem>("Emerald", Noesis::Color(16, 222, 98)));
    mThemeAccents.Add(Noesis::MakePtr<ColorItem>("Purple", Noesis::Color(137, 78, 237)));
    mThemeAccents.Add(Noesis::MakePtr<ColorItem>("Crimson", Noesis::Color(222, 16, 67)));
    mThemeAccents.Add(Noesis::MakePtr<ColorItem>("Lime", Noesis::Color(153, 223, 16)));
    mThemeAccents.Add(Noesis::MakePtr<ColorItem>("Aqua", Noesis::Color(16, 221, 223)));

    mSelectedThemeColor = mThemeColors.Get(1);
    mSelectedThemeAccent = mThemeAccents.Get(2);

    InitializeComponent();

    UpdateTheme();

    Noesis::Panel* windowContent = FindName<Noesis::Panel>("WindowContent");
    windowContent->SizeChanged() += [this](Noesis::BaseComponent*, const Noesis::SizeChangedEventArgs& e)
    {
        float scale;

        if (GetActualWidth() > GetActualHeight())
        {
            mSampleOffset->SetWidth(mSelectorBar->GetWidth());
            mSelectorExpanderButton->SetVisibility(Noesis::Visibility_Hidden);
            mSelectorExpanderButton->SetIsChecked(false);
            mSelectorExpanderButton->SetIsChecked(true);

            scale = Noesis::Max(1.0f, e.newSize.width / 1280.0f);
        }
        else
        {
            mSampleOffset->SetWidth(0.0f);
            mSelectorExpanderButton->SetIsChecked(true);
            mSelectorExpanderButton->SetIsChecked(false);
            mSelectorExpanderButton->SetVisibility(Noesis::Visibility_Visible);

            scale = Noesis::Max(1.0f, e.newSize.height / 720.0f);
        }

        Noesis::ScaleTransform* rootScale = (Noesis::ScaleTransform*)mLayoutRoot->GetLayoutTransform();
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
    Noesis::GUI::LoadComponent(this, "MainWindow.xaml");

    mLayoutRoot = FindName<Noesis::Panel>("LayoutRoot");

    mSamplePanel = FindName<Noesis::Panel>("SamplePanel");
    mSampleContainer1 = FindName<Noesis::ContentControl>("SampleContainer1");
    mSampleContainer2 = FindName<Noesis::ContentControl>("SampleContainer2");

    mSampleOffset = FindName<Noesis::FrameworkElement>("SampleOffset");
    mSelectorBar = FindName<Noesis::FrameworkElement>("SelectorBar");
    mSelectorExpanderButton = FindName<Noesis::ToggleButton>("SelectorExpanderButton");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::UpdateSample()
{
    Noesis::String sampleName(Noesis::String::VarArgs(),
        "Gallery/Samples/%s.xaml", mSelectedSample->name.Str());
    Noesis::Ptr<Noesis::FrameworkElement> sample =
        Noesis::GUI::LoadXaml<Noesis::FrameworkElement>(sampleName.Str());

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
    Noesis::ResourceDictionary* theme = GetTheme(color, accent);

    Noesis::ResourceDictionary* resources = mSamplePanel->GetResources();
    resources->GetMergedDictionaries()->Clear();
    resources->GetMergedDictionaries()->Add(theme);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::ResourceDictionary* MainWindow::GetTheme(const char* color, const char* accent)
{
    Noesis::String themeName(Noesis::String::VarArgs(),
        "NoesisTheme.Brushes.%s%s.xaml", color, accent);
    ThemeDictionaries::Iterator it = mThemeDictionaries.Find(themeName);
    if (it != mThemeDictionaries.End())
    {
        return it->value;
    }

    Noesis::String uri(Noesis::String::VarArgs(),
        "/Noesis.GUI.Extensions;component/Theme/%s", themeName.Str());
    Noesis::Ptr<Noesis::ResourceDictionary> theme =
        Noesis::GUI::LoadXaml<Noesis::ResourceDictionary>(uri.Str());
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

NS_END_COLD_REGION
