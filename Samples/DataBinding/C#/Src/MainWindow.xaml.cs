#if NOESIS
using Noesis;
using NoesisApp;
#else
using System.Windows;
#endif

namespace DataBinding
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            DataContext = new SolarSystem();
        }

#if NOESIS
        private void InitializeComponent()
        {
            GUI.LoadComponent(this, "/DataBinding;component/MainWindow.xaml");
        }
#endif
    }
}
