# NoesisGUI Unreal Engine Menu3D Demo

![Demo screenshot](https://noesis.github.io/NoesisGUI/Samples/Menu3D/UE4/Screenshot.PNG)

## Introduction

This is a demo that shows how you can use `UserControl`s to implement a multi-panel main game menu. The main focus points of this demo are:

* Shows how to implement `UserControl`s with code-behind classes in C++.

* Shows how to set a global `ResourceDictionary` to be used by all your XAMLs.

* Shows how to use a `BlueprintFunctionLibrary` to extend the possibilities of your `Blueprint` code.



## Demo Breakdown

### C++ Code

* [MainMenu.h](Source/Menu3D/MainMenu.h), [MainMenu.cpp](Source/Menu3D/MainMenu.cpp), [OptionSelector.h](Source/Menu3D/OptionSelector.h), [OptionSelector.cpp](Source/Menu3D/OptionSelector.cpp), [SettingsMenu.h](Source/Menu3D/SettingsMenu.h), [SettingsMenu.cpp](Source/Menu3D/SettingsMenu.cpp), [StartMenu.h](Source/Menu3D/StartMenu.h) and [StartMenu.cpp](Source/Menu3D/StartMenu.cpp): Implement the code-behind classes for the `UserControl`s in the `NoesisXaml`s `NoesisXaml'/Game/MainMenu.MainMenu'`, `NoesisXaml'/Game/OptionSelector.OptionSelector'`, `NoesisXaml'/Game/SettingsMenu.SettingsMenu'` and `NoesisXaml'/Game/StartMenu.StartMenu'`. The most interesting bit is the way in which the classes reference the `NoesisXaml`s that define their structure. This happens in the `InitializeComponent` functions each of these classes have. Note how the Unreal asset is referenced, and not the original XAML file.

* [MainWindow.h](Source/Menu3D/MainWindow.h): Implements a minimal code-behind for [MainWindow.xaml](Content/MainWindow.xaml).

* [Menu3DFunctionLibrary.h](Source/Menu3D/Menu3DFunctionLibrary.h) and [Menu3DFunctionLibrary.cpp](Source/Menu3D/Menu3DFunctionLibrary.cpp): Implements a `BlueprintFunctionLibrary` that exposes the function `SetFocus` to `Blueprint`s. This function uses `NoesisCreateComponentForUObject` to obtain a `BaseComponent` from the `Object` passed from the `Blueprint` code.

* [Menu3DGame.cpp](Source/Menu3D/Menu3DGame.cpp): Implements a minimal game module that registers the NoesisGUI native components.

### Blueprint

* `Blueprint'/Game/Menu3DViewModel.Menu3DViewModel'`: It's an `Object` that is used as the `DataContext` for `NoesisBlueprint'/Game/MainWindowView.MainWindowView'`. It exposes the variable `State` that is used as a property for `Binding`, as well as the `Command`s `FadeInCompleted`, `Start`, `Settings`, `Back`, `Exit`, `StartCasual`, `StartNormal` and `StartVeteran` that are also used in `Binding`s. `FadeInCompleted` receives a parameter that is a `UIElement` to focus on. Even though in the `Blueprint` itself we cannot do anything with it, we can pass it as a parameter to the native function `SetFocus` defined in `Menu3DFunctionLibrary` that can retrieve the NoesisGUI component from the `Object`pointer. 

![Blueprint'/Game/Menu3DViewModel.Menu3DViewModel'](https://noesis.github.io/NoesisGUI/Samples/Menu3D/UE4/ViewModel.PNG)

* `NoesisBlueprint'/Game/MainWindowView.MainWindowView'`: It's a `NoesisView` for `NoesisXaml'/Game/MainWindow.MainWindow'` ([MainWindow.xaml](Content/MainWindow.xaml)). It also creates an object with the `Class` `Blueprint'/Game/Menu3DViewModel.Menu3DViewModel'` and sets it as its `DataContext`.

![NoesisBlueprint'/Game/MainWindowView.MainWindowView'](https://noesis.github.io/NoesisGUI/Samples/Menu3D/UE4/MainWindowView.PNG)

* `TestLevel - Level Blueprint`: Creates a `Widget` from `NoesisBlueprint'/Game/MainWindowView.MainWindowView'`, adds it to the viewport and captures mouse and keyboard input.

![TestLevel - Level Blueprint](https://noesis.github.io/NoesisGUI/Samples/Menu3D/UE4/LevelBlueprint.PNG)

### Project Settings

* `NoesisGUI Project Settings`: Sets the `NoesisXaml` `NoesisXaml'/Game/MenuResources.MenuResources'` as the global application `ResourceDictionary`.

![Project Settings](https://noesis.github.io/NoesisGUI/Samples/Menu3D/UE4/ProjectSettings.PNG)