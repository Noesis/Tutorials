#if UNITY_5_3_OR_NEWER
#define NOESIS
using System;
using Noesis;
#else
using System;
using System.Globalization;
using System.Windows.Controls;
#endif

namespace WorldSpaceUI
{
    public partial class LayoutRoot : UserControl
    {
        public LayoutRoot()
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
