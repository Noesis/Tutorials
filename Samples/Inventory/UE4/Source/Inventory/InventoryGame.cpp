////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "InventoryGame.h"
#include "Modules/ModuleManager.h"

#include "AnimatedNumber.h"
#include "DragAdornerBehavior.h"
#include "DragItemBehavior.h"
#include "DropItemBehavior.h"

class InventoryModule : public FDefaultGameModuleImpl
{
    virtual void StartupModule() override
    {
        Noesis::RegisterComponent<Inventory::AnimatedNumber>();
        Noesis::RegisterComponent<Inventory::DragAdornerBehavior>();
        Noesis::RegisterComponent<Inventory::DragItemBehavior>();
        Noesis::RegisterComponent<Inventory::DropItemBehavior>();
    }

    virtual void ShutdownModule() override
    {
        Noesis::UnregisterComponent<Inventory::AnimatedNumber>();
        Noesis::UnregisterComponent<Inventory::DragAdornerBehavior>();
        Noesis::UnregisterComponent<Inventory::DragItemBehavior>();
        Noesis::UnregisterComponent<Inventory::DropItemBehavior>();
    }
};

IMPLEMENT_MODULE(InventoryModule, InventoryModule);
