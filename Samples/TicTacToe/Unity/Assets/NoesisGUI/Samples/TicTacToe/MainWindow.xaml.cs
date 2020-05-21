#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
#else
using System;
using System.Windows;
using System.Windows.Controls;
#endif


namespace TicTacToe
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : UserControl
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
            Noesis.GUI.LoadComponent(this, "Assets/NoesisGUI/Samples/TicTacToe/MainWindow.xaml");
        }
#endif

        private void OnInitialized(object sender, EventArgs e)
        {
            DataContext = new ViewModel();
        }
    }
}
