namespace IntegrationSharpDX
{
    #region

    using System;
    using System.Windows.Forms;
    using Noesis;
    using NoesisApp;
    using MouseEventArgs = System.Windows.Forms.MouseEventArgs;
    using View = Noesis.View;

    #endregion

    public static class Program
    {
        private static App app;

        private static bool isRunning;

        private static View view;
        private static Renderer renderer;
        private static readonly DeviceStateD3D11 deviceState = new DeviceStateD3D11();


        private static void Main()
        {
            try
            {
                Run();
            }
            catch (Exception e)
            {
                LogError(e.Message);

                OnClose();
            }
        }

        private static void Run()
        {
            // Prepare and run D3D11 wrapper
            var configuration = new DemoConfiguration("NoesisGUI Integration Sample", 1280, 720);
            app = new App();
            app.Run(configuration, contentLoadCallback: OnContentLoaded);
        }

        private static void OnContentLoaded()
        {
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
                view = Noesis.GUI.CreateView(content);
                IntPtr deviceContext = app.Device.ImmediateContext.NativePointer;
                RenderDevice device = new RenderDeviceD3D11(deviceContext);
                renderer = view.Renderer;
                renderer.Init(device);
            }

            // Attach to Application events
            app.Close += OnClose;
            app.Tick += OnTick;
            app.PreRender += OnPreRender;
            app.PostRender += OnPostRender;
            app.Resize += OnResize;
            app.MouseMove += OnMouseMove;
            app.MouseDown += OnMouseDown;
            app.MouseUp += OnMouseUp;

            OnResize(app.Size.Width, app.Size.Height);

            isRunning = true;
        }

        private static void OnTick(double timeInSeconds)
        {
            view.Update(timeInSeconds);
        }

        private static void OnPreRender()
        {
            deviceState.Save(app.Device.ImmediateContext);

            try
            {
                renderer.UpdateRenderTree();

                if (renderer.NeedsOffscreen())
                {
                    renderer.RenderOffscreen();
                }
            }
            finally
            {
                deviceState.Restore(app.Device.ImmediateContext);
            }
        }

        private static void OnPostRender()
        {
            deviceState.Save(app.Device.ImmediateContext);
            try
            {
                renderer.Render();
            }
            finally
            {
                deviceState.Restore(app.Device.ImmediateContext);
            }
        }

        private static void OnClose()
        {
            // Detach from Application events
            if (!isRunning)
            {
                return;
            }

            isRunning = false;
            app.Close -= OnClose;
            app.Tick -= OnTick;
            app.PreRender -= OnPreRender;
            app.PostRender -= OnPostRender;
            app.Resize -= OnResize;
            app.MouseMove -= OnMouseMove;
            app.MouseDown -= OnMouseDown;
            app.MouseUp -= OnMouseUp;

            renderer?.Shutdown();
            view = null;

            try
            {
                GUI.Shutdown();
            }
            catch (Exception e)
            {
                LogError(e.Message);
            }
        }

        private static void OnResize(int width, int height)
        {
            view.SetSize(width, height);
        }

        private static Noesis.MouseButton NoesisButton(MouseButtons b)
        {
            switch (b)
            {
                default:
                case MouseButtons.Left: return Noesis.MouseButton.Left;
                case MouseButtons.Middle: return Noesis.MouseButton.Middle;
                case MouseButtons.Right: return Noesis.MouseButton.Right;
                case MouseButtons.XButton1: return Noesis.MouseButton.XButton1;
                case MouseButtons.XButton2: return Noesis.MouseButton.XButton2;
            }
        }

        private static void OnMouseDown(MouseEventArgs args)
        {
            view.MouseButtonDown(args.X, args.Y, NoesisButton(args.Button));
        }

        private static void OnMouseMove(MouseEventArgs args)
        {
            view.MouseMove(args.X, args.Y);
        }

        private static void OnMouseUp(MouseEventArgs args)
        {
            view.MouseButtonUp(args.X, args.Y, NoesisButton(args.Button));
        }

        private static void LogError(string msg)
        {
            Console.WriteLine("ERROR!");
            Console.WriteLine("--------------------------------------------------------");
            Console.WriteLine(msg);
            Console.WriteLine("--------------------------------------------------------");
            Console.WriteLine("PRESS ANY KEY TO CONTINUE");
            Console.ReadKey();
        }
    }
}