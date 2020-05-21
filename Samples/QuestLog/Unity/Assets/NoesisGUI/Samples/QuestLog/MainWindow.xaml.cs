#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
#else
using System;
using System.Windows;
using System.Windows.Controls;
#endif

namespace QuestLog
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : UserControl
    {
        public MainWindow()
        {
            System.WeakReference wr = new System.WeakReference(this);
            this.Initialized += (s, e) => { ((MainWindow)wr.Target).OnInitialized(s, e); };
            this.InitializeComponent();
        }

#if NOESIS
        void InitializeComponent()
        {
            Noesis.GUI.LoadComponent(this, "Assets/NoesisGUI/Samples/QuestLog/MainWindow.xaml");
        }
#endif

        private void OnInitialized(object sender, EventArgs args)
        {
            this.DataContext = new ViewModel();
        }
    }
}
