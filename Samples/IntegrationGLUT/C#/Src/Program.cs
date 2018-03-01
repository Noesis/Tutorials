using System;
using Noesis;
using NoesisApp;

namespace IntegrationGLUT
{
    class Program
    {
        static View _view = null;
        static Renderer _renderer = null;
        static bool _eventsAttached = false;

        static void Main(string[] args)
        {
            try
            {
                // Initialization
                GLUTWrapper.Init(1280, 720, "NoesisGUI Integration Sample");

                Log.LogCallback += (level, channel, message) =>
                {
                    if (channel == "")
                    {
                        // [TRACE] [DEBUG] [INFO] [WARNING] [ERROR]
                        string[] prefixes = new string[] { "T", "D", "I", "W", "E" };
                        string prefix = (int)level < prefixes.Length ? prefixes[(int)level] : " ";
                        Console.WriteLine("[NOESIS/" + prefix + "] " + message);
                    }
                };

                GUI.Init();

                // Setup embedded resource providers
                EmbeddedXaml[] xamls = new EmbeddedXaml[]
                {
                    new EmbeddedXaml { filename = "Reflections.xaml", resource = "Reflections" }
                };
                GUI.SetXamlProvider(new EmbeddedXamlProvider(xamls, Properties.Resources.ResourceManager));

                // Data loading
                {
                    var content = (Noesis.Grid)Noesis.GUI.LoadXaml("Reflections.xaml");
                    _view = Noesis.GUI.CreateView(content);
                    RenderDevice device = new RenderDeviceGL();
                    _renderer = _view.Renderer;
                    _renderer.Init(device);
                }

                // Attach to Application events
                GLUTWrapper.Close += OnClose;
                GLUTWrapper.Tick += OnTick;
                GLUTWrapper.PreRender += OnPreRender;
                GLUTWrapper.PostRender += OnPostRender;
                GLUTWrapper.Resize += OnResize;
                GLUTWrapper.MouseMove += OnMouseMove;
                GLUTWrapper.MouseDown += OnMouseDown;
                GLUTWrapper.MouseUp += OnMouseUp;
                _eventsAttached = true;

                // Main Loop
                GLUTWrapper.Run();
            }
            catch (Exception e)
            {
                LogError(e.Message);

                OnClose();
            }
        }

        static void LogError(string msg)
        {
            Console.WriteLine("ERROR!");
            Console.WriteLine("--------------------------------------------------------");
            Console.WriteLine(msg);
            Console.WriteLine("--------------------------------------------------------");
        }

        static void OnClose()
        {
            // Detach from Application events
            if (_eventsAttached)
            {
                _eventsAttached = false;
                GLUTWrapper.Close -= OnClose;
                GLUTWrapper.Tick -= OnTick;
                GLUTWrapper.PreRender -= OnPreRender;
                GLUTWrapper.PostRender -= OnPostRender;
                GLUTWrapper.Resize -= OnResize;
                GLUTWrapper.MouseMove -= OnMouseMove;
                GLUTWrapper.MouseDown -= OnMouseDown;
                GLUTWrapper.MouseUp -= OnMouseUp;
            }

            if (_renderer != null)
            {
                _renderer.Shutdown();
            }

            _view = null;

            try
            {
                Noesis.GUI.Shutdown();
            }
            catch (Exception e)
            {
                LogError(e.Message);
            }

            GLUTWrapper.Shutdown();
        }

        static void OnTick(double timeInSeconds)
        {
            _view.Update(timeInSeconds);
        }

        static void OnPreRender()
        {
            _renderer.UpdateRenderTree();

            if (_renderer.NeedsOffscreen())
            {
                _renderer.RenderOffscreen();
            }
        }

        static void OnPostRender()
        {
            _renderer.Render();
        }

        static void OnResize(int width, int height)
        {
            _view.SetSize(width, height);
        }

        static void OnMouseMove(int x, int y)
        {
            _view.MouseMove(x, y);
        }

        static void OnMouseDown(int x, int y, GLUTWrapper.MouseButton button)
        {
            _view.MouseButtonDown(x, y, (Noesis.MouseButton)button);
        }

        static void OnMouseUp(int x, int y, GLUTWrapper.MouseButton button)
        {
            _view.MouseButtonUp(x, y, (Noesis.MouseButton)button);
        }
    }
}
