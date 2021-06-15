using System;
using System.Windows;
using System.Windows.Controls;

namespace VideoEffect
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            this.InitializeComponent();
        }

#if NOESIS
        private void InitializeComponent()
        {
            Noesis.GUI.LoadComponent(this, "Assets/NoesisGUI/Samples/VideoEffect/MainWindow.xaml");
        }
#endif

    }
}
