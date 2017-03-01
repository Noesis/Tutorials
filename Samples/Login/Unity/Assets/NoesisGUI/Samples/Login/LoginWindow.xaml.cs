#if UNITY_5_3_OR_NEWER
#define NOESIS
#endif

#if NOESIS
using Noesis;
#else
using System;
using System.Windows;
using System.Windows.Controls;
#endif

namespace Noesis.Samples
{
    /// <summary>
    /// Interaction logic for LoginWindow.xaml
    /// </summary>
    public partial class LoginWindow : UserControl
    {
        public LoginWindow()
        {
            this.Initialized += OnInitialized;
            this.InitializeComponent();
        }
#if NOESIS
        void InitializeComponent()
        {
            Noesis.GUI.LoadComponent(this, "Assets/NoesisGUI/Samples/Login/LoginWindow.xaml");
        }
#endif

        private void OnInitialized(object sender, EventArgs args)
        {
            this.DataContext = new LoginViewModel();
        }
    }
}
