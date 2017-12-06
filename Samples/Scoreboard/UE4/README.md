# NoesisGUI Unreal Engine Scoreboard Demo

![Demo screenshot](https://noesis.github.io/NoesisGUI/Samples/Scoreboard/UE4/Screenshot.PNG)

## Introduction

This is a demo that shows how you can use `Binding` with properties implemented as `Get` functions. The main focus points of this demo are:

* Shows how to expose properties using `Get` functions.

* Shows how to use manual notifications to keep the UI in sync when the underlying data changes.

## Demo Breakdown

### C++ Code

* [ThousandConverter.h](Source/Scoreboard/ThousandConverter.h) and [ThousandConverter.cpp](Source/Scoreboard/ThousandConverter.cpp): Implements a `BaseValueConverter` that is used to modify how numbers are displayed.

* [MainWindow.h](Source/Scoreboard/MainWindow.h): Implements a minimal code-behind for [MainWindow.xaml](Content/MainWindow.xaml).

* [ScoreboardGame.cpp](Source/Scoreboard/ScoreboardGame.cpp): Implements a minimal game module that registers the NoesisGUI native components.

### Blueprint

* `Blueprint'/Game/Game.Game'`: It's an `Object` that is used as the `DataContext` for `NoesisBlueprint'/Game/MainWindowView.MainWindowView'`. It exposes several variables that are used as properties for `Binding`, such as `Name`, `ElapsedTime` and `Players`, but it also exposes the properties `AllianceScore` and `HordeScore` through the functions `GetAllianceScore` and `GetHordeScore`. These two properties are computed by traversing the `Players` `Array` and adding the individual scores. Since the value of these properties will change when the `Players` `Array` is modified, and we can't use the custom `Blueprint` node `Set w/ NotifyChanged` because they are not implemented as a variable, we have to manually notify NoesisGUI of the changes to those properties whenever `Players` changes. We can see that in the functions `AddPlayer` and `RemovePlayer`. In those we can see how we use the nodes `ADD w/ NotifyArrayChanged` and `REMOVE w/ NotifyArrayChanged` for the property `Players` itself, but for `AllianceScore` and `HordeScore` we must do so manually using the function `NotifyChanged`.

![Blueprint'/Game/Game.Game'](https://noesis.github.io/NoesisGUI/Samples/Scoreboard/UE4/Game.PNG)

* `NoesisBlueprint'/Game/MainWindowView.MainWindowView'`: It's a `NoesisView` for `NoesisXaml'/Game/MainWindow.MainWindow'` ([MainWindow.xaml](Content/MainWindow.xaml)).

![NoesisBlueprint'/Game/MainWindowView.MainWindowView'](https://noesis.github.io/NoesisGUI/Samples/Scoreboard/UE4/MainWindowView.PNG)

* `TestLevel - Level Blueprint`: Creates a `Widget` from `NoesisBlueprint'/Game/MainWindowView.MainWindowView'`, adds it to the viewport and captures mouse and keyboard input. It also creates and initializes an instance of `Blueprint'/Game/Game.Game` and sets it as its `DataContext`, and several instances of `Blueprint'/Game/Player.Player'` that it adds and removes calling the functions `AddPlayer` and `RemovePlayer` discussed above. It adds and removes players over the course of 10 seconds, so the effect of the notifications is visible. You can experiment by removing the manual notifications and observing that the team scores at the top don't change as the number of players varies.

![TestLevel - Level Blueprint](https://noesis.github.io/NoesisGUI/Samples/Scoreboard/UE4/LevelBlueprint.PNG)