using System;
using System.Windows;

namespace WorldSpaceUI
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        protected override void OnActivated(EventArgs e)
        {
            MainWindow.DataContext = new ViewModel() { Name = "DRONE INFO", Energy = 75.0f };
        }
    }
}
