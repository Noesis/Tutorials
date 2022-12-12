# Rive Sample

![Screenshot](https://github.com/Noesis/Noesis.github.io/blob/master/NoesisGUI/Samples/Rive/Screenshot.png)

This sample demonstrates how to integrate vector graphics created with [Rive](https://rive.app/) into NoesisGUI.

Rive content defines animated vector graphics and a state machine that can be managed from the XAML using bindings and interaction triggers. The rive scene is rendered in NoesisGUI with a [RiveControl](https://www.noesisengine.com/docs/App.RiveControl._RiveControl.html) which exposes a list of [inputs](https://www.noesisengine.com/docs/App.RiveControl._RiveInput.html) (bool and float) to control the state machine and animations:

```
<Grid
  xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
  xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
  xmlns:noesis="clr-namespace:NoesisGUIExtensions;assembly=Noesis.GUI.Extensions">
  <noesis:RiveControl Source="player.riv">
    <noesis:RiveInput InputName="Life" InputValue="{Binding PlayerLife}"/>
  </noesis:RiveControl>
</Grid>
```

The Rive scene can also define triggers that can be fired by the UI using interactivity [actions](https://www.noesisengine.com/docs/App.RiveControl._RiveTriggerAction.html):

```
<Grid
  xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
  xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
  xmlns:b="http://schemas.microsoft.com/xaml/behaviors"
  xmlns:noesis="clr-namespace:NoesisGUIExtensions;assembly=Noesis.GUI.Extensions">
  <noesis:RiveControl x:Name="rive" Source="player.riv"/>
  <Button Content="{Binding PlayerName}">
    <b:Interaction.Triggers>
      <b:EventTrigger EventName="Click">
        <noesis:RiveTriggerAction TargetName="rive" TriggerName="Fire"/>
      </b:EventTrigger>
    </b:Interaction.Triggers>
  </Button>
</Grid>
```

