#if NOESIS
using Noesis;
using NoesisApp;
#else
using System;
using System.Windows;
#endif

namespace RssReader
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
#if !NOESIS
        public App()
        {
            // NoesisTheme added to Application.Resources also so it runs exactly the same as inside Noesis
            ResourceDictionary theme = (ResourceDictionary)LoadComponent(new Uri("NoesisTheme.xaml", UriKind.Relative));
            Resources.MergedDictionaries.Insert(0, theme);
        }
#endif
    }
}
