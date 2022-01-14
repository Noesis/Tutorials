#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
#else
using System.Windows.Controls;
#endif

namespace NorthGame
{
    /// <summary>
    /// Interaction logic for Menu.xaml
    /// </summary>
    public partial class Menu : UserControl
    {
        public Menu()
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
