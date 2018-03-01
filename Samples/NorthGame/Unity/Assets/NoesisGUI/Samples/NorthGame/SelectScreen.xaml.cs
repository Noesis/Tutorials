#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
#else
using System.Windows.Controls;
#endif


namespace NorthGame
{
    /// <summary>
    /// Interaction logic for SelectScreen.xaml
    /// </summary>
    public partial class SelectScreen : UserControl
    {
        public SelectScreen()
        {
            InitializeComponent();
        }

#if NOESIS
        private void InitializeComponent()
        {
            Noesis.GUI.LoadComponent(this, "Assets/NoesisGUI/Samples/NorthGame/SelectScreen.xaml");
        }
#endif
    }
}
