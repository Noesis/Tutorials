# NoesisGUI Unreal Engine Hello World Demo

![Demo screenshot](https://noesis.github.io/NoesisGUI/Samples/HelloWorld/UE4/Screenshot.PNG)

## Introduction

This is a minimal demo that presents a Noesis Xaml to the user. The main focus points of this demo are:

* Shows how to create a `Widget` from a `NoesisView` and add it to the viewport.

## Demo Breakdown

### Blueprint

* `NoesisBlueprint'/Game/HelloWorld/View.View'`: It's a `NoesisView` for `NoesisXaml'/Game/HelloWorld/MainWindow.MainWindow'` ([MainWindow.xaml](Assets/MainWindow.xaml)).

![NoesisBlueprint'/Game/HelloWorld/View.View'](https://noesis.github.io/NoesisGUI/Samples/HelloWorld/UE4/View.PNG)

* `HelloWorld - Level Blueprint`: Creates a `Widget` from `NoesisBlueprint'/Game/HelloWorld/View.View'` and adds it to the viewport.

![HelloWorld - Level Blueprint](https://noesis.github.io/NoesisGUI/Samples/HelloWorld/UE4/LevelBlueprint.PNG)