#if NOESIS
using Noesis;
using NoesisApp;
#else
using System.Windows;
#endif

namespace RadialMenu
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            DataContext = new ViewModel();
        }

#if NOESIS
        private void InitializeComponent()
        {
            GUI.LoadComponent(this, "/RadialMenu;component/MainWindow.xaml");
        }
#endif
    }
}
