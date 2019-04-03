using NoesisApp;

namespace DataBinding
{
    partial class App : Application
    {
        protected override Display CreateDisplay()
        {
            return new XDisplay();
        }

        protected override RenderContext CreateRenderContext()
        {
            return new RenderContextGLX();
        }

        static void Main(string[] args)
        {
            App app = new App();
            app.Uri = "App.xaml";
            app.Run();
        }
    }
}
