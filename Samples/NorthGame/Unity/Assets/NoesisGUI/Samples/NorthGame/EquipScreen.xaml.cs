#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
#else
using System.Windows.Controls;
#endif


namespace NorthGame
{
    /// <summary>
    /// Interaction logic for EquipScreen.xaml
    /// </summary>
    public partial class EquipScreen : UserControl
    {
        public EquipScreen()
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
