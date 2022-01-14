#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
#else
using System;
using System.Windows;
using System.Windows.Controls;
#endif

namespace VideoEffect
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Page
    {
        public MainWindow()
        {
            this.InitializeComponent();
        }

#if NOESIS
        private void InitializeComponent()
        {
            NoesisUnity.LoadComponent(this);
        }
#endif
    }
}
