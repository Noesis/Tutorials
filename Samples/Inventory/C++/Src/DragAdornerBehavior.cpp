////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "DragAdornerBehavior.h"
#include "ViewModel.h"

#include <NsCore/ReflectionImplement.h>
#include <NsCore/TypeId.h>
#include <NsCore/Delegate.h>
#include <NsGui/DragDrop.h>


using namespace Inventory;
using namespace Noesis;


////////////////////////////////////////////////////////////////////////////////////////////////////
Ptr<Freezable> DragAdornerBehavior::CreateInstanceCore() const
{
    return *new DragAdornerBehavior();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DragAdornerBehavior::OnAttached()
{
    ParentClass::OnAttached();

    ContentControl* control = GetAssociatedObject();
    control->SetAllowDrop(true);
    control->DragOver() += MakeDelegate(this, &DragAdornerBehavior::OnDragOver);
    control->Drop() += MakeDelegate(this, &DragAdornerBehavior::OnDrop);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DragAdornerBehavior::OnDetaching()
{
    ContentControl* control = GetAssociatedObject();
    control->ClearLocalValue(UIElement::AllowDropProperty);
    control->DragOver() -= MakeDelegate(this, &DragAdornerBehavior::OnDragOver);
    control->Drop() -= MakeDelegate(this, &DragAdornerBehavior::OnDrop);

    ParentClass::OnDetaching();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DragAdornerBehavior::OnDragOver(BaseComponent*, const DragEventArgs& e)
{
    Point position = e.GetPosition(GetAssociatedObject());
    ViewModel::Instance()->SetDraggedItemX(position.x);
    ViewModel::Instance()->SetDraggedItemY(position.y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DragAdornerBehavior::OnDrop(BaseComponent*, const DragEventArgs& e)
{
    e.effects = DragDropEffects_None;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(DragAdornerBehavior)
{
    NsMeta<TypeId>("Inventory.DragAdornerBehavior");
}
