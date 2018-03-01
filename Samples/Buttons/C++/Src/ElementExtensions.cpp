////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "ElementExtensions.h"

#include <NsCore/ReflectionImplement.h>
#include <NsCore/TypeId.h>
#include <NsGui/FrameworkElement.h>
#include <NsGui/UIElementData.h>
#include <NsGui/PropertyMetadata.h>
#include <NsGui/Selector.h>
#include <NsGui/PasswordBox.h>
#include <NsGui/TextBox.h>


using namespace Buttons;
using namespace Noesis;


////////////////////////////////////////////////////////////////////////////////////////////////////
bool ElementExtensions::GetFocusOnLoaded(DependencyObject* d)
{
    return d->GetValue<bool>(FocusOnLoadedProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ElementExtensions::SetFocusOnLoaded(DependencyObject* d, bool value)
{
    d->SetValue<bool>(FocusOnLoadedProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool ElementExtensions::GetFocusOnHover(DependencyObject* d)
{
    return d->GetValue<bool>(FocusOnHoverProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ElementExtensions::SetFocusOnHover(DependencyObject* d, bool value)
{
    d->SetValue<bool>(FocusOnHoverProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool ElementExtensions::GetSelectOnHover(DependencyObject* d)
{
    return d->GetValue<bool>(SelectOnHoverProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ElementExtensions::SetSelectOnHover(DependencyObject* d, bool value)
{
    d->SetValue<bool>(SelectOnHoverProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool ElementExtensions::GetSelectAllOnFocus(DependencyObject* d)
{
    return d->GetValue<bool>(SelectAllOnFocusProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ElementExtensions::SetSelectAllOnFocus(DependencyObject* d, bool value)
{
    d->SetValue<bool>(SelectAllOnFocusProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ElementExtensions::OnFocusOnLoadedChanged(DependencyObject* d,
        const DependencyPropertyChangedEventArgs& e)
{
    FrameworkElement* element = NsDynamicCast<FrameworkElement*>(d);
    if (element != 0 && *(bool*)e.newValue)
    {
        element->Loaded() += [](BaseComponent* sender, const RoutedEventArgs&)
        {
            FrameworkElement* element = (FrameworkElement*)sender;
            element->Focus();
        };
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ElementExtensions::OnFocusOnHoverChanged(DependencyObject* d,
        const DependencyPropertyChangedEventArgs& e)
{
    FrameworkElement* element = NsDynamicCast<FrameworkElement*>(d);
    if (element != 0 && *(bool*)e.newValue)
    {
        element->Focus();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ElementExtensions::OnSelectOnHoverChanged(DependencyObject* d,
        const DependencyPropertyChangedEventArgs& e)
{
    FrameworkElement* element = NsDynamicCast<FrameworkElement*>(d);
    if (element != 0 && *(bool*)e.newValue)
    {
        Selector::SetIsSelected(element, true);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ElementExtensions::OnSelectAllOnFocusChanged(DependencyObject* d,
    const DependencyPropertyChangedEventArgs& e)
{
    UIElement* element = NsDynamicCast<UIElement*>(d);
    if (element != 0 && *(bool*)e.newValue)
    {
        element->GotFocus() += [](BaseComponent* sender, const RoutedEventArgs&)
        {
            PasswordBox* passwordBox = NsDynamicCast<PasswordBox*>(sender);
            if (passwordBox != 0)
            {
                passwordBox->SelectAll();
                return;
            }

            TextBox* textBox = NsDynamicCast<TextBox*>(sender);
            if (textBox != 0)
            {
                textBox->SelectAll();
                return;
            }
        };
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_IMPLEMENT_REFLECTION(Buttons::ElementExtensions)
{
    NsMeta<TypeId>("Buttons.ElementExtensions");

    Ptr<UIElementData> data = NsMeta<UIElementData>(TypeOf<SelfClass>());
    data->RegisterProperty<bool>(FocusOnLoadedProperty, "FocusOnLoaded",
        PropertyMetadata::Create(false, &ElementExtensions::OnFocusOnLoadedChanged));
    data->RegisterProperty<bool>(FocusOnHoverProperty, "FocusOnHover",
        PropertyMetadata::Create(false, &ElementExtensions::OnFocusOnHoverChanged));
    data->RegisterProperty<bool>(SelectOnHoverProperty, "SelectOnHover",
        PropertyMetadata::Create(false, &ElementExtensions::OnSelectOnHoverChanged));
    data->RegisterProperty<bool>(SelectAllOnFocusProperty, "SelectAllOnFocus",
        PropertyMetadata::Create(false, &ElementExtensions::OnSelectAllOnFocusChanged));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const DependencyProperty* ElementExtensions::FocusOnLoadedProperty;
const DependencyProperty* ElementExtensions::FocusOnHoverProperty;
const DependencyProperty* ElementExtensions::SelectOnHoverProperty;
const DependencyProperty* ElementExtensions::SelectAllOnFocusProperty;
