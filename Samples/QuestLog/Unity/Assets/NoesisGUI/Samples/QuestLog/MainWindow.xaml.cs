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
            this.InitializeComponent();
        }

#if NOESIS
        void InitializeComponent()
        {
            NoesisUnity.LoadComponent(this);
        }
#endif
    }
}
