////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "DropItemBehavior.h"
#include "ViewModel.h"

#include <NsCore/ReflectionImplement.h>
#include <NsCore/TypeId.h>
#include <NsCore/Delegate.h>
#include <NsGui/DragDrop.h>


using namespace Inventory;
using namespace Noesis;


////////////////////////////////////////////////////////////////////////////////////////////////////
Ptr<Freezable> DropItemBehavior::CreateInstanceCore() const
{
    return *new DropItemBehavior();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DropItemBehavior::OnAttached()
{
    ParentClass::OnAttached();

    ContentControl* control = GetAssociatedObject();
    control->SetAllowDrop(true);
    control->PreviewDragEnter() += MakeDelegate(this, &DropItemBehavior::OnDragEnter);
    control->PreviewDragLeave() += MakeDelegate(this, &DropItemBehavior::OnDragLeave);
    control->PreviewDrop() += MakeDelegate(this, &DropItemBehavior::OnDrop);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DropItemBehavior::OnDetaching()
{
    ContentControl* control = GetAssociatedObject();
    control->ClearLocalValue(UIElement::AllowDropProperty);
    control->PreviewDragEnter() -= MakeDelegate(this, &DropItemBehavior::OnDragEnter);
    control->PreviewDragLeave() -= MakeDelegate(this, &DropItemBehavior::OnDragLeave);
    control->PreviewDrop() -= MakeDelegate(this, &DropItemBehavior::OnDrop);

    ParentClass::OnDetaching();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DropItemBehavior::OnDragEnter(BaseComponent* sender, const DragEventArgs& e)
{
    ContentControl* control = (ContentControl*)sender;
    Slot* slot = (Slot*)control->GetContent();

    slot->SetIsDragOver(true);

    e.handled = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DropItemBehavior::OnDragLeave(BaseComponent* sender, const DragEventArgs& e)
{
    ContentControl* control = (ContentControl*)sender;
    Slot* slot = (Slot*)control->GetContent();

    slot->SetIsDragOver(false);

    e.handled = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DropItemBehavior::OnDrop(BaseComponent*, const DragEventArgs& e)
{
    ContentControl* control = GetAssociatedObject();

    Slot* sourceSlot = (Slot*)e.data;
    Slot* targetSlot = (Slot*)control->GetContent();
    targetSlot->SetIsDragOver(false);

    if (targetSlot->GetIsDropAllowed())
    {
        // Move any item in target slot to the source slot
        sourceSlot->SetItem(targetSlot->GetItem());

        // Move dragged item to the target slot
        targetSlot->SetItem(ViewModel::Instance()->GetDraggedItem());
    }
    else
    {
        e.effects = DragDropEffects_None;
    }

    e.handled = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(DropItemBehavior)
{
    NsMeta<TypeId>("Inventory.DropItemBehavior");
}
