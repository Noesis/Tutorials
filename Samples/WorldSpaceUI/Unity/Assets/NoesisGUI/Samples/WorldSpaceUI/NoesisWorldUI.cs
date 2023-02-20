using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using UnityEngine;
using Noesis;

public class NoesisWorldUI : MonoBehaviour
{
    [Header("View")]
    [Tooltip("The View used to render the specified XAML")]
    public NoesisView View;
    [Tooltip("The name of the Panel container where the specified XAML will be inserted")]
    public string Container = "Root";

    [Header("Xaml")]
    public NoesisXaml Xaml;

    public float Scale = 0.005f;
    public Vector3 Offset = new Vector3();
    [Tooltip("If enabled centers UI in the GameObject position; otherwise anchors top-left corner of the UI to GameObject position")]
    public bool Center = true;

    public FrameworkElement Content { get => _content; }

    void OnEnable()
    {
        UpdateContent();
    }

    void OnDisable()
    {
        RemoveContent();

        _view = null;
        _panel = null;
        _xaml = null;
        _content = null;
        _transform = null;
    }

    void Update()
    {
        UpdateContent();

        if (_transform != null)
        {
            float width = 1.0f;
            float height = 1.0f;

            if (Center)
            {
                _content.Measure(new Size(float.PositiveInfinity, float.PositiveInfinity));
                width = _content.DesiredSize.Width;
                height = _content.DesiredSize.Height;
            }

            Matrix4x4 mtx = transform.localToWorldMatrix * Matrix4x4.Translate(Offset) *
                Matrix4x4.Scale(new Vector3(Scale, -Scale, Scale)) *
                Matrix4x4.Translate(new Vector3(-0.5f * width, -0.5f * height, 0.00f));

            _transform.Matrix = new Matrix3D
            (
                mtx[0, 0], mtx[1, 0], mtx[2, 0],
                mtx[0, 1], mtx[1, 1], mtx[2, 1],
                mtx[0, 2], mtx[1, 2], mtx[2, 2],
                mtx[0, 3], mtx[1, 3], mtx[2, 3]
            );
        }
    }

    void UpdateContent()
    {
        if (_view != View)
        {
            RemoveContent();

            _view = View;
            _panel = null;
            _content = null;
            _transform = null;
        }

        if (_xaml != Xaml)
        {
            RemoveContent();

            _xaml = Xaml;
            _content = null;
            _transform = null;
        }

        if (_view != null && _panel == null && !string.IsNullOrEmpty(Container))
        {
            _panel = _view.Content?.FindName(Container) as Panel;

            AddContent();
        }

        if (_xaml != null && _content == null)
        {
            _content = _xaml.Load() as FrameworkElement;
            _transform = new MatrixTransform3D();
            _content.Transform3D = _transform;

            AddContent();
        }
    }

    void AddContent()
    {
        if (_panel != null && _content != null)
        {
            _panel.Children.Add(_content);
        }
    }

    void RemoveContent()
    {
        if (_panel != null && _content != null)
        {
            _panel.Children.Remove(_content);
        }
    }

    private NoesisView _view;
    private Panel _panel;

    private NoesisXaml _xaml;
    private FrameworkElement _content;
    private MatrixTransform3D _transform;
}
