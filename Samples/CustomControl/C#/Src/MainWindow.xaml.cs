#if NOESIS
using Noesis;
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
            GUI.LoadComponent(this, "MainWindow.xaml");
        }
#endif
    }
}
