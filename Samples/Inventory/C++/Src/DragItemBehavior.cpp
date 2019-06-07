////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "DragItemBehavior.h"

#include <NsCore/ReflectionImplement.h>
#include <NsCore/TypeId.h>
#include <NsCore/Delegate.h>
#include <NsGui/DragDrop.h>
#include <NsGui/UIElementData.h>
#include <NsGui/PropertyMetadata.h>
#include <NsGui/BaseCommand.h>
#include <NsDrawing/Point.h>


using namespace Inventory;
using namespace Noesis;


////////////////////////////////////////////////////////////////////////////////////////////////////
DragItemBehavior::DragItemBehavior(): _mouseClicked(false)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const Point& DragItemBehavior::GetDragStartOffset() const
{
    return GetValue<Point>(DragStartOffsetProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DragItemBehavior::SetDragStartOffset(const Point& offset)
{
    SetValue<Point>(DragStartOffsetProperty, offset);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
BaseCommand* DragItemBehavior::GetStartDragCommand() const
{
    return GetValue<Ptr<BaseCommand>>(StartDragCommandProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DragItemBehavior::SetStartDragCommand(BaseCommand* command)
{
    SetValue<Ptr<BaseCommand>>(StartDragCommandProperty, command);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
BaseCommand* DragItemBehavior::GetEndDragCommand() const
{
    return GetValue<Ptr<BaseCommand>>(EndDragCommandProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DragItemBehavior::SetEndDragCommand(BaseCommand* command)
{
    SetValue<Ptr<BaseCommand>>(EndDragCommandProperty, command);
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

    FrameworkElement* element = GetAssociatedObject();
    element->GiveFeedback() += MakeDelegate(this, &DragItemBehavior::OnGiveFeedback);
    element->PreviewMouseLeftButtonDown() += MakeDelegate(this, &DragItemBehavior::OnMouseDown);
    element->PreviewMouseLeftButtonUp() += MakeDelegate(this, &DragItemBehavior::OnMouseUp);
    element->PreviewMouseMove() += MakeDelegate(this, &DragItemBehavior::OnMouseMove);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DragItemBehavior::OnDetaching()
{
    FrameworkElement* element = GetAssociatedObject();
    element->GiveFeedback() -= MakeDelegate(this, &DragItemBehavior::OnGiveFeedback);
    element->PreviewMouseLeftButtonDown() -= MakeDelegate(this, &DragItemBehavior::OnMouseDown);
    element->PreviewMouseLeftButtonUp() -= MakeDelegate(this, &DragItemBehavior::OnMouseUp);
    element->PreviewMouseMove() -= MakeDelegate(this, &DragItemBehavior::OnMouseMove);

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
    if (!_mouseClicked)
    {
        return;
    }

    _mouseClicked = false;

    FrameworkElement* element = GetAssociatedObject();
    BaseComponent* item = element->GetDataContext();
    if (item != 0)
    {
        BaseCommand* startDrag = GetStartDragCommand();
        if (startDrag != 0 && startDrag->CanExecute(item))
        {
            SetDragStartOffset(element->PointFromScreen(e.position));

            startDrag->Execute(item);

            DragDrop::DoDragDrop(element, item, DragDropEffects_Move, [this](DependencyObject*,
                BaseComponent*, UIElement*, const Point&, uint32_t effects)
            {
                Ptr<BaseComponent> dragSuccess = Boxing::Box<bool>(effects != DragDropEffects_None);
                BaseCommand* endDrag = GetEndDragCommand();
                if (endDrag != 0 && endDrag->CanExecute(dragSuccess))
                {
                    endDrag->Execute(dragSuccess);
                }
            });
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(DragItemBehavior)
{
    NsMeta<TypeId>("Inventory.DragItemBehavior");

    UIElementData* data = NsMeta<UIElementData>(TypeOf<SelfClass>());
    data->RegisterProperty<Point>(DragStartOffsetProperty, "DragStartOffset",
        PropertyMetadata::Create(Point(0.0f, 0.0f)));
    data->RegisterProperty<Ptr<BaseCommand>>(StartDragCommandProperty, "StartDragCommand",
        PropertyMetadata::Create(Ptr<BaseCommand>()));
    data->RegisterProperty<Ptr<BaseCommand>>(EndDragCommandProperty, "EndDragCommand",
        PropertyMetadata::Create(Ptr<BaseCommand>()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* DragItemBehavior::DragStartOffsetProperty;
const Noesis::DependencyProperty* DragItemBehavior::StartDragCommandProperty;
const Noesis::DependencyProperty* DragItemBehavior::EndDragCommandProperty;
