#if NOESIS
using Noesis;
#else
using System;
using System.Windows.Controls;
#endif

namespace Menu3D
{
    /// <summary>
    /// Interaction logic for MainMenu.xaml
    /// </summary>
    public partial class MainMenu : UserControl
    {
        public MainMenu()
        {
            this.InitializeComponent();
        }

#if NOESIS
        private void InitializeComponent()
        {
            Noesis.GUI.LoadComponent(this, "MainMenu.xaml");
        }
#endif
    }
}
