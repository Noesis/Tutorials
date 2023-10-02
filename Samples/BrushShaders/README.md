# BrushShaders Sample

![Screenshot](https://github.com/Noesis/Noesis.github.io/blob/master/NoesisGUI/Samples/BrushShaders/Screenshot.png)

This sample demonstrates how to use *Shaders* to add awesome effects to fill any geometry.

This is a NoesisGUI [extension](https://www.noesisengine.com/docs/Gui.Core._BrushShader.html) that allows the creation of custom brushes using pixel shaders. It is applied through an ImageBrush as follows:

```
<Grid
  xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
  xmlns:noesis="clr-namespace:NoesisGUIExtensions;assembly=Noesis.GUI.Extensions"
  xmlns:local="clr-namespace:CustomBrushes">

  <Rectangle Width="300" Height="300">
    <Rectangle.Fill>
      <ImageBrush ImageSource="Images/image.jpg">
        <noesis:Brush.Shader>
          <local:WaveBrushShader Frequency="0.7" />
        </noesis:Brush.Shader>
      </ImageBrush>
    </Rectangle.Fill>
  </Rectangle>

</Grid>
```
