# NoesisGUI Unreal Engine Login Demo

![Demo screenshot](https://noesis.github.io/NoesisGUI/Samples/Login/UE4/Screenshot.PNG)

## Introduction

This is a demo that shows how to implement a more complex interaction between native and `Blueprint` code. The main focus points of this demo are:

* Shows how to implement `Command`s with parameters as `Blueprint` functions.

* Shows how to deal with NoesisGUI native objects accross the C++-`Blueprint` border.

## Demo Breakdown

### C++ Code

* [MainWindow.h](Source/Login/MainWindow.h): Implements a minimal code-behind for [MainWindow.xaml](Assets/MainWindow.xaml).

* [LoginFunctionLibrary.h](Source/Login/LoginFunctionLibrary.h) and [LoginFunctionLibrary.cpp](Source/Login/LoginFunctionLibrary.cpp): Implements a `BlueprintFunctionLibrary` that exposes the function `IsPasswordValid` to `Blueprint`s. This function uses `NoesisCreateComponentForUObject` to obtain a `BaseComponent` from the `Object` passed from the `Blueprint` code.

* [LoginGame.cpp](Source/Login/LoginGame.cpp): Implements a minimal game module that registers the NoesisGUI native components.

### Blueprint

* `Blueprint'/Game/Login/LoginModel.LoginModel'`: It's an `Object` that will be used as the `DataContext` for the `NoesisView`. It implements the `LoginCommand` `Command` used by it. This `Command` receives a parameter that is a `PasswordBox`. Even though in the `Blueprint` itself we cannot do anything with it, we can pass it as a parameter to the native function `IsPasswordValid` that can retrieve the NoesisGUI component from the `Object`pointer.

![Blueprint'/Game/Login/LoginModel.LoginModel'](https://noesis.github.io/NoesisGUI/Samples/Login/UE4/LoginModel.PNG)

* `NoesisBlueprint'/Game/Login/View.View'`: It's a `NoesisView` for `NoesisXaml'/Game/Login/MainWindow.MainWindow'` ([MainWindow.xaml](Assets/MainWindow.xaml)). It also creates an object with the `Class` `Blueprint'/Game/Login/LoginModel.LoginModel'` and sets it as its `DataContext`.

![NoesisBlueprint'/Game/Login/View.View'](https://noesis.github.io/NoesisGUI/Samples/Login/UE4/View.PNG)

* `Login - Level Blueprint`: Creates a `Widget` from `NoesisBlueprint'/Game/Login/View.View'`, adds it to the viewport and captures mouse and keyboard input.

![Login - Level Blueprint](https://noesis.github.io/NoesisGUI/Samples/Login/UE4/LevelBlueprint.PNG)

### Project Settings

* `NoesisGUI Project Settings`: Sets the `NoesisXaml` `NoesisXaml'/Game/Login/Resources.Resources'` as the global application `ResourceDictionary`.

![Project Settings](https://noesis.github.io/NoesisGUI/Samples/Login/UE4/ProjectSettings.PNG)