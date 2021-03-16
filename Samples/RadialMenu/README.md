# RadialMenu Sample

![Screenshot](https://github.com/Noesis/Noesis.github.io/blob/master/NoesisGUI/Samples/RadialMenu/Screenshot.png)

A recreation of a radial interface as seen on 'Counterstrike' using NoesisGUI.

This example showcases how to create a radial menu by creating a custom *RadialPanel* and the elements to render *Arc* shapes. Entries of the menu list are populated using *MVVM*.

This design contains the following key elements:

* *RadialPanel*: a *Panel* that can be used as *ItemsPanel* in a *ListBox*. It arranges items in a circular fashion, setting the attached properties *CenterX*, *CenterY*, *AngleStart* and *AngleDelta* on its children.

  ```xml
  <ListBox>
    <ListBox.ItemsPanel>
      <ItemsPanelTemplate>
        <local:RadialPanel/>
      </ItemsPanelTemplate>
    </ListBox.ItemsPanel>
    <ListBox.Template>
      <ControlTemplate TargetType="{x:Type ListBox}">
        <ItemsPresenter/>
      </ControlTemplate>
    </ListBox.Template>
  </ListBox>
  ```

* *RadialItem*: displays items using radial coordinates (*CenterX*, *CenterY*, *AngleStart*, *AngleDelta*, *InnerRadius*, *OuterRadius*, *Offset* and *Padding*).

  ```xml
  <local:RadialItem
    x:Name="ContentHost"
    CenterX="{Binding (local:RadialPanel.CenterX), RelativeSource={RelativeSource TemplatedParent}, FallbackValue=0}"
    CenterY="{Binding (local:RadialPanel.CenterY), RelativeSource={RelativeSource TemplatedParent}, FallbackValue=0}"
    AngleStart="{Binding (local:RadialPanel.AngleStart), RelativeSource={RelativeSource TemplatedParent}, FallbackValue=0}"
    AngleDelta="{Binding (local:RadialPanel.AngleDelta), RelativeSource={RelativeSource TemplatedParent}, FallbackValue=0}"
    Radius="160">
    <ContentPresenter/>
  </local:RadialItem>
  ```

* *Arc*: renders arcs with fill and stroke given *CenterY*, *CenterY*, *AngleStart*, *AngleDelta*, *InnerRadius*, *OuterRadius*, *Offset* and *Padding* properties.

  ```xml
  <local:Arc 
    x:Name="OuterArc"
    CenterX="{Binding (local:RadialPanel.CenterX), RelativeSource={RelativeSource TemplatedParent}, FallbackValue=0}"
    CenterY="{Binding (local:RadialPanel.CenterY), RelativeSource={RelativeSource TemplatedParent}, FallbackValue=0}"
    AngleStart="{Binding (local:RadialPanel.AngleStart), RelativeSource={RelativeSource TemplatedParent}, FallbackValue=0}"
    AngleDelta="{Binding (local:RadialPanel.AngleDelta), RelativeSource={RelativeSource TemplatedParent}, FallbackValue=0}"
    InnerRadius="245"
    OuterRadius="255"
    Padding="5"
    Fill="#B2C7CCD1"/>
  ```
