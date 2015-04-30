using UnityEngine;
using Noesis;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;

[AddComponentMenu("NoesisGUI/NoesisGUI Panel")]
public class NoesisGUIPanel : MonoBehaviour
{
    public string _xamlFile = string.Empty;
    public Object _xaml = null;
    public string _styleFile = string.Empty;
    public Object _style = null;

    public Vector2 _offscreenSize = new Vector2(1, 1);

    public AntialiasingMode _antiAliasingMode = AntialiasingMode.MSAA;
    public TessellationMode _tessellationMode = TessellationMode.Threshold;
    public TessellationQuality _tessellationQuality = TessellationQuality.Medium;
    public RendererFlags _renderFlags;

    public bool _enableKeyboard = true;
    public bool _enableMouse = true;
    public bool _enableTouch = true;

    public bool _enablePostProcess = false;

    public bool _flipVertically = false;

    public bool _useRealTimeClock = false;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    private Noesis.UIRenderer _uiRenderer;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    public FrameworkElement GetContent()
    {
        if (_uiRenderer != null)
        {
            return _uiRenderer.GetContent();
        }
        else
        {
            return null;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    public void KeyDown(Noesis.Key key)
    {
        if (_uiRenderer != null)
        {
            _uiRenderer.KeyDown(key);
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    public void KeyUp(Noesis.Key key)
    {
        if (_uiRenderer != null)
        {
            _uiRenderer.KeyUp(key);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////
    public void MouseDown(float x, float y, Noesis.MouseButton button)
    {
        if (_uiRenderer != null)
        {
            _uiRenderer.MouseDown(x, y, button);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////
    public void MouseUp(float x, float y, Noesis.MouseButton button)
    {
        if (_uiRenderer != null)
        {
            _uiRenderer.MouseUp(x, y, button);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////
    public void MouseDoubleClick(float x, float y, Noesis.MouseButton button)
    {
        if (_uiRenderer != null)
        {
            _uiRenderer.MouseDoubleClick(x, y, button);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////
    public void MouseWheel(float x, float y, int wheelRotation)
    {
        if (_uiRenderer != null)
        {
            _uiRenderer.MouseWheel(x, y, wheelRotation);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////
    public void MouseMove(float x, float y)
    {
        if (_uiRenderer != null)
        {
            _uiRenderer.MouseMove(x, y);
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    public bool IsRenderToTexture()
    {
        Renderer renderer = gameObject.GetComponent<Renderer>();
        if (renderer != null && renderer.sharedMaterial != null)
        {
            return renderer.sharedMaterial.mainTexture is UnityEngine.RenderTexture;
        }
        else
        {
            return false;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    public event System.EventHandler Rendering
    {
        add { if (_uiRenderer != null) { _uiRenderer.Rendering += value; } }
        remove { if (_uiRenderer != null) { _uiRenderer.Rendering -= value; } }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    void Reset()
    {
        // Called once when component is attached to GameObject for the first time
        _offscreenSize = new Vector2(1, 1);
        _antiAliasingMode = AntialiasingMode.MSAA;
        _tessellationMode = TessellationMode.Threshold;
        _tessellationQuality = TessellationQuality.Medium;
        _renderFlags = RendererFlags.None;
        _enableKeyboard = true;
        _enableMouse = true;
        _enableTouch = true;
        _enablePostProcess = false;
        _flipVertically = false;
        _useRealTimeClock = false;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    public void LoadXaml(string xaml)
    {
        DestroyRenderer();
        _xamlFile = xaml;
        LoadXaml();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    private void LoadXaml()
    {
        // Create NoesisGUI System
        NoesisGUISystem.Create();

        // Create UI Renderer
        if (NoesisGUISystem.IsInitialized && _xamlFile.Length > 0 && _uiRenderer == null)
        {
            FrameworkElement root = NoesisGUISystem.LoadXaml(_xamlFile) as FrameworkElement;
            if (root != null)
            {
                if (_styleFile != "")
                {
                    ResourceDictionary resources = NoesisGUISystem.LoadXaml(_styleFile) as ResourceDictionary;
                    if (resources != null)
                    {
                        root.Resources.MergedDictionaries.Add(resources);
                    }
                    else
                    {
                        throw new System.Exception("Unable to load style xaml: " + _styleFile);
                    }
                }

                _uiRenderer = new Noesis.UIRenderer(root, _offscreenSize, gameObject);
                NoesisGUISystem.AddPanel(this);
            }
            else
            {
                throw new System.Exception("Unable to load xaml: " + _xamlFile);
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    void OnEnable()
    {
        LoadXaml();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    void LateUpdate()
    {
        if (_uiRenderer != null)
        {
            _uiRenderer.Update(_useRealTimeClock ? Time.realtimeSinceStartup : Time.time,
                _antiAliasingMode, _tessellationMode, _tessellationQuality, _renderFlags,
                _enableMouse, _enableTouch, _enablePostProcess, _flipVertically);
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    void OnBecameInvisible()
    {
        if (_uiRenderer != null && _uiRenderer.IsRenderToTexture())
        {
            _enableRender = false;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    void OnBecameVisible()
    {
        if (_uiRenderer != null && _uiRenderer.IsRenderToTexture())
        {
            _enableRender = true;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    void OnPreRender()
    {
        if (_uiRenderer != null && _enableRender)
        {
            _uiRenderer.PreRender();
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    void OnPostRender()
    {
        if (_uiRenderer != null && _enableRender)
        {
            if (_enablePostProcess || _uiRenderer.IsRenderToTexture())
            {
                _uiRenderer.PostRender();
            }
            else
            {
                StartCoroutine(RenderAtEndOfFrame());
            }
        }
    }

    private bool _enableRender = true;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    IEnumerator RenderAtEndOfFrame()
    {
        yield return waitEndOfFrame;
        _uiRenderer.PostRender();
    }

    private YieldInstruction waitEndOfFrame = new WaitForEndOfFrame();

    ////////////////////////////////////////////////////////////////////////////////////////////////
    void OnGUI()
    {
        if (_uiRenderer != null)
        {
            _uiRenderer.ProcessEvent(UnityEngine.Event.current, _enableKeyboard, _enableMouse);
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    void OnApplicationFocus(bool focused)
    {
        if (_uiRenderer != null)
        {
            if (!NoesisGUISystem.SoftwareKeyboardManager.IsOpen)
            {
                if (focused)
                {
                    _uiRenderer.Activate();
                }
                else
                {
                    _uiRenderer.Deactivate();
                }
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    void OnDestroy()
    {
        DestroyRenderer();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    internal void DestroyRenderer()
    {
        // Destroy native UI renderer
        if (_uiRenderer != null)
        {
            NoesisGUISystem.RemovePanel(this);
            _uiRenderer.Destroy();
            _uiRenderer = null;
        }
    }
}
