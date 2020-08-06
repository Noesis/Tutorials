# NoesisGUI Unreal Engine Buttons Demo

![Demo screenshot](https://noesis.github.io/NoesisGUI/Samples/Buttons/UE4/Screenshot.PNG)

## Introduction

This is a simple demo that presents three buttons to the user. The main focus points of this demo are:

* Shows how to create a `Widget` from a `NoesisView`, add it to the viewport and capture mouse and keyboard input.

* Shows how to implement `Command`s as `Blueprint` functions.

## Demo Breakdown

### Blueprint

* `NoesisBlueprint'/Game/Buttons/View.View'`: It's a `NoesisView` for `NoesisXaml'/Game/Buttons/MainWindow.MainWindow'` ([MainWindow.xaml](Assets/MainWindow.xaml)) and also acts as its `DataContext`. Implements the `Command`s `StartCommand`, `SettingsCommand` and `ExitCommand` that are used via `Binding`.

![NoesisBlueprint'/Game/Buttons/View.View'](https://noesis.github.io/NoesisGUI/Samples/Buttons/UE4/View.PNG)

* `Buttons - Level Blueprint`: Creates a `Widget` from `NoesisBlueprint'/Game/Buttons/View.View'`, adds it to the viewport and captures mouse and keyboard input.

![Buttons - Level Blueprint](https://noesis.github.io/NoesisGUI/Samples/Buttons/UE4/LevelBlueprint.PNG)