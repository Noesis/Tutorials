#if NOESIS
using Noesis;
using NoesisApp;
#else
using System.Windows;
#endif

namespace Menu3D
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
                new EmbeddedXaml { filename = "MainMenu.xaml", resource = "MainMenu" },
                new EmbeddedXaml { filename = "StartMenu.xaml", resource = "StartMenu" },
                new EmbeddedXaml { filename = "SettingsMenu.xaml", resource = "SettingsMenu" },
                new EmbeddedXaml { filename = "OptionSelector.xaml", resource = "OptionSelector" },
                new EmbeddedXaml { filename = "MenuResources.xaml", resource = "MenuResources" }
            };
            return new EmbeddedXamlProvider(xamls, Properties.Resources.ResourceManager);
        }

        protected override TextureProvider GetTextureProvider()
        {
            EmbeddedTexture[] textures =
            {
                new EmbeddedTexture { filename = "Images/BackClouds.png", resource = "BackClouds" },
                new EmbeddedTexture { filename = "Images/FrontClouds.png", resource = "FrontClouds" },
                new EmbeddedTexture { filename = "Images/FrontTrees.png", resource = "FrontClouds" },
                new EmbeddedTexture { filename = "Images/LakeAndMountains.png", resource = "LakeAndMountains" },
                new EmbeddedTexture { filename = "Images/SkyAndSun.jpg", resource = "SkyAndSun" }

            };
            return new EmbeddedTextureProvider(textures, Properties.Resources.ResourceManager);
        }

        protected override FontProvider GetFontProvider()
        {
            EmbeddedFont[] fonts =
            {
                new EmbeddedFont { folder = "Fonts", resource = "weblysleekuisb" },
                new EmbeddedFont { folder = "Fonts", resource = "weblysleekuisl" }
            };
            return new EmbeddedFontProvider(fonts, Properties.Resources.ResourceManager);
        }
#endif
    }
}
