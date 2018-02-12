////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "OptionSelector.xaml.h"

#include <NsCore/ReflectionImplement.h>
#include <NsGui/IntegrationAPI.h>
#include <NsGui/RepeatButton.h>
#include <NsGui/UIElement.h>
#include <NsGui/UIElementData.h>
#include <NsGui/KeyboardNavigation.h>
#include <NsGui/ObservableCollection.h>
#include <NsGui/INotifyCollectionChanged.h>


using namespace Menu3D;
using namespace Noesis;


////////////////////////////////////////////////////////////////////////////////////////////////////
OptionSelector::OptionSelector(): _prevButton(0), _nextButton(0)
{
    SetOptions(MakePtr<ObservableCollection<UIElement>>());

    Initialized() += MakeDelegate(this, &OptionSelector::OnInitialized);
    InitializeComponent();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ObservableCollection<UIElement>* OptionSelector::GetOptions() const
{
    return _options;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void OptionSelector::SetOptions(ObservableCollection<UIElement>* value)
{
    if (_options)
    {
        _options->CollectionChanged() -= MakeDelegate(this, &OptionSelector::OnOptionsChanged);
    }

    _options.Reset(value);

    if (_options)
    {
        _options->CollectionChanged() += MakeDelegate(this, &OptionSelector::OnOptionsChanged);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int OptionSelector::GetSelectedIndex() const
{
    return GetValue<int>(SelectedIndexProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void OptionSelector::SetSelectedIndex(int value)
{
    SetValue<int>(SelectedIndexProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
BaseComponent* OptionSelector::GetSelectedOption() const
{
    return GetValue<Ptr<BaseComponent>>(SelectedOptionProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void OptionSelector::InitializeComponent()
{
    GUI::LoadComponent(this, "OptionSelector.xaml");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void OptionSelector::OnInitialized(Noesis::BaseComponent*, const Noesis::EventArgs&)
{
    _prevButton = FindName<RepeatButton>("PrevButton");
    _nextButton = FindName<RepeatButton>("NextButton");

    _prevButton->Click() += MakeDelegate(this, &OptionSelector::OnPrev);
    _nextButton->Click() += MakeDelegate(this, &OptionSelector::OnNext);

    UpdateSelectedOption();
    UpdateButtons();

    KeyDown() += MakeDelegate(this, &OptionSelector::OnKeyDownHandler);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void OptionSelector::OnPrev(BaseComponent*, const RoutedEventArgs&)
{
    SetSelectedIndex(GetSelectedIndex() - 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void OptionSelector::OnNext(BaseComponent*, const RoutedEventArgs&)
{
    SetSelectedIndex(GetSelectedIndex() + 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void OptionSelector::OnKeyDownHandler(Noesis::BaseComponent*, const Noesis::KeyEventArgs& e)
{
    switch (e.key)
    {
        case Key_Space:
        {
            CycleNext();
            e.handled = true;
            break;
        }
        case Key_Enter:
        {
            if (KeyboardNavigation::GetAcceptsReturn(this))
            {
                CycleNext();
                e.handled = true;
            }
            break;
        }
        case Key_Left:
        {
            if (GetIndex() > 0)
            {
                SetSelectedIndex(GetSelectedIndex() - 1);
            }

            e.handled = true;
            break;
        }
        case Key_Right:
{
            if (GetIndex() < GetLastIndex())
            {
                SetSelectedIndex(GetSelectedIndex() + 1);
            }

            e.handled = true;
            break;
        }
        default:
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void OptionSelector::OnOptionsChanged(BaseComponent*, const NotifyCollectionChangedEventArgs&)
{
    UpdateSelectedOption();
    UpdateButtons();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void OptionSelector::OnIndexChanged(DependencyObject* d, const DependencyPropertyChangedEventArgs&)
{
    OptionSelector* selector = NsDynamicCast<OptionSelector*>(d);
    if (selector != 0)
    {
        selector->UpdateSelectedOption();
        selector->UpdateButtons();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void OptionSelector::CycleNext()
{
    if (GetNumOptions() > 0)
    {
        SetSelectedIndex(GetIndex() < GetLastIndex() ? GetIndex() + 1 : 0);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void OptionSelector::UpdateSelectedOption()
{
    SetSelectedOption(GetIndex() < 0 ? nullptr : GetOptions()->Get(GetIndex()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void OptionSelector::UpdateButtons()
{
    if (_prevButton)
    {
        _prevButton->SetIsEnabled(GetIndex() > 0);
    }

    if (_nextButton)
    {
        _nextButton->SetIsEnabled(GetIndex() < GetLastIndex());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int OptionSelector::GetNumOptions() const
{
    return _options ? _options->Count() : 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int OptionSelector::GetLastIndex() const
{
    return GetNumOptions() - 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int OptionSelector::GetIndex() const
{
    return GetNumOptions() == 0 ? -1 : Max(0, Min(GetSelectedIndex(), GetLastIndex()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void OptionSelector::SetSelectedOption(BaseComponent* value)
{
    SetValue<Ptr<BaseComponent>>(SelectedOptionProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_IMPLEMENT_REFLECTION(Menu3D::OptionSelector)
{
    NsMeta<TypeId>("Menu3D.OptionSelector");
    NsProp("Options", &OptionSelector::GetOptions, &OptionSelector::SetOptions);
    NsProp("NumOptions", &OptionSelector::GetNumOptions);
    NsProp("LastIndex", &OptionSelector::GetLastIndex);
    NsProp("Index", &OptionSelector::GetIndex);

    Ptr<UIElementData> data = NsMeta<UIElementData>(TypeOf<SelfClass>());
    data->RegisterProperty<int>(SelectedIndexProperty, "SelectedIndex",
        PropertyMetadata::Create(-1, &OptionSelector::OnIndexChanged));
    data->RegisterProperty<Ptr<BaseComponent>>(SelectedOptionProperty, "SelectedOption",
        PropertyMetadata::Create(Ptr<BaseComponent>()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const DependencyProperty* OptionSelector::SelectedIndexProperty;
const DependencyProperty* OptionSelector::SelectedOptionProperty;
