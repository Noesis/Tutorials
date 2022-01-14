using System;
using System.Windows;

namespace DataBinding
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        protected override void OnActivated(EventArgs e)
        {
            MainWindow.DataContext = new SolarSystem();
        }
    }
}
