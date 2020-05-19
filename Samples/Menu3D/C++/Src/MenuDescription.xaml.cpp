////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "MenuDescription.xaml.h"

#include <NsCore/ReflectionImplement.h>
#include <NsGui/IntegrationAPI.h>
#include <NsGui/UIElementData.h>
#include <NsGui/PropertyMetadata.h>


using namespace Menu3D;
using namespace Noesis;


////////////////////////////////////////////////////////////////////////////////////////////////////
MenuDescription::MenuDescription()
{
    InitializeComponent();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MenuDescription::InitializeComponent()
{
    GUI::LoadComponent(this, "MenuDescription.xaml");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(Menu3D::MenuDescription, "Menu3D.MenuDescription")
{
    UIElementData* data = NsMeta<UIElementData>(TypeOf<SelfClass>());
    data->RegisterProperty<String>(DescriptionProperty, "Description",
        PropertyMetadata::Create(String()));
    data->RegisterProperty<String>(AcceptTextProperty, "AcceptText",
        PropertyMetadata::Create(String()));
    data->RegisterProperty<String>(CancelTextProperty, "CancelText",
        PropertyMetadata::Create(String()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* MenuDescription::DescriptionProperty;
const Noesis::DependencyProperty* MenuDescription::AcceptTextProperty;
const Noesis::DependencyProperty* MenuDescription::CancelTextProperty;
