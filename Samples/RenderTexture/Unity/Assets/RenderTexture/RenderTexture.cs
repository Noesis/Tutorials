using UnityEngine;
using System;

public class RenderTexture : MonoBehaviour
{
    public UnityEngine.Camera _offscreenCamera;
    public UnityEngine.GameObject _spaceBoy;

    Noesis.Border _titleBar;
    Noesis.TranslateTransform _panelPosition;

    void Start()
    {
        // Find the rectangle where texture will be drawn
        var gui = GetComponent<NoesisGUIPanel>();
        var root = (Noesis.FrameworkElement)gui.GetContent();
        var rect = (Noesis.Rectangle)root.FindName("rtRect");

        // Create render texture
        UnityEngine.RenderTexture renderTexture = new UnityEngine.RenderTexture(
            512, 512, 1, UnityEngine.RenderTextureFormat.Default);
        UnityEngine.RenderTexture.active = renderTexture;

        // Set render texture as camera target
        this._offscreenCamera.targetTexture = renderTexture;
        this._offscreenCamera.aspect = 1;

        // Create brush to store render texture and assign it to the rectangle
        rect.Fill  = new Noesis.ImageBrush()
        {
            ImageSource = new Noesis.TextureSource(renderTexture),
            Stretch = Noesis.Stretch.UniformToFill,
            Opacity = 0.9f
        };

        // Title bar drag to move
        this._titleBar = (Noesis.Border)root.FindName("titleBar");
        this._titleBar.MouseLeftButtonDown += this.OnTitleBarMouseDown;
        this._titleBar.MouseLeftButtonUp += this.OnTitleBarMouseUp;
        this._titleBar.MouseMove += this.OnTitleBarMouseMove;

        var panel = (Noesis.Panel)root.FindName("panel");
        this._panelPosition = (Noesis.TranslateTransform)panel.RenderTransform;

        // Model rotation
        var rotateLeft = (Noesis.RepeatButton)root.FindName("rotateLeft");
        rotateLeft.Click += this.OnRotateLeft;

        var rotateRight = (Noesis.RepeatButton)root.FindName("rotateRight");
        rotateRight.Click += this.OnRotateRight;
    }

    Noesis.Point _lastPosition;

    void OnTitleBarMouseDown(object sender, Noesis.MouseButtonEventArgs e)
    {
        this._titleBar.CaptureMouse();
        this._lastPosition = e.GetPosition(null);
    }

    void OnTitleBarMouseUp(object sender, Noesis.MouseButtonEventArgs e)
    {
        this._titleBar.ReleaseMouseCapture();
    }

    void OnTitleBarMouseMove(object sender, Noesis.MouseEventArgs e)
    {
        if (this._titleBar.GetMouse().Captured == this._titleBar)
        {
            Noesis.Point pos = e.GetPosition(null);
            Noesis.Point delta = pos - this._lastPosition;
            this._lastPosition = pos;

            this._panelPosition.X += delta.X;
            this._panelPosition.Y += delta.Y;
        }
    }

    void OnRotateLeft(object sender, Noesis.RoutedEventArgs e)
    {
        this._spaceBoy.transform.Rotate(Vector3.up, 2.0f);
    }

    void OnRotateRight(object sender, Noesis.RoutedEventArgs e)
    {
        this._spaceBoy.transform.Rotate(Vector3.up, -2.0f);
    }
}
