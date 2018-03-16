using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace SamplesWPF
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        public App()
        {
            // NoesisTheme added to Application.Resources also so it runs exactly the same as inside Noesis
            ResourceDictionary theme = (ResourceDictionary)LoadComponent(new Uri("NoesisTheme.xaml", UriKind.Relative));
            Resources.MergedDictionaries.Insert(0, theme);
        }
    }
}
