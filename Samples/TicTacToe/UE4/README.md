# NoesisGUI Unreal Engine TicTacToe Demo

![Demo screenshot](https://noesis.github.io/NoesisGUI/Samples/TicTacToe/UE4/Screenshot.PNG)

## Introduction

This is a demo that shows how you can implement the classic game Tic-Tac-Toe using XAML. The main focus points of this demo are:

* Shows how to implement complex logic and state management using mostly XAML.

* Shows how to implement `Command`s that take a simple parameter in `Blueprint` code.


## Demo Breakdown

### Blueprint

* `UserDefinedEnum'/Game/TicTacToe/State.State'`: It's an `UserDefinedEnum` used by `NoesisBlueprint'/Game/TicTacToe/View.View'`. Its symbolic values are used within the XAML to handle the game logic.

![UserDefinedEnum'/Game/TicTacToe/State.State'](https://noesis.github.io/NoesisGUI/Samples/TicTacToe/UE4/State.PNG)

* `NoesisBlueprint'/Game/TicTacToe/View.View'`: It's a `NoesisView` for `NoesisXaml'/Game/TicTacToe/MainWindow.MainWindow'` ([MainWindow.xaml](Assets/MainWindow.xaml)) and also acts as its `DataContext`. Implements the `Command`s `Start` and `Check` that are used via `Binding`. `Check` takes an `Integer` parameter that is passed from the XAML.

![NoesisBlueprint'/Game/TicTacToe/View.View'](https://noesis.github.io/NoesisGUI/Samples/TicTacToe/UE4/View.PNG)

* `TicTacToe - Level Blueprint`: Creates a `Widget` from `NoesisBlueprint'/Game/TicTacToe/View.View'`, adds it to the viewport and captures mouse and keyboard input.

![TicTacToe - Level Blueprint](https://noesis.github.io/NoesisGUI/Samples/TicTacToe/UE4/LevelBlueprint.PNG)

