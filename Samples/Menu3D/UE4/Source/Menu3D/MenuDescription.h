////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __MENU3D_MENUDESCRIPTION_H__
#define __MENU3D_MENUDESCRIPTION_H__


#include <NsCore/Noesis.h>
#include <NsGui/UserControl.h>


namespace Menu3D
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class MenuDescription final: public Noesis::UserControl
{
public:
    MenuDescription();

public:
    static const Noesis::DependencyProperty* DescriptionProperty;
    static const Noesis::DependencyProperty* AcceptTextProperty;
    static const Noesis::DependencyProperty* CancelTextProperty;

private:
    void InitializeComponent();

    NS_DECLARE_REFLECTION(MenuDescription, UserControl)
};

}


#endif
