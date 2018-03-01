#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
#else
using System.Windows.Controls;
#endif


namespace NorthGame
{
    /// <summary>
    /// Interaction logic for RaidScreen.xaml
    /// </summary>
    public partial class RaidScreen : UserControl
    {
        public RaidScreen()
        {
            InitializeComponent();
        }

#if NOESIS
        private void InitializeComponent()
        {
            Noesis.GUI.LoadComponent(this, "Assets/NoesisGUI/Samples/NorthGame/RaidScreen.xaml");
        }
#endif
    }
}
