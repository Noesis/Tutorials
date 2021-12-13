#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
#else
using System;
using System.Windows.Controls;
#endif

namespace LayeredUI
{
    public class HUDViewModel
    {

    }

    /// <summary>
    /// Interaction logic for HUDView.xaml
    /// </summary>
    public partial class HUDView : UserControl
    {
        public HUDView()
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
