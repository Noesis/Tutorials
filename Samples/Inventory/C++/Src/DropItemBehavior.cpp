////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "DropItemBehavior.h"

#include <NsCore/ReflectionImplement.h>
#include <NsCore/Delegate.h>
#include <NsGui/BaseCommand.h>
#include <NsGui/DragDrop.h>
#include <NsGui/UIElementData.h>
#include <NsGui/PropertyMetadata.h>


using namespace Inventory;
using namespace Noesis;


////////////////////////////////////////////////////////////////////////////////////////////////////
bool DropItemBehavior::GetIsDragOver() const
{
    return GetValue<bool>(IsDragOverProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DropItemBehavior::SetIsDragOver(bool value)
{
    SetValue<bool>(IsDragOverProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
BaseCommand* DropItemBehavior::GetDropCommand() const
{
    return GetValue<Ptr<BaseCommand>>(DropCommandProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DropItemBehavior::SetDropCommand(BaseCommand* value)
{
    SetValue<Ptr<BaseCommand>>(DropCommandProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Ptr<Freezable> DropItemBehavior::CreateInstanceCore() const
{
    return *new DropItemBehavior();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DropItemBehavior::OnAttached()
{
    ParentClass::OnAttached();

    FrameworkElement* element = GetAssociatedObject();
    element->SetAllowDrop(true);
    element->PreviewDragEnter() += MakeDelegate(this, &DropItemBehavior::OnDragEnter);
    element->PreviewDragLeave() += MakeDelegate(this, &DropItemBehavior::OnDragLeave);
    element->PreviewDrop() += MakeDelegate(this, &DropItemBehavior::OnDrop);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DropItemBehavior::OnDetaching()
{
    FrameworkElement* element = GetAssociatedObject();
    element->ClearLocalValue(UIElement::AllowDropProperty);
    element->PreviewDragEnter() -= MakeDelegate(this, &DropItemBehavior::OnDragEnter);
    element->PreviewDragLeave() -= MakeDelegate(this, &DropItemBehavior::OnDragLeave);
    element->PreviewDrop() -= MakeDelegate(this, &DropItemBehavior::OnDrop);

    ParentClass::OnDetaching();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DropItemBehavior::OnDragEnter(BaseComponent*, const DragEventArgs& e)
{
    SetIsDragOver(true);
    e.handled = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DropItemBehavior::OnDragLeave(BaseComponent*, const DragEventArgs& e)
{
    SetIsDragOver(false);
    e.handled = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DropItemBehavior::OnDrop(BaseComponent*, const DragEventArgs& e)
{
    SetIsDragOver(false);

    BaseComponent* item = GetAssociatedObject()->GetDataContext();
    BaseCommand* drop = GetDropCommand();
    if (item != 0 && drop != 0 && drop->CanExecute(item))
    {
        drop->Execute(item);
    }
    else
    {
        e.effects = DragDropEffects_None;
    }

    e.handled = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(DropItemBehavior, "Inventory.DropItemBehavior")
{
    UIElementData* data = NsMeta<UIElementData>(TypeOf<SelfClass>());
    data->RegisterProperty<bool>(IsDragOverProperty, "IsDragOver",
        PropertyMetadata::Create(false));
    data->RegisterProperty<Ptr<BaseCommand>>(DropCommandProperty, "DropCommand",
        PropertyMetadata::Create(Ptr<BaseCommand>()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* DropItemBehavior::IsDragOverProperty;
const Noesis::DependencyProperty* DropItemBehavior::DropCommandProperty;
