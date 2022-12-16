# Background Effect Sample

![Screenshot](https://github.com/Noesis/Noesis.github.io/blob/master/NoesisGUI/Samples/BackgroundBlur/Screenshot.jpg)

The [BackgroundEffectBehavior](https://www.noesisengine.com/docs/App.Interactivity._BackgroundEffectBehavior.html) can be attached to Panels, Borders or Shapes to fill their background with the elements beneath, and post-processed with the specified effect, for example a Blur.

```
<Grid
  xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
  xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
  xmlns:b="http://schemas.microsoft.com/xaml/behaviors"
  xmlns:noesis="clr-namespace:NoesisGUIExtensions;assembly=NoesisGUI.GUI.Extensions">
  <Image x:Name="img" Source="Images/landscape.jpg" Stretch="UniformToFill"/>
  <Ellipse Width="600" Height="200">
    <b:Interaction.Behaviors>
      <noesis:BackgroundEffectBehavior Source="{Binding ElementName=img}">
        <BlurEffect Radius="20"/>
      </noesis:BackgroundEffectBehavior>
    </b:Interaction.Behaviors>
  </Ellipse>
</Grid>
```
