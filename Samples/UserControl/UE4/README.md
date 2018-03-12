# NoesisGUI Unreal Engine User Control Demo

![Demo screenshot](https://noesis.github.io/NoesisGUI/Samples/UserControl/UE4/Screenshot.PNG)

## Introduction

This demo shows how to implement an `UserControl` using XAML and a C++ code-behind. The main focus points of this demo are:

* Shows how to create an `UserControl` with a code-behind class in C++ that implements `DependencyProperty`s and `Event`s.

* Shows how to use the `UseControl` in another XAML.

## Demo Breakdown

### C++ Code

* [NumericUpDown.h](Source/UserControl/NumericUpDown.h) and [NumericUpDown.cpp](Source/UserControl/NumericUpDown.cpp): Implements a code-behind for [NumericUpDown.xaml](Content/NumericUpDown.xaml). It declares four `DependencyProperty`s (`Value`, `MaxValue`, `MinValue` and `StepValue`) as well as a `RoutedEvent` (`ValueChanged`);

* [MainWindow.h](Source/UserControl/MainWindow.h): Implements a minimal code-behind for [MainWindow.xaml](Content/MainWindow.xaml).

* [UserControlGame.cpp](Source/UserControl/UserControlGame.cpp): Implements a minimal game module that registers the NoesisGUI native components.

### Blueprint

* `NoesisBlueprint'/Game/MainWindowView.MainWindowView'`: It's a `NoesisView` for `NoesisXaml'/Game/MainWindow.MainWindow'` ([MainWindow.xaml](Content/MainWindow.xaml)).

![NoesisBlueprint'/Game/MainWindowView.MainWindowView'](https://noesis.github.io/NoesisGUI/Samples/UserControl/UE4/MainWindowView.PNG)

* `TestLevel - Level Blueprint`: Creates a `Widget` from `NoesisBlueprint'/Game/MainWindowView.MainWindowView'`, adds it to the viewport and captures mouse input.

![TestLevel - Level Blueprint](https://noesis.github.io/NoesisGUI/Samples/UserControl/UE4/LevelBlueprint.PNG)