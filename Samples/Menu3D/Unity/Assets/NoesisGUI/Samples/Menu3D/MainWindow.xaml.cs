#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
#else
using System;
using System.Windows;
using System.Windows.Controls;
#endif

namespace Menu3D
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Grid
    {
        public MainWindow()
        {
            this.Initialized += OnInitialized;
            this.InitializeComponent();
        }

#if NOESIS
        private void InitializeComponent()
        {
            Noesis.GUI.LoadComponent(this, "Assets/NoesisGUI/Samples/Menu3D/MainWindow.xaml");
        }
#endif

        private void OnInitialized(object sender, EventArgs e)
        {
            var mainMenu = (MainMenu)FindName("Main");
            var startMenu = (StartMenu)FindName("Start");
            var settingsMenu = (SettingsMenu)FindName("Settings");

            var model = new ViewModel(mainMenu, startMenu, settingsMenu);

            mainMenu.DataContext = model;
            startMenu.DataContext = model;
            settingsMenu.DataContext = model;

            mainMenu.FadeIn();
        }
    }
}
