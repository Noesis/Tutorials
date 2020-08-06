# NoesisGUI Unreal Engine QuestLog Demo

![Demo screenshot](https://noesis.github.io/NoesisGUI/Samples/QuestLog/UE4/Screenshot.PNG)

## Introduction

This is a demo that shows how you can use `Binding` with user defined types and `Images`. The main focus points of this demo are:

* Shows how to expose `Texture2D`s and `UserDefinedEnum`s as properties for `Binding`.

* Shows how to expose `Array`s of properties as collections that can be used for `Binding`.

## Demo Breakdown

### Blueprint

* `UserDefinedEnum'/Game/QuestLog/QuestDifficulty.QuestDifficulty'`: It's an `UserDefinedEnum` used by `Blueprint'/Game/QuestLog/Quest.Quest'`. Its symbolic values are used within the XAML and are automatically converted to text.

![UserDefinedEnum'/Game/QuestLog/QuestDifficulty.QuestDifficulty'](https://noesis.github.io/NoesisGUI/Samples/QuestLog/UE4/QuestDificulty.PNG)

* `Blueprint'/Game/QuestLog/Quest.Quest'`: `NoesisBlueprint'/Game/QuestLog/View.View'` contains an `Array` of these that it exposes as a property for `Binding`. It contais variables of types `Texture2D` as well as `UserDefinedEnum'/Game/QuestLog/QuestDifficulty.QuestDifficulty'` that are used for `Binding` in the XAML.

![Blueprint'/Game/QuestLog/Quest.Quest'](https://noesis.github.io/NoesisGUI/Samples/QuestLog/UE4/Quest.PNG)

* `NoesisBlueprint'/Game/QuestLog/View.View'`: It's a `NoesisView` for `NoesisXaml'/Game/QuestLog/MainWindow.MainWindow'` ([MainWindow.xaml](Assets/MainWindow.xaml)) and also acts as its `DataContext`. Its variables `Quests` and `SelectedQuest` are used for `Binding`. It also creates and initializes several instances of `Blueprint'/Game/QuestLog/Quest.Quest'` that it adds to the `Quests` and `SelectedQuest` variables of the `NoesisBlueprint'/Game/QuestLog/View.View'` instance. Note the use of the plugin functions `ADDUNIQUE w/ NotifyArrayChanged` and `Set w/ NotifyChanged` instead of the standard `ADDUNIQUE` and `SET`. This is fundamental to let the NoesisGUI runtime that data has changed so it can update its internal data to match.

![NoesisBlueprint'/Game/QuestLog/View.View'](https://noesis.github.io/NoesisGUI/Samples/QuestLog/UE4/View.PNG)

* `QuestLog - Level Blueprint`: Creates a `Widget` from `NoesisBlueprint'/Game/QuestLog/View.View'`, adds it to the viewport and captures mouse and keyboard input.

![QuestLog - Level Blueprint](https://noesis.github.io/NoesisGUI/Samples/QuestLog/UE4/LevelBlueprint.PNG)

### Project Settings

* `NoesisGUI Project Settings`: Sets the `NoesisXaml` `NoesisXaml'/Game/QuestLog/Resources.Resources'` as the global application `ResourceDictionary`.

![Project Settings](https://noesis.github.io/NoesisGUI/Samples/QuestLog/UE4/ProjectSettings.PNG)