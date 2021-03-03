using System.Windows;
using System.Windows.Controls;

namespace RadialMenu
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : UserControl
    {
        public MainWindow()
        {
            InitializeComponent();

            DataContext = new ViewModel();
        }
    }
}
