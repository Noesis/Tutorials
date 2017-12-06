# NoesisGUI Unreal Engine Widget3D Demo

![Demo screenshot](https://noesis.github.io/NoesisGUI/Samples/Widget3D/UE4/Screenshot.PNG)

## Introduction

This is a demo that shows how to present a `NoesisView` in 3D. This sample makes use of Unreal Engine's First Person package assets and code. The main focus points of this demo are:

* Shows how to create a `Widget` from a `NoesisView` within a `WidgetComponent` and interact with it using a `WidgetInteractionComponent`.

* Shows how to override the default `DataContext` of a `NoesisView`.

## Demo Breakdown

### C++ Code

* [ElementExtensions.h](Source/Widget3D/ElementExtensions.h) and [ElementExtensions.cpp](Source/Widget3D/ElementExtensions.cpp): Implements a `DependencyObject` that allows modifying the behaviour of standard controls via `DependencyProperty`s.

* [MainWindow.h](Source/Widget3D/MainWindow.h): Implements a minimal code-behind for [MainWindow.xaml](Content/MainWindow.xaml).

* [Widget3DGame.cpp](Source/Widget3D/Widget3DGame.cpp): Implements a minimal game module that registers the NoesisGUI native components.

### Blueprint

* `NoesisBlueprint'/Game/MainWindowView.MainWindowView'`: It's a `NoesisView` for `NoesisXaml'/Game/MainWindow.MainWindow'` ([MainWindow.xaml](Content/MainWindow.xaml)).

![NoesisBlueprint'/Game/MainWindowView.MainWindowView'](https://noesis.github.io/NoesisGUI/Samples/Widget3D/UE4/MainWindowView.PNG)

* `Blueprint'/Game/3DWidgetActor.3DWidgetActor'`: It's an `Actor` with two components: a `StaticMeshComponent` and a `WidgetComponent` that uses `NoesisBlueprint'/Game/MainWindowView.MainWindowView'` as its `WidgetClass`. It also sets itself as its `DataContext` by calling `SetDataContext` from its `BeginPlay` event. Implements the `Command`s `StartCommand`, `SettingsCommand` and `ExitCommand` that are used via `Binding`.

![Blueprint'/Game/3DWidgetActor.3DWidgetActor'](https://noesis.github.io/NoesisGUI/Samples/Widget3D/UE4/3DWidgetActor.PNG)

* `Blueprint'/Game/FirstPersonCharacter.FirstPersonCharacter'`: it's a `FP_FirstPersonCharacter` that, amongst other components, has a `WidgetInteractionComponent` that allows it to interact with the UI in the `WidgetComponent`present in `Blueprint'/Game/3DWidgetActor.3DWidgetActor'`. It also has `Blueprint` events that handle changing the crosshair color when the `WidgetComponent` is in range to interact, deciding whether or not the character can shoot, and passing mouse events to the `WidgetInteractionComponent`.

![Blueprint'/Game/FirstPersonCharacter.FirstPersonCharacter'](https://noesis.github.io/NoesisGUI/Samples/Widget3D/UE4/FirstPersonCharacter.PNG)

* `Blueprint'/Game/FirstPersonGameMode.FirstPersonGameMode'`: Sets `Blueprint'/Game/FirstPersonCharacter.FirstPersonCharacter'` as the `DefaultPawnClass`.

![Blueprint'/Game/FirstPersonGameMode.FirstPersonGameMode'](https://noesis.github.io/NoesisGUI/Samples/Widget3D/UE4/FirstPersonGameMode.PNG)

* `World'/Game/TestLevel.TestLevel'`: Sets `Blueprint'/Game/FirstPersonGameMode.FirstPersonGameMode'` as its `GameModeOverride`.

![World'/Game/TestLevel.TestLevel'](https://noesis.github.io/NoesisGUI/Samples/Widget3D/UE4/TestLevel.PNG)