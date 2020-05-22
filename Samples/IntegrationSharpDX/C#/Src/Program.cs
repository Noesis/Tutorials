using System;
using System.Windows.Forms;
using SharpDX;
using SharpDX.Direct3D;
using SharpDX.Direct3D11;
using SharpDX.DXGI;
using SharpDX.Windows;
using Device = SharpDX.Direct3D11.Device;

namespace IntegrationSharpDX
{
    // This is a minimal integration example. For simplification purposes only basic input events are
    // handled, no resource providers are used and the shutdown procedure is omitted.

    internal static class Program
    {
        [STAThread]
        private static void Main()
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
            Noesis.View view = Noesis.GUI.CreateView(xaml);
            view.SetFlags(Noesis.RenderFlags.PPAA | Noesis.RenderFlags.LCD);

            // Creation of the system window
            RenderForm form = new RenderForm("NoesisGUI - IntegrationSharpDX D3D11")
            {
                Width = 1000,
                Height = 600,
                Icon = new System.Drawing.Icon("Noesis.ico")
            };
            view.SetSize(form.ClientSize.Width, form.ClientSize.Height);

            // SwapChain description
            SwapChainDescription desc = new SwapChainDescription()
            {
                BufferCount = 1,
                ModeDescription = new ModeDescription(form.ClientSize.Width, form.ClientSize.Height,
                    new Rational(60, 1), Format.R8G8B8A8_UNorm),
                IsWindowed = true,
                OutputHandle = form.Handle,
                SampleDescription = new SampleDescription(1, 0),
                SwapEffect = SwapEffect.Discard,
                Usage = Usage.RenderTargetOutput
            };

            // Create Device and SwapChain
            Device device;
            SwapChain swapChain;
            Device.CreateWithSwapChain(DriverType.Hardware, DeviceCreationFlags.None, desc, out device, out swapChain);
            DeviceContext context = device.ImmediateContext;

            Factory factory = swapChain.GetParent<Factory>();
            factory.MakeWindowAssociation(form.Handle, WindowAssociationFlags.IgnoreAll);
            factory.Dispose();

            // Renderer initialization with a Direct3D11 device
            view.Renderer.Init(new Noesis.RenderDeviceD3D11(context.NativePointer));

            // New RenderTargetView from the backbuffer
            Texture2D backBuffer = Texture2D.FromSwapChain<Texture2D>(swapChain, 0);
            RenderTargetView renderView = new RenderTargetView(device, backBuffer);
            backBuffer.Dispose();

            // Register window events
            form.SizeChanged += (s, e) =>
            {
                context.OutputMerger.SetRenderTargets(null, (RenderTargetView)null);
                renderView.Dispose();

                swapChain.ResizeBuffers(0, 0, 0, Format.Unknown, SwapChainFlags.None);

                backBuffer = Texture2D.FromSwapChain<Texture2D>(swapChain, 0);
                renderView = new RenderTargetView(device, backBuffer);
                backBuffer.Dispose();

                view.SetSize(form.ClientSize.Width, form.ClientSize.Height);
            };
            form.MouseMove += (s, e) => { view.MouseMove(e.X, e.Y); };
            form.MouseDown += (s, e) =>
            {
                if (e.Button == MouseButtons.Left)
                {
                    view.MouseButtonDown(e.X, e.Y, Noesis.MouseButton.Left);
                }
            };
            form.MouseUp += (s, e) =>
            {
                if (e.Button == MouseButtons.Left)
                {
                    view.MouseButtonUp(e.X, e.Y, Noesis.MouseButton.Left);
                }
            };

            // Main loop
            DateTime start = DateTime.Now;
            RenderLoop.Run(form, () =>
            {
                // Update view (layout, animations, ...)
                view.Update((DateTime.Now - start).TotalSeconds);

                // Offscreen rendering phase populates textures needed by the on-screen rendering
                view.Renderer.UpdateRenderTree();
                view.Renderer.RenderOffscreen();

                // If you are going to render here with your own engine you need to restore the GPU state
                // because noesis changes it. In this case only framebuffer and viewport need to be restored
                context.Rasterizer.SetViewport(new Viewport(0, 0, form.ClientSize.Width, form.ClientSize.Height, 0.0f, 1.0f));
                context.OutputMerger.SetTargets(renderView);
                context.ClearRenderTargetView(renderView, Color.Black);

                // Rendering is done in the active framebuffer
                view.Renderer.Render();

                // Present and swap buffers
                swapChain.Present(0, PresentFlags.None);
            });

            // Release all resources
            renderView.Dispose();
            context.ClearState();
            context.Flush();
            device.Dispose();
            context.Dispose();
            swapChain.Dispose();
        }
    }
}
