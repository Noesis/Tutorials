#if NOESIS
using Noesis;
using NoesisApp;
#else
using System.Windows;
#endif

namespace Localization
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
                new EmbeddedXaml { filename = "ControlResources.xaml", resource = "ControlResources" },
                new EmbeddedXaml { filename = "LogoResources.xaml", resource = "LogoResources" },
                new EmbeddedXaml { filename = "Language-en.xaml", resource = "Language_en" },
                new EmbeddedXaml { filename = "Language-fr.xaml", resource = "Language_fr" }
            };
            return new EmbeddedXamlProvider(xamls, Properties.Resources.ResourceManager);
        }

        protected override TextureProvider GetTextureProvider()
        {
            EmbeddedTexture[] textures =
            {
                new EmbeddedTexture { filename = "Flag-en.png", resource = "Flag_en" },
                new EmbeddedTexture { filename = "Flag-fr.png", resource = "Flag_fr" }
            };
            return new EmbeddedTextureProvider(textures, Properties.Resources.ResourceManager);
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
