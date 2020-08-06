# NoesisGUI Unreal Engine Widget3D Demo

![Demo screenshot](https://noesis.github.io/NoesisGUI/Samples/Widget3D/UE4/Screenshot.PNG)

## Introduction

This is a demo that shows how to present a `NoesisView` in 3D. This sample makes use of Unreal Engine's First Person package assets and code. The main focus points of this demo are:

* Shows how to create a `Widget` from a `NoesisView` within a `WidgetComponent` and interact with it using a `WidgetInteractionComponent`.

* Shows how to override the default `DataContext` of a `NoesisView`.

## Demo Breakdown

### Blueprint

* `NoesisBlueprint'/Game/Widget3D/View.View'`: It's a `NoesisView` for `NoesisXaml'/Game/Widget3D/MainWindow.MainWindow'` ([MainWindow.xaml](Assets/MainWindow.xaml)).

![NoesisBlueprint'/Game/Widget3D/View.View'](https://noesis.github.io/NoesisGUI/Samples/Widget3D/UE4/View.PNG)

* `Blueprint'/Game/Widget3D/3DWidgetActor.3DWidgetActor'`: It's an `Actor` with two components: a `StaticMeshComponent` and a `WidgetComponent` that uses `NoesisBlueprint'/Game/Widget3D/View.View'` as its `WidgetClass`. It also sets itself as its `DataContext` by calling `SetDataContext` from its `BeginPlay` event. Implements the `Command`s `StartCommand`, `SettingsCommand` and `ExitCommand` that are used via `Binding`.

![Blueprint'/Game/Widget3D/3DWidgetActor.3DWidgetActor'](https://noesis.github.io/NoesisGUI/Samples/Widget3D/UE4/3DWidgetActor.PNG)

* `Blueprint'/Game/Widget3D/Widget3DCharacter.Widget3DCharacter'`: it's a `FirstPersonCharacter` that, amongst other components, has a `WidgetInteractionComponent` that allows it to interact with the UI in the `WidgetComponent`present in `Blueprint'/Game/Widget3D/3DWidgetActor.3DWidgetActor'`. It also has `Blueprint` events that handle changing the crosshair color when the `WidgetComponent` is in range to interact, deciding whether or not the character can shoot, and passing mouse events to the `WidgetInteractionComponent`.

![Blueprint'/Game/Widget3D/Widget3DCharacter.Widget3DCharacter'](https://noesis.github.io/NoesisGUI/Samples/Widget3D/UE4/Widget3DCharacter.PNG)

* `Blueprint'/Game/Widget3D/FirstPersonGameMode.Widget3DGameMode'`: Sets `Blueprint'/Game/Widget3D/Widget3DCharacter.Widget3DCharacter'` as the `DefaultPawnClass`.

![Blueprint'/Game/Widget3D/Widget3DGameMode.Widget3DGameMode'](https://noesis.github.io/NoesisGUI/Samples/Widget3D/UE4/Widget3DGameMode.PNG)

* `World'/Game/Widget3D/Widget3D.Widget3D'`: Sets `Blueprint'/Game/Widget3D/Widget3DGameMode.Widget3DGameMode'` as its `GameModeOverride`.

![World'/Game/Widget3D/Widget3D.Widget3D'](https://noesis.github.io/NoesisGUI/Samples/Widget3D/UE4/Widget3D.PNG)