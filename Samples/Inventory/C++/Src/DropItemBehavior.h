////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __INVENTORY_DROPITEMBEHAVIOR_H__
#define __INVENTORY_DROPITEMBEHAVIOR_H__


#include <NsCore/Noesis.h>
#include <NsGui/FrameworkElement.h>
#include <NsApp/Behavior.h>


namespace Noesis
{
class BaseCommand;
class DependencyProperty;
struct DragEventArgs;
}

namespace Inventory
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class DropItemBehavior final: public NoesisApp::BehaviorT<Noesis::FrameworkElement>
{
public:
    bool GetIsDragOver() const;
    void SetIsDragOver(bool value);

    Noesis::BaseCommand* GetDropCommand() const;
    void SetDropCommand(Noesis::BaseCommand* value);

public:
    static const Noesis::DependencyProperty* IsDragOverProperty;
    static const Noesis::DependencyProperty* DropCommandProperty;

protected:
    Noesis::Ptr<Freezable> CreateInstanceCore() const override;
    void OnAttached() override;
    void OnDetaching() override;

private:
    void OnDragEnter(Noesis::BaseComponent* sender, const Noesis::DragEventArgs& e);
    void OnDragLeave(Noesis::BaseComponent* sender, const Noesis::DragEventArgs& e);
    void OnDrop(Noesis::BaseComponent* sender, const Noesis::DragEventArgs& e);

    NS_DECLARE_REFLECTION(DropItemBehavior, Behavior)
};

}


#endif
