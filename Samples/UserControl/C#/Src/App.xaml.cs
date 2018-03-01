#if NOESIS
using Noesis;
using NoesisApp;
#else
using System.Windows;
#endif

namespace UserControls
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
                new EmbeddedXaml { filename = "MainWindow.xaml", resource = "MainWindow" },
                new EmbeddedXaml { filename = "NumericUpDown.xaml", resource = "NumericUpDown" }
            };
            return new EmbeddedXamlProvider(xamls, Properties.Resources.ResourceManager);
        }

        protected override FontProvider GetFontProvider()
        {
            EmbeddedFont[] fonts =
            {
                new EmbeddedFont { folder = "", resource = "Aero_Matics_Regular" }
            };
            return new EmbeddedFontProvider(fonts, Properties.Resources.ResourceManager);
        }
#endif
    }
}
