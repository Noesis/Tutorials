# NoesisGUI Unreal Engine Localization Demo

![Demo screenshot](https://noesis.github.io/NoesisGUI/Samples/Localization/UE4/Screenshot.PNG)

## Introduction

This demo shows one way to localize your user interface to multiple languages. The main focus points of this demo are:

* Shows how to use `ResourceDictionary`s to map from labels to the actual text to display in the various languages supported.

* Shows how to use the `LoadXaml` function in a `Blueprint` to load the dictionaries.

## Demo Breakdown

### C++ Code

* [LevelToColorConverter.h](Source/Localization/LevelToColorConverter.h): Implements an `IValueConverter` used to convert the `SoundLevel` and `MusicLevel` properties exposed by the view model to colors.

* [MainWindow.h](Source/Localization/MainWindow.h): Implements a minimal code-behind for [MainWindow.xaml](Assets/MainWindow.xaml).

* [LocalizationGame.cpp](Source/Localization/LocalizationGame.cpp): Implements a minimal game module that registers the NoesisGUI native components.

### Blueprint

* `NoesisBlueprint'/Game/Localization/View.View'`: It's a `NoesisView` for `NoesisXaml'/Game/Localization/MainWindow.MainWindow'` ([MainWindow.xaml](Assets/MainWindow.xaml)). It also creates several instances of `Blueprint'/Game/Localization/Language.Language'` and an instance of `Blueprint'/Game/Localization/ViewModel.ViewModel'` that it sets as its `DataContext`.

![NoesisBlueprint'/Game/Localization/View.View'](https://noesis.github.io/NoesisGUI/Samples/Localization/UE4/View.PNG)

* `Blueprint'/Game/Localization/Language.Language'`: This `Object` derived `Blueprint` represents a language for the UI. It exposes two properties, the `Name` of the language and the `Resources`, which are loaded from a `NoesisXaml` using the `LoadXaml` function from the `NoesisFunctionLibrary`.

![Blueprint'/Game/Localization/Language.Language'](https://noesis.github.io/NoesisGUI/Samples/Localization/UE4/Language.PNG)

* `Blueprint'/Game/Localization/ViewModel.ViewModel'`: An `Object` that is used as the `DataContext` for `NoesisBlueprint'/Game/Localization/View.View'`. It exposes the list of supported `Languages` and the currently `SelectedLanguage`, as well as the previously mentioned `SoundLevel` and `MusicLevel`.

![Blueprint'/Game/Localization/Language.Language'](https://noesis.github.io/NoesisGUI/Samples/Localization/UE4/ViewModel.PNG)

* `Localization - Level Blueprint`: Creates a `Widget` from `NoesisBlueprint'/Game/Localization/View.View'`, adds it to the viewport and captures mouse input.

![Localization - Level Blueprint](https://noesis.github.io/NoesisGUI/Samples/Localization/UE4/LevelBlueprint.PNG)