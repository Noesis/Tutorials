#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
#else
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Animation;
#endif

namespace Menu3D
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : UserControl
    {
        public MainWindow()
        {
            this.Loaded += OnLoaded;
            this.SizeChanged += OnSizeChanged;

            this.InitializeComponent();
        }

        private void OnLoaded(object sender, RoutedEventArgs e)
        {
            DataContext = new ViewModel();
        }

        private void OnSizeChanged(object sender, SizeChangedEventArgs e)
        {
            // Remove animated values
            this.SkyAndSun.RenderTransform.BeginAnimation(TranslateTransform.XProperty, null);
            this.Mountains.RenderTransform.BeginAnimation(TranslateTransform.XProperty, null);
            this.FrontTrees.RenderTransform.BeginAnimation(TranslateTransform.XProperty, null);
            this.BackClouds.RenderTransform.BeginAnimation(TranslateTransform.XProperty, null);
            this.FrontClouds.RenderTransform.BeginAnimation(TranslateTransform.XProperty, null);

            // Reset positions according to new size
            UpdateLayout();

            // Restart the background animation
            ((Storyboard)Resources["BackgroundAnim"]).Begin(this);
        }

#if NOESIS
        private void InitializeComponent()
        {
            Noesis.GUI.LoadComponent(this, "Assets/NoesisGUI/Samples/Menu3D/MainWindow.xaml");

            SkyAndSun = (StackPanel)FindName("SkyAndSun");
            Mountains = (StackPanel)FindName("Mountains");
            FrontTrees = (StackPanel)FindName("FrontTrees");
            BackClouds = (StackPanel)FindName("BackClouds");
            FrontClouds = (StackPanel)FindName("FrontClouds");
        }

        StackPanel SkyAndSun;
        StackPanel Mountains;
        StackPanel FrontTrees;
        StackPanel BackClouds;
        StackPanel FrontClouds;
#endif
    }

#if NOESIS
    public static class AnimatableExtensions
    {
        public static void BeginAnimation(this Animatable animatable, DependencyProperty dp, object dummy)
        {
            animatable.ClearAnimation(dp);
        }
    }
#endif
}
