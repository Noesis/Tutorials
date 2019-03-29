////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __INVENTORY_DRAGITEMBEHAVIOR_H__
#define __INVENTORY_DRAGITEMBEHAVIOR_H__


#include <NsCore/Noesis.h>
#include <NsGui/ContentControl.h>
#include <NsApp/Behavior.h>


namespace Noesis
{
struct GiveFeedbackEventArgs;
struct MouseEventArgs;
struct MouseButtonEventArgs;
struct KeyEventArgs;
}

namespace Inventory
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class DragItemBehavior final: public NoesisApp::BehaviorT<Noesis::ContentControl>
{
public:
    DragItemBehavior();

protected:
    Noesis::Ptr<Freezable> CreateInstanceCore() const override;
    void OnAttached() override;
    void OnDetaching() override;

private:
    void OnGiveFeedback(BaseComponent*, const Noesis::GiveFeedbackEventArgs& e);
    void OnMouseDown(Noesis::BaseComponent* sender, const Noesis::MouseButtonEventArgs& e);
    void OnMouseUp(Noesis::BaseComponent* sender, const Noesis::MouseButtonEventArgs& e);
    void OnMouseMove(Noesis::BaseComponent* sender, const Noesis::MouseEventArgs& e);
    void OnKeyDown(Noesis::BaseComponent* sender, const Noesis::KeyEventArgs& e);

private:
    bool _mouseClicked;

    NS_DECLARE_REFLECTION(DragItemBehavior, Behavior)
};

}


#endif
