# NoesisGUI Unreal Engine Scoreboard Demo

![Demo screenshot](https://noesis.github.io/NoesisGUI/Samples/Scoreboard/UE4/Screenshot.PNG)

## Introduction

This is a demo that shows how you can use `Binding` with properties implemented as `Get` functions. The main focus points of this demo are:

* Shows how to expose properties using `Get` functions.

* Shows how to use manual notifications to keep the UI in sync when the underlying data changes.

## Demo Breakdown

### Blueprint

* `Blueprint'/Game/Scoreboard/Game.Game'`: It's an `Object` that is used as the `DataContext` for `NoesisBlueprint'/Game/Scoreboard/View.View'`. It exposes several variables that are used as properties for `Binding`, such as `Name`, `ElapsedTime` and `Players`, but it also exposes the properties `AllianceScore` and `HordeScore` through the functions `GetAllianceScore` and `GetHordeScore`. These two properties are computed by traversing the `Players` `Array` and adding the individual scores. Since the value of these properties will change when the `Players` `Array` is modified, and we can't use the custom `Blueprint` node `Set w/ NotifyChanged` because they are not implemented as a variable, we have to manually notify NoesisGUI of the changes to those properties whenever `Players` changes. We can see that in the functions `AddPlayer` and `RemovePlayer`. In those we can see how we use the nodes `ADD w/ NotifyArrayChanged` and `REMOVE w/ NotifyArrayChanged` for the property `Players` itself, but for `AllianceScore` and `HordeScore` we must do so manually using the function `NotifyChanged`.

![Blueprint'/Game/Scoreboard/Game.Game'](https://noesis.github.io/NoesisGUI/Samples/Scoreboard/UE4/Game.PNG)

* `NoesisBlueprint'/Game/Scoreboard/View.View'`: It's a `NoesisView` for `NoesisXaml'/Game/Scoreboard/MainWindow.MainWindow'` ([MainWindow.xaml](Assets/MainWindow.xaml)). It also creates and initializes an instance of `Blueprint'/Game/Scoreboard/Game.Game` and sets it as its `DataContext`, and several instances of `Blueprint'/Game/Scoreboard/Player.Player'` that it adds calling the function `AddPlayer` discussed above.

![NoesisBlueprint'/Game/Scoreboard/View.View'](https://noesis.github.io/NoesisGUI/Samples/Scoreboard/UE4/View.PNG)

* `Scoreboard - Level Blueprint`: Creates a `Widget` from `NoesisBlueprint'/Game/Scoreboard/View.View'`, adds it to the viewport and captures mouse and keyboard input.  After 5 seconds it removes a player from the `NoesisView`'s `DataContext` using the function `RemovePlayer` discussed above, so the effect of the notifications is visible. You can experiment by removing the manual notifications and observing that the team scores at the top don't change as the number of players varies.

![Scoreboard - Level Blueprint](https://noesis.github.io/NoesisGUI/Samples/Scoreboard/UE4/LevelBlueprint.PNG)