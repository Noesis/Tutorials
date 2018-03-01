#if NOESIS
using Noesis;
using NoesisApp;
#else
using System.Windows;
#endif

namespace HelloWorld
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
#if NOESIS
        protected override XamlProvider GetXamlProvider()
        {
            EmbeddedXaml[] xamls =
            {
                new EmbeddedXaml { filename = "App.xaml", resource = "App" },
                new EmbeddedXaml { filename= "MainWindow.xaml", resource = "MainWindow" }
            };
            return new EmbeddedXamlProvider(xamls, Properties.Resources.ResourceManager);
        }
#endif
    }
}
