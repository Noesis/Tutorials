#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
#else
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Input;
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
            this.Initialized += OnInitialized;
            this.InitializeComponent();
        }

        public void FadeIn()
        {
            _fadeIn.Begin();
        }

        public void FadeOut()
        {
            _fadeOut.Begin();
        }

#if NOESIS
        private void InitializeComponent()
        {
            Noesis.GUI.LoadComponent(this, "Assets/NoesisGUI/Samples/Menu3D/MainMenu.xaml");
        }
#endif

        private void OnInitialized(object sender, EventArgs e)
        {
            _fadeIn = (Storyboard)FindResource("FadeIn");
            _fadeOut = (Storyboard)FindResource("FadeOut");

            _fadeIn.Completed += OnFadeInCompleted;

            _start = (ToggleButton)FindName("Start");
            _exit = (ToggleButton)FindName("Exit");

            PreviewKeyDown += ProcessKeyDown;
        }

#if NOESIS
        private void OnFadeInCompleted(object sender, TimelineEventArgs e)
        {
            _start.Focus();
        }
#else
        private void OnFadeInCompleted(object sender, EventArgs e)
        {
            Dispatcher.BeginInvoke(new Action(() =>
            {
                _start.Focus();
            }));
        }
#endif

        private void ProcessKeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Return)
            {
#if NOESIS
                object source = e.Source;
#else
                object source = e.OriginalSource;
#endif

                ToggleButton btn = source as ToggleButton;
                if (btn != null)
                {
                    CommandHelper.TryExecute(btn.Command);
                }
            }
            else if (e.Key == Key.Escape)
            {
                CommandHelper.TryExecute(_exit.Command);
            }
        }

        #region Private members
        Storyboard _fadeIn;
        Storyboard _fadeOut;

        ToggleButton _start;
        ToggleButton _exit;
        #endregion
    }
}
