# NoesisGUI Unreal Engine QuestLog Demo

![Demo screenshot](https://noesis.github.io/NoesisGUI/Samples/QuestLog/UE4/Screenshot.PNG)

## Introduction

This is a demo that shows how you can use `Binding` with user defined types and `Images`. The main focus points of this demo are:

* Shows how to expose `Texture2D`s and `UserDefinedEnum`s as properties for `Binding`.

* Shows how to expose `Array`s of properties as collections that can be used for `Binding`.

## Demo Breakdown

### Blueprint

* `UserDefinedEnum'/Game/QuestDifficulty.QuestDifficulty'`: It's an `UserDefinedEnum` used by `Blueprint'/Game/Quest.Quest'`. Its symbolic values are used within the XAML and are automatically converted to text.

![UserDefinedEnum'/Game/QuestDifficulty.QuestDifficulty'](https://noesis.github.io/NoesisGUI/Samples/QuestLog/UE4/QuestDificulty.PNG)

* `Blueprint'/Game/Quest.Quest'`: `NoesisBlueprint'/Game/MainWindowView.MainWindowView'` contains an `Array` of these that it exposes as a property for `Binding`. It contais variables of types `Texture2D` as well as `UserDefinedEnum'/Game/QuestDifficulty.QuestDifficulty'` that are used for `Binding` in the XAML.

![Blueprint'/Game/Quest.Quest'](https://noesis.github.io/NoesisGUI/Samples/QuestLog/UE4/Quest.PNG)

* `NoesisBlueprint'/Game/MainWindowView.MainWindowView'`: It's a `NoesisView` for `NoesisXaml'/Game/MainWindow.MainWindow'` ([MainWindow.xaml](Content/MainWindow.xaml)) and also acts as its `DataContext`. Its variables `Quests` and `SelectedQuest` are used for `Binding`.

![NoesisBlueprint'/Game/MainWindowView.MainWindowView'](https://noesis.github.io/NoesisGUI/Samples/QuestLog/UE4/MainWindowView.PNG)

* `TestLevel - Level Blueprint`: Creates a `Widget` from `NoesisBlueprint'/Game/MainWindowView.MainWindowView'`, adds it to the viewport and captures mouse and keyboard input. It also creates and initializes several instances of `Blueprint'/Game/Quest.Quest'` that it adds to the `Quests` and `SelectedQuest` variables of the `NoesisBlueprint'/Game/MainWindowView.MainWindowView'` instance. Note the use of the plugin functions `ADDUNIQUE w/ NotifyArrayChanged` and `Set w/ NotifyChanged` instead of the standard `ADDUNIQUE` and `SET`. This is fundamental to let the NoesisGUI runtime that data has changed so it can update its internal data to match.

![TestLevel - Level Blueprint](https://noesis.github.io/NoesisGUI/Samples/QuestLog/UE4/LevelBlueprint.PNG)

### Project Settings

* `NoesisGUI Project Settings`: Sets the `NoesisXaml` `NoesisXaml'/Game/Resources.Resources'` as the global application `ResourceDictionary`.

![Project Settings](https://noesis.github.io/NoesisGUI/Samples/QuestLog/UE4/ProjectSettings.PNG)