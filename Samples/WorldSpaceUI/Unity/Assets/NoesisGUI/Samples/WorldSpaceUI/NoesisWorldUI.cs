using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using UnityEngine;
using Noesis;

public class NoesisWorldUI : MonoBehaviour
{
    [SerializeField]
    private NoesisView _view;
    public NoesisView View { get => _view; set { if (_view != value) { _view = value; LoadContent(); } } }

    [SerializeField]
    private string _container = "Root";
    public string Container { get => _container; set { if (_container != value) { _container = value; LoadContent(); } } }

    [SerializeField]
    private NoesisXaml _xaml;
    public NoesisXaml Xaml { get => _xaml; set { if (_xaml != value) { _xaml = value; LoadContent(); } } }

    [SerializeField]
    private float _scale = 0.005f;
    public float Scale { get => _scale; set { _scale = value; } }

    [SerializeField]
    private Vector3 _offset = new Vector3();
    public Vector3 Offset { get => _offset; set { _offset = value; } }

    [SerializeField]
    private bool _center = true;
    public bool Center { get => _center; set { _center = value; } }

    public FrameworkElement Content => _content;

    void OnEnable()
    {
        LoadContent();
    }

    void OnDisable()
    {
        RemoveContent();
    }

    void Update()
    {
        if (_transform != null)
        {
            float width = 0.0f;
            float height = 0.0f;

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

    void LoadContent()
    {
        RemoveContent();

        if (View != null && !string.IsNullOrEmpty(Container))
        {
            _panel = View.Content?.FindName(Container) as Panel;
        }

        if (Xaml != null)
        {
            _content = Xaml.Load() as FrameworkElement;
            _transform = new MatrixTransform3D();
            _content.Transform3D = _transform;
        }

        AddContent();
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

        _panel = null;
        _content = null;
        _transform = null;
    }

    private Panel _panel;
    private FrameworkElement _content;
    private MatrixTransform3D _transform;
}
