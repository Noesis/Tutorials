using System.Windows;

namespace DataBinding
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        public App()
        {
            Activated += (s, e) =>
            {
                MainWindow.DataContext = new SolarSystem();
            };
        }
    }
}
