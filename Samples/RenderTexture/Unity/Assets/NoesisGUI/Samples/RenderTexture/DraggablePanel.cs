using UnityEngine;
using Noesis;
using System;

public class DraggablePanel : MonoBehaviour
{
    public UnityEngine.Camera _offscreenCamera;
    public UnityEngine.GameObject _spaceBoy;

    void Start()
    {
        // Get view component
        var view = GetComponent<NoesisView>();

        // Find the rectangle where texture will be drawn
        var rect = (Rectangle)view.Content.FindName("rtRect");

        // Create render texture
        UnityEngine.RenderTexture renderTexture = new UnityEngine.RenderTexture(
            512, 512, 1, UnityEngine.RenderTextureFormat.Default);
        UnityEngine.RenderTexture.active = renderTexture;

        // Set render texture as camera target
        this._offscreenCamera.targetTexture = renderTexture;
        this._offscreenCamera.aspect = 1;

        // Create Noesis texture
        renderTexture.Create();
        var tex = Noesis.Texture.WrapTexture(renderTexture, renderTexture.GetNativeTexturePtr(),
            renderTexture.width, renderTexture.height, 1);

        // Create brush to store render texture and assign it to the rectangle
        rect.Fill = new ImageBrush()
        {
            ImageSource = new TextureSource(tex),
            Stretch = Stretch.UniformToFill,
            Opacity = 0.9f
        };

        // Title bar drag to move
        this._titleBar = (Border)view.Content.FindName("titleBar");
        this._titleBar.MouseLeftButtonDown += this.OnTitleBarMouseDown;
        this._titleBar.MouseLeftButtonUp += this.OnTitleBarMouseUp;
        this._titleBar.MouseMove += this.OnTitleBarMouseMove;

        var panel = (Panel)view.Content.FindName("panel");
        this._panelPosition = (TranslateTransform)panel.RenderTransform;

        // Model rotation
        var rotateLeft = (RepeatButton)view.Content.FindName("rotateLeft");
        rotateLeft.Click += this.OnRotateLeft;

        var rotateRight = (RepeatButton)view.Content.FindName("rotateRight");
        rotateRight.Click += this.OnRotateRight;
    }

    void OnTitleBarMouseDown(object sender, MouseButtonEventArgs e)
    {
        this._titleBar.CaptureMouse();
        this._lastPosition = e.GetPosition(null);
    }

    void OnTitleBarMouseUp(object sender, MouseButtonEventArgs e)
    {
        this._titleBar.ReleaseMouseCapture();
    }

    void OnTitleBarMouseMove(object sender, MouseEventArgs e)
    {
        if (this._titleBar.Mouse.Captured == this._titleBar)
        {
            Point pos = e.GetPosition(null);
            Vector delta = pos - this._lastPosition;
            this._lastPosition = pos;

            this._panelPosition.X += delta.X;
            this._panelPosition.Y += delta.Y;
        }
    }

    void OnRotateLeft(object sender, RoutedEventArgs e)
    {
        this._spaceBoy.transform.Rotate(UnityEngine.Vector3.up, 2.0f);
    }

    void OnRotateRight(object sender, RoutedEventArgs e)
    {
        this._spaceBoy.transform.Rotate(UnityEngine.Vector3.up, -2.0f);
    }

    #region Private members
    Point _lastPosition;
    Border _titleBar;
    TranslateTransform _panelPosition;
    #endregion
}
