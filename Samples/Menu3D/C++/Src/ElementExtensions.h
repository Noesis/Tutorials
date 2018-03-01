////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __MENU3D_ELEMENTEXTENSIONS_H__
#define __MENU3D_ELEMENTEXTENSIONS_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/DependencyObject.h>


namespace Menu3D
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class ElementExtensions final: public Noesis::DependencyObject
{
public:
    static bool GetFocusOnLoaded(DependencyObject* d);
    static void SetFocusOnLoaded(DependencyObject* d, bool value);

    static bool GetFocusOnHover(DependencyObject* d);
    static void SetFocusOnHover(DependencyObject* d, bool value);

    static bool GetFocusContentOnHover(DependencyObject* d);
    static void SetFocusContentOnHover(DependencyObject* d, bool value);

    static bool GetSelectOnHover(DependencyObject* d);
    static void SetSelectOnHover(DependencyObject* d, bool value);

    static bool GetSelectAllOnFocus(DependencyObject* d);
    static void SetSelectAllOnFocus(DependencyObject* d, bool value);

public:
    static const Noesis::DependencyProperty* FocusOnLoadedProperty;
    static const Noesis::DependencyProperty* FocusOnHoverProperty;
    static const Noesis::DependencyProperty* FocusContentOnHoverProperty;
    static const Noesis::DependencyProperty* SelectOnHoverProperty;
    static const Noesis::DependencyProperty* SelectAllOnFocusProperty;

private:
    static void OnFocusOnLoadedChanged(DependencyObject* d,
        const Noesis::DependencyPropertyChangedEventArgs& e);
    static void OnFocusOnHoverChanged(DependencyObject* d,
        const Noesis::DependencyPropertyChangedEventArgs& e);
    static void OnFocusContentOnHoverChanged(DependencyObject* d,
        const Noesis::DependencyPropertyChangedEventArgs& e);
    static void OnSelectOnHoverChanged(DependencyObject* d,
        const Noesis::DependencyPropertyChangedEventArgs& e);
    static void OnSelectAllOnFocusChanged(DependencyObject* d,
        const Noesis::DependencyPropertyChangedEventArgs& e);

private:
    NS_DECLARE_REFLECTION(ElementExtensions, DependencyObject)
};

}


#endif
