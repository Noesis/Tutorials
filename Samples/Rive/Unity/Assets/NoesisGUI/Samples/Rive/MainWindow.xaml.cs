#if UNITY_5_3_OR_NEWER
#define NOESIS
using System;
using Noesis;
#else
using System;
using System.Windows;
using System.Windows.Controls;
#endif

namespace Rive
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : UserControl
    {
        public MainWindow()
        {
            InitializeComponent();
        }

#if NOESIS
        private void InitializeComponent()
        {
            NoesisUnity.LoadComponent(this);
        }
#endif
    }
}
