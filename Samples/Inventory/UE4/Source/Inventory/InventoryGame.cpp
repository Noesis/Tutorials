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
#include "MainWindow.h"

class InventoryGameModule : public FDefaultGameModuleImpl
{
	virtual void StartupModule() override
	{
		NsRegisterComponent<Inventory::AnimatedNumber>();
		NsRegisterComponent<Inventory::DragAdornerBehavior>();
		NsRegisterComponent<Inventory::DragItemBehavior>();
		NsRegisterComponent<Inventory::DropItemBehavior>();
		NsRegisterComponent<Inventory::MainWindow>();
	}

	virtual void ShutdownModule() override
	{
		NsUnregisterComponent<Inventory::AnimatedNumber>();
		NsUnregisterComponent<Inventory::DragAdornerBehavior>();
		NsUnregisterComponent<Inventory::DragItemBehavior>();
		NsUnregisterComponent<Inventory::DropItemBehavior>();
		NsUnregisterComponent<Inventory::MainWindow>();
	}
};

IMPLEMENT_PRIMARY_GAME_MODULE(InventoryGameModule, Inventory, "Inventory" );
