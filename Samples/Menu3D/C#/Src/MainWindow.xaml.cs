#if NOESIS
using Noesis;
using NoesisApp;
#else
using System;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Animation;
#endif

namespace Menu3D
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            System.WeakReference wr = new System.WeakReference(this);
            this.Loaded += (s, e) => { ((MainWindow)wr.Target).OnLoaded(s, e); };
            this.SizeChanged += (s, e) => { ((MainWindow)wr.Target).OnSizeChanged(s, e); };

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
            Noesis.GUI.LoadComponent(this, "MainWindow.xaml");

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
}
