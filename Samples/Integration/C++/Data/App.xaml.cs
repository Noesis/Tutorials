using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace Integration
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        public App()
        {
            Resources = new ResourceDictionary
            {
                Source = new Uri("NoesisTheme.xaml", UriKind.Relative)
            };
        }
    }
}
