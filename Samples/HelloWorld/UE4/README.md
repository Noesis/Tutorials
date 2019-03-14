# NoesisGUI Unreal Engine Hello World Demo

![Demo screenshot](https://noesis.github.io/NoesisGUI/Samples/HelloWorld/UE4/Screenshot.PNG)

## Introduction

This is a minimal demo that presents a Noesis Xaml to the user. The main focus points of this demo are:

* Shows how to create a `Widget` from a `NoesisView` and add it to the viewport.

## Demo Breakdown

### Blueprint

* `NoesisBlueprint'/Game/MainWindowView.MainWindowView'`: It's a `NoesisView` for `NoesisXaml'/Game/MainWindow.MainWindow'` ([MainWindow.xaml](Content/MainWindow.xaml)).

![NoesisBlueprint'/Game/MainWindowView.MainWindowView'](https://noesis.github.io/NoesisGUI/Samples/HelloWorld/UE4/MainWindowView.PNG)

* `TestLevel - Level Blueprint`: Creates a `Widget` from `NoesisBlueprint'/Game/MainWindowView.MainWindowView'` and adds it to the viewport.

![TestLevel - Level Blueprint](https://noesis.github.io/NoesisGUI/Samples/HelloWorld/UE4/LevelBlueprint.PNG)