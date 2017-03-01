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
            Noesis.GUI.LoadComponent(this, "Assets/MainWindow.xaml");
        }
#endif

        private void OnInitialized(object sender, EventArgs e)
        {
            var mainMenu = (MainMenu)FindName("Main");
            var startMenu = (StartMenu)FindName("Start");
            var settingsMenu = (SettingsMenu)FindName("Settings");

            var model = new MenuModel(mainMenu, startMenu, settingsMenu);
            
            mainMenu.DataContext = model;
            startMenu.DataContext = model;
            settingsMenu.DataContext = model;
            
            mainMenu.FadeIn();
        }

        public static DependencyProperty HoverProperty = DependencyProperty.RegisterAttached(
            "Hover", typeof(bool), typeof(MainWindow), new PropertyMetadata(false, OnHoverChanged));
        
        public static bool GetHover(DependencyObject d)
        {
            return (bool)d.GetValue(HoverProperty);
        }
        
        public static void SetHover(DependencyObject d, bool hover)
        {
            d.SetValue(HoverProperty, hover);
        }

        private static void OnHoverChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            UIElement element = d as UIElement;
            if (element != null && (bool)e.NewValue == true)
            {
                element.Focus();
            }
        }
    }
}
