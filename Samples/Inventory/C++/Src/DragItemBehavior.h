////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __INVENTORY_DRAGITEMBEHAVIOR_H__
#define __INVENTORY_DRAGITEMBEHAVIOR_H__


#include <NsCore/Noesis.h>
#include <NsGui/FrameworkElement.h>
#include <NsApp/Behavior.h>


namespace Noesis
{
class BaseCommand;
struct GiveFeedbackEventArgs;
struct MouseEventArgs;
struct MouseButtonEventArgs;
struct Point;
}

namespace Inventory
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class DragItemBehavior final: public NoesisApp::BehaviorT<Noesis::FrameworkElement>
{
public:
    DragItemBehavior();

    const Noesis::Point& GetDragStartOffset() const;
    void SetDragStartOffset(const Noesis::Point& offset);

    Noesis::BaseCommand* GetStartDragCommand() const;
    void SetStartDragCommand(Noesis::BaseCommand* command);

    Noesis::BaseCommand* GetEndDragCommand() const;
    void SetEndDragCommand(Noesis::BaseCommand* command);

protected:
    Noesis::Ptr<Freezable> CreateInstanceCore() const override;
    void OnAttached() override;
    void OnDetaching() override;

public:
    static const Noesis::DependencyProperty* DragStartOffsetProperty;
    static const Noesis::DependencyProperty* StartDragCommandProperty;
    static const Noesis::DependencyProperty* EndDragCommandProperty;

private:
    void OnGiveFeedback(BaseComponent*, const Noesis::GiveFeedbackEventArgs& e);
    void OnMouseDown(Noesis::BaseComponent* sender, const Noesis::MouseButtonEventArgs& e);
    void OnMouseUp(Noesis::BaseComponent* sender, const Noesis::MouseButtonEventArgs& e);
    void OnMouseMove(Noesis::BaseComponent* sender, const Noesis::MouseEventArgs& e);

private:
    bool _mouseClicked;

    NS_DECLARE_REFLECTION(DragItemBehavior, Behavior)
};

}


#endif
