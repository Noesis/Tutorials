# Localization Sample

![Screenshot](https://github.com/Noesis/Noesis.github.io/blob/master/NoesisGUI/Samples/Localization/Screenshot.png)

There are many ways to implement localization in NoesisGUI. In this example we are using **Data Binding**.

Each language is stored in a *ResourceDictionary* containing localized texts for each entry. The desired language is selected in the root *DataContext*. Each time the language is changed, the displayed text is updated accordingly.
