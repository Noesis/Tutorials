# NoesisGUI Unreal Engine Buttons Demo

![Demo screenshot](https://noesis.github.io/NoesisGUI/Samples/Buttons/UE4/Screenshot.PNG)

## Introduction

This is a simple demo that presents three buttons to the user. The main focus points of this demo are:

* Shows how to create a `Widget` from a `NoesisView`, add it to the viewport and capture mouse and keyboard input.

* Shows how to implement `Command`s as `Blueprint` functions.

## Demo Breakdown

### C++ Code

* [ElementExtensions.h](Source/Buttons/ElementExtensions.h) and [ElementExtensions.cpp](Source/Buttons/ElementExtensions.cpp): Implements a `DependencyObject` that allows modifying the behaviour of standard controls via `DependencyProperty`s.

* [MainWindow.h](Source/Buttons/MainWindow.h): Implements a minimal code-behind for [MainWindow.xaml](Content/MainWindow.xaml).

* [ButtonsGame.cpp](Source/Buttons/ButtonsGame.cpp): Implements a minimal game module that registers the NoesisGUI native components.

### Blueprint

* `NoesisBlueprint'/Game/MainWindowView.MainWindowView'`: It's a `NoesisView` for `NoesisXaml'/Game/MainWindow.MainWindow'` ([MainWindow.xaml](Content/MainWindow.xaml)) and also acts as its `DataContext`. Implements the `Command`s `StartCommand`, `SettingsCommand` and `ExitCommand` that are used via `Binding`.

![NoesisBlueprint'/Game/MainWindowView.MainWindowView'](https://noesis.github.io/NoesisGUI/Samples/Buttons/UE4/MainWindowView.PNG)

* `TestLevel - Level Blueprint`: Creates a `Widget` from `NoesisBlueprint'/Game/MainWindowView.MainWindowView'`, adds it to the viewport and captures mouse and keyboard input.

![TestLevel - Level Blueprint](https://noesis.github.io/NoesisGUI/Samples/Buttons/UE4/LevelBlueprint.PNG)