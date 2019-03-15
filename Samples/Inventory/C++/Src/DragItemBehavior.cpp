////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "DragItemBehavior.h"
#include "ViewModel.h"

#include <NsCore/ReflectionImplement.h>
#include <NsCore/TypeId.h>
#include <NsCore/Delegate.h>
#include <NsGui/DragDrop.h>


using namespace Inventory;
using namespace Noesis;


////////////////////////////////////////////////////////////////////////////////////////////////////
DragItemBehavior::DragItemBehavior(): _mouseClicked(false)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Ptr<Freezable> DragItemBehavior::CreateInstanceCore() const
{
    return *new DragItemBehavior();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DragItemBehavior::OnAttached()
{
    ParentClass::OnAttached();

    ContentControl* control = GetAssociatedObject();
    control->GiveFeedback() += MakeDelegate(this, &DragItemBehavior::OnGiveFeedback);
    control->PreviewMouseLeftButtonDown() += MakeDelegate(this, &DragItemBehavior::OnMouseDown);
    control->PreviewMouseLeftButtonUp() += MakeDelegate(this, &DragItemBehavior::OnMouseUp);
    control->PreviewMouseMove() += MakeDelegate(this, &DragItemBehavior::OnMouseMove);
    control->PreviewKeyDown() += MakeDelegate(this, &DragItemBehavior::OnKeyDown);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DragItemBehavior::OnDetaching()
{
    ContentControl* control = GetAssociatedObject();
    control->GiveFeedback() -= MakeDelegate(this, &DragItemBehavior::OnGiveFeedback);
    control->PreviewMouseLeftButtonDown() -= MakeDelegate(this, &DragItemBehavior::OnMouseDown);
    control->PreviewMouseLeftButtonUp() -= MakeDelegate(this, &DragItemBehavior::OnMouseUp);
    control->PreviewMouseMove() -= MakeDelegate(this, &DragItemBehavior::OnMouseMove);
    control->PreviewKeyDown() -= MakeDelegate(this, &DragItemBehavior::OnKeyDown);

    ParentClass::OnAttached();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DragItemBehavior::OnGiveFeedback(BaseComponent*, const GiveFeedbackEventArgs& e)
{
    e.useDefaultCursors = false;
    e.handled = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DragItemBehavior::OnMouseDown(BaseComponent*, const MouseButtonEventArgs&)
{
    _mouseClicked = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DragItemBehavior::OnMouseUp(BaseComponent*, const MouseButtonEventArgs&)
{
    _mouseClicked = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DragItemBehavior::OnMouseMove(BaseComponent*, const MouseEventArgs& e)
{
    if (_mouseClicked)
    {
        ContentControl* control = GetAssociatedObject();
        Slot* slot = (Slot*)control->GetContent();
        if (slot != 0 && slot->GetItem() != 0)
        {
            if (ViewModel::Instance()->StartDragging(slot, e.position))
            {
                DragDrop::DoDragDrop(control, slot, DragDropEffects_Move, [](DependencyObject*,
                    BaseComponent*, UIElement*, const Point&, uint32_t effects)
                {
                    ViewModel::Instance()->EndDragging(effects == DragDropEffects_None);
                });
            }
        }

        _mouseClicked = false;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DragItemBehavior::OnKeyDown(BaseComponent*, const Noesis::KeyEventArgs& e)
{
    if (e.key == Key_Space || e.key == Key_Enter)
    {
        Slot* slot = (Slot*)GetAssociatedObject()->GetContent();
        ViewModel::Instance()->SelectSlot(slot);
    }
    else if (e.key == Key_Escape)
    {
        ViewModel::Instance()->SelectSlot(0);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(DragItemBehavior)
{
    NsMeta<TypeId>("Inventory.DragItemBehavior");
}
