# NoesisGUI Unreal Engine Localization Demo

![Demo screenshot](https://noesis.github.io/NoesisGUI/Samples/Localization/UE4/Screenshot.PNG)

## Introduction

This demo shows one way to localize your user interface to multiple languages. The main focus points of this demo are:

* Shows how to use `ResourceDictionary`s to map from labels to the actual text to display in the various languages supported.

* Shows how to use the `LoadXaml` function in a `Blueprint` to load the dictionaries.

## Demo Breakdown

### C++ Code

* [LevelToColorConverter.h](Source/Localization/LevelToColorConverter.h): Implements an `IValueConverter` used to convert the `SoundLevel` and `MusicLevel` properties exposed by the view model to colors.

* [MainWindow.h](Source/Localization/MainWindow.h): Implements a minimal code-behind for [MainWindow.xaml](Content/MainWindow.xaml).

* [LocalizationGame.cpp](Source/Localization/LocalizationGame.cpp): Implements a minimal game module that registers the NoesisGUI native components.

### Blueprint

* `NoesisBlueprint'/Game/MainWindowView.MainWindowView'`: It's a `NoesisView` for `NoesisXaml'/Game/MainWindow.MainWindow'` ([MainWindow.xaml](Content/MainWindow.xaml)).

![NoesisBlueprint'/Game/MainWindowView.MainWindowView'](https://noesis.github.io/NoesisGUI/Samples/Localization/UE4/MainWindowView.PNG)

* `Blueprint'/Game/Language.Language'`: This `Object` derived `Blueprint` represents a language for the UI. It exposes two properties, the `Name` of the language and the `Resources`, which are loaded from a `NoesisXaml` using the `LoadXaml` function from the `NoesisFunctionLibrary`.

![Blueprint'/Game/Language.Language'](https://noesis.github.io/NoesisGUI/Samples/Localization/UE4/Language.PNG)

* `Blueprint'/Game/ViewModel.ViewModel'`: An `Object` that is used as the `DataContext` for `NoesisBlueprint'/Game/MainWindowView.MainWindowView'`. It exposes the list of supported `Languages` and the currently `SelectedLanguage`, as well as the previously mentioned `SoundLevel` and `MusicLevel`.

![Blueprint'/Game/Language.Language'](https://noesis.github.io/NoesisGUI/Samples/Localization/UE4/ViewModel.PNG)

* `TestLevel - Level Blueprint`: Creates a `Widget` from `NoesisBlueprint'/Game/MainWindowView.MainWindowView'`, adds it to the viewport and captures mouse input. It also creates several instances of `Blueprint'/Game/Language.Language'` and an instance of `Blueprint'/Game/ViewModel.ViewModel'` that it sets as the `DataContext` of the `Widget`.

![TestLevel - Level Blueprint](https://noesis.github.io/NoesisGUI/Samples/Localization/UE4/LevelBlueprint.PNG)