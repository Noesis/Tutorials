////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __MENU3D_SETTINGSMENU_H__
#define __MENU3D_SETTINGSMENU_H__


#include <NsCore/Noesis.h>
#include <NsGui/UserControl.h>


namespace Menu3D
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class SettingsMenu final: public Noesis::UserControl
{
public:
    SettingsMenu();

private:
    void InitializeComponent();

    NS_DECLARE_REFLECTION(SettingsMenu, UserControl)
};

}


#endif
