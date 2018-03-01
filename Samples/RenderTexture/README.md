# RenderTexture Sample

![Screenshot](https://github.com/Noesis/Noesis.github.io/blob/master/NoesisGUI/Samples/RenderTexture/Screenshot.png)

This example shows how to use a Unity's *RenderTexture* to draw 3D scenes as dynamic images inside a XAML.

The 3D scene is rendered to a camera with a RenderTexture target. That texture is used then to create a Noesis *TextureSource* that is asigned to an *ImageBrush.ImageSource* to fill a *Rectangle*.

It also showcases how to use Noesis controls to interact with Unity's game objects. In this example 2 *Buttons* are used to rotate the 3D character around the Y axis.


