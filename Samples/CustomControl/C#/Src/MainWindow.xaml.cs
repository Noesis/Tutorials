#if NOESIS
using Noesis;
using NoesisApp;
#else
using System.Windows;
#endif

namespace CustomControl
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

#if NOESIS
        private void InitializeComponent()
        {
            GUI.LoadComponent(this, "/CustomControl;component/MainWindow.xaml");
        }
#endif
    }
}
