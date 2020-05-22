using System;

namespace IntegrationGLUT
{
    // This is a minimal integration example. For simplification purposes only basic input events are
    // handled, no resource providers are used and the shutdown procedure is omitted.

    class Program
    {
        static void Main(string[] args)
        {
            int argc = args.Length;
            GLUT.Init(ref argc, args);
            GLUT.InitDisplayMode(GLUT.RGB | GLUT.DOUBLE | GLUT.STENCIL);
            GLUT.InitWindowSize(1000, 600);
            GLUT.CreateWindow("NoesisGUI - GLUT integration");

            NoesisInit();

            GLUT.SetDisplayFunc(OnDisplay);
            GLUT.SetReshapeFunc(OnReshape);
            GLUT.SetPassiveMotionFunc(OnMouseMove);
            GLUT.SetMouseFunc(OnMouseButton);

            GLUT.MainLoop();
        }

        static void NoesisInit()
        {
            Noesis.Log.SetLogCallback((level, channel, message) =>
            {
                if (channel == "")
                {
                    // [TRACE] [DEBUG] [INFO] [WARNING] [ERROR]
                    string[] prefixes = new string[] { "T", "D", "I", "W", "E" };
                    string prefix = (int)level < prefixes.Length ? prefixes[(int)level] : " ";
                    Console.WriteLine("[NOESIS/" + prefix + "] " + message);
                }
            });

            // Noesis initialization. This must be the first step before using any NoesisGUI functionality
            Noesis.GUI.Init("LICENSE_NAME", "LICENSE_KEY");

            // Setup theme
            NoesisApp.Application.SetThemeProviders();
            Noesis.GUI.LoadApplicationResources("Theme/NoesisTheme.DarkBlue.xaml");

            // For simplicity purposes we are not using resource providers in this sample. ParseXaml() is
            // enough if there is no extra XAML dependencies
            Noesis.Grid xaml = (Noesis.Grid)Noesis.GUI.ParseXaml(@"
                <Grid xmlns=""http://schemas.microsoft.com/winfx/2006/xaml/presentation"">
                    <Grid.Background>
                        <LinearGradientBrush StartPoint=""0,0"" EndPoint=""0,1"">
                            <GradientStop Offset=""0"" Color=""#FF123F61""/>
                            <GradientStop Offset=""0.6"" Color=""#FF0E4B79""/>
                            <GradientStop Offset=""0.7"" Color=""#FF106097""/>
                        </LinearGradientBrush>
                    </Grid.Background>
                    <Viewbox>
                        <StackPanel Margin=""50"">
                            <Button Content=""Hello World!"" Margin=""0,30,0,0""/>
                            <Rectangle Height=""5"" Margin=""-10,20,-10,0"">
                                <Rectangle.Fill>
                                    <RadialGradientBrush>
                                        <GradientStop Offset=""0"" Color=""#40000000""/>
                                        <GradientStop Offset=""1"" Color=""#00000000""/>
                                    </RadialGradientBrush>
                                </Rectangle.Fill>
                            </Rectangle>
                        </StackPanel>
                    </Viewbox>
                </Grid>");

            // View creation to render and interact with the user interface
            // We transfer the ownership to a global pointer instead of a Ptr<> because there is no way
            // in GLUT to do shutdown and we don't want the Ptr<> to be released at global time
            _view = Noesis.GUI.CreateView(xaml);
            _view.SetFlags(Noesis.RenderFlags.PPAA | Noesis.RenderFlags.LCD);

            // Renderer initialization with an OpenGL device
            _view.Renderer.Init(new Noesis.RenderDeviceGL());
        }

        static void OnDisplay()
        {
            // Update view (layout, animations, ...)
            _view.Update(GLUT.Get(GLUT.ELAPSED_TIME) / 1000.0);

            // Offscreen rendering phase populates textures needed by the on-screen rendering
            _view.Renderer.UpdateRenderTree();
            _view.Renderer.RenderOffscreen();

            // If you are going to render here with your own engine you need to restore the GPU state
            // because noesis changes it. In this case only framebuffer and viewport need to be restored
            GL.BindFramebuffer(GL.FRAMEBUFFER, 0);
            GL.Viewport(0, 0, (uint)GLUT.Get(GLUT.WINDOW_WIDTH), (uint)GLUT.Get(GLUT.WINDOW_HEIGHT));

            GL.ClearColor(0.0f, 0.0f, 0.25f, 0.0f);
            GL.ClearStencil(0);
            GL.Clear(GL.COLOR_BUFFER_BIT | GL.STENCIL_BUFFER_BIT);

            // Rendering is done in the active framebuffer
            _view.Renderer.Render();

            GLUT.SwapBuffers();
            GLUT.PostRedisplay();
        }

        static void OnReshape(int width, int height)
        {
            _view.SetSize(width, height);
        }

        static void OnMouseMove(int x, int y)
        {
            _view.MouseMove(x, y);
        }

        static void OnMouseButton(int button, int state, int x, int y)
        {
            if (button == GLUT.LEFT_BUTTON)
            {
                if (state == GLUT.DOWN)
                {
                    _view.MouseButtonDown(x, y, Noesis.MouseButton.Left);
                }
                else
                {
                    _view.MouseButtonUp(x, y, Noesis.MouseButton.Left);
                }
            }
        }

        static Noesis.View _view = null;
    }
}
