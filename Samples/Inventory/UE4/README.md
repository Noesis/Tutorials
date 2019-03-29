# NoesisGUI Unreal Engine Inventory Demo

![Demo screenshot](https://noesis.github.io/NoesisGUI/Samples/Inventory/UE4/Screenshot.PNG)

## Introduction

This is a demo that shows how to implement a drag and drop based UI forn an inventory system. The main focus points of this demo are:

* Shows how to implement a drag and drop UI for an inventory system.

* Shows how to easily bring a C++ project to Unreal.


## Demo Breakdown

### C++ Code

* [DragAdornerBehavior.h](Source/Inventory/DragAdornerBehavior.h), [DragAdornerBehavior.cpp](Source/Inventory/DragAdornerBehavior.cpp), [DragItemBehavior.h](Source/Inventory/DragItemBehavior.h), [DragItemBehavior.cpp](Source/Inventory/DragItemBehavior.cpp), [DropItemBehavior.h](Source/Inventory/DropItemBehavior.h) and [DropItemBehavior.cpp](Source/Inventory/DropItemBehavior.cpp): Implement `Behavior`s used to modify the associated objects.

* [AnimatedNumber.h](Source/Inventory/AnimatedNumber.h), [AnimatedNumber.cpp](Source/Inventory/AnimatedNumber.cpp): Implement an `UserControl` used for the animated stats for the character.

* [MainWindow.h](Source/Inventory/MainWindow.h): Implements a minimal code-behind for [MainWindow.xaml](Content/MainWindow.xaml).

* [InventoryGame.cpp](Source/Inventory/InventoryGame.cpp): Implements a minimal game module that registers the NoesisGUI native components.

### Blueprint

* `NoesisBlueprint'/Game/MainWindowView.MainWindowView'`: It's a `NoesisView` for `NoesisXaml'/Game/MainWindow.MainWindow'` ([MainWindow.xaml](Content/MainWindow.xaml)). It also creates an object with the `Class` `Blueprint'/Game/Menu3DViewModel.Menu3DViewModel'` and sets it as its `DataContext`.

![NoesisBlueprint'/Game/MainWindowView.MainWindowView'](https://noesis.github.io/NoesisGUI/Samples/Inventory/UE4/MainWindowView.PNG)

* `TestLevel - Level Blueprint`: Creates a `Widget` from `NoesisBlueprint'/Game/MainWindowView.MainWindowView'`, adds it to the viewport and captures mouse and keyboard input.

![TestLevel - Level Blueprint](https://noesis.github.io/NoesisGUI/Samples/Inventory/UE4/LevelBlueprint.PNG)

