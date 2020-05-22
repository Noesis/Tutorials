#if NOESIS
using Noesis;
using NoesisApp;
#else
using System;
using System.Windows;
#endif

namespace Commands
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            System.WeakReference wr = new System.WeakReference(this);
            Initialized += (s, e) => { ((MainWindow)wr.Target).OnInitialized(s, e); };
            InitializeComponent();
        }

#if NOESIS
        private void InitializeComponent()
        {
            Noesis.GUI.LoadComponent(this, "MainWindow.xaml");
        }
#endif

        private void OnInitialized(object sender, EventArgs e)
        {
            DataContext = new ViewModel();
        }
    }
}
