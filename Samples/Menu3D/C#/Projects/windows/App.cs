using System;
using NoesisApp;

namespace Menu3D
{
    partial class App : Application
    {
        protected override Display CreateDisplay()
        {
            return new Win32Display();
        }

        protected override RenderContext CreateRenderContext()
        {
            return new RenderContextD3D11();
        }

        [STAThread]
        static void Main()
        {
            App app = new App();
            app.Uri = "/Menu3D;component/App.xaml";

            Noesis.Log.SetLogCallback((level, channel, message) =>
            {
                if (string.IsNullOrEmpty(channel) || channel == "Binding")
                {
                    string[] prefixes = new string[] { "T", "D", "I", "W", "E" };
                    string prefix = (int)level < prefixes.Length ? prefixes[(int)level] : " ";
                    System.Diagnostics.Debug.WriteLine("[NOESIS/" + prefix + "] " + message);
                }
            });
            app.Run();
        }
    }
}
