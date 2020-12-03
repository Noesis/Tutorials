# NineSlice Control Sample

![Screenshot](https://raw.githubusercontent.com/Noesis/Noesis.github.io/master/NoesisGUI/Samples/NineSlice/Screenshot.png)

This app shows how to implement a 9-Slice image control. When rendering a 9-Slice image, you can specify how different areas of the image are stretched. This feature is useful for preserving the detail on image corners when an image scales or stretches. The *Slices* property specifies the lengths for the left, top, right and bottom corners.

```
<local:NineSliceImage Width="320" Height="300" ImageSource="Sign.png" Slices="60,80,55,45" />
```
