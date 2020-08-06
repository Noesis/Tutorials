# NoesisGUI Unreal Engine User Control Demo

![Demo screenshot](https://noesis.github.io/NoesisGUI/Samples/UserControl/UE4/Screenshot.PNG)

## Introduction

This demo shows how to implement an `UserControl` using XAML and a C++ code-behind. The main focus points of this demo are:

* Shows how to create an `UserControl` with a code-behind class in C++ that implements `DependencyProperty`s and `Event`s.

* Shows how to use the `UseControl` in another XAML.

## Demo Breakdown

### C++ Code

* [NumericUpDown.h](Source/UserControl/NumericUpDown.h) and [NumericUpDown.cpp](Source/UserControl/NumericUpDown.cpp): Implements a code-behind for [NumericUpDown.xaml](Assets/NumericUpDown.xaml). It declares four `DependencyProperty`s (`Value`, `MaxValue`, `MinValue` and `StepValue`) as well as a `RoutedEvent` (`ValueChanged`);

* [MainWindow.h](Source/UserControl/MainWindow.h): Implements a minimal code-behind for [MainWindow.xaml](Assets/MainWindow.xaml).

* [UserControlGame.cpp](Source/UserControl/UserControlGame.cpp): Implements a minimal game module that registers the NoesisGUI native components.

### Blueprint

* `NoesisBlueprint'/Game/UserControls/View.View'`: It's a `NoesisView` for `NoesisXaml'/Game/UserControls/MainWindow.MainWindow'` ([MainWindow.xaml](Assets/MainWindow.xaml)).

![NoesisBlueprint'/Game/UserControls/View.View'](https://noesis.github.io/NoesisGUI/Samples/UserControl/UE4/View.PNG)

* `UserControl - Level Blueprint`: Creates a `Widget` from `NoesisBlueprint'/Game/UserControls/View.View'`, adds it to the viewport and captures mouse input.

![UserControl - Level Blueprint](https://noesis.github.io/NoesisGUI/Samples/UserControl/UE4/LevelBlueprint.PNG)

### Project Settings

* `NoesisGUI Project Settings`: Sets the `NoesisXaml` `NoesisXaml'/Game/Theme/NoesisTheme_DarkBlue.NoesisTheme_DarkBlue'` as the global application `ResourceDictionary`.

![Project Settings](https://noesis.github.io/NoesisGUI/Samples/UserControl/UE4/ProjectSettings.PNG)