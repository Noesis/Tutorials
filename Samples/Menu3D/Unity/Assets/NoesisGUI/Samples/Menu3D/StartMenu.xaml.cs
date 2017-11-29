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
    /// Interaction logic for StartMenu.xaml
    /// </summary>
    public partial class StartMenu : UserControl
    {
        public StartMenu()
        {
            this.Initialized += OnInitialized;

            this.InitializeComponent();
        }

        public void FadeIn()
        {
            _fadeIn.Begin();
            _activateCasual.Begin();
        }

        public void FadeOut()
        {
            _fadeOut.Begin();
            _activateCasual.Begin();
        }

#if NOESIS
        private void InitializeComponent()
        {
            Noesis.GUI.LoadComponent(this, "Assets/NoesisGUI/Samples/Menu3D/StartMenu.xaml");
        }
#endif

        private void OnInitialized(object sender, EventArgs e)
        {
            _fadeIn = (Storyboard)FindResource("FadeIn");
            _fadeOut = (Storyboard)FindResource("FadeOut");

            _activateCasual = (Storyboard)FindResource("ActivateCasual");

            _fadeIn.Completed += OnFadeInCompleted;

            _casual = (ToggleButton)FindName("Casual");
            _back = (ToggleButton)FindName("Back");

            PreviewKeyDown += ProcessKeyDown;
        }

#if NOESIS
        private void OnFadeInCompleted(object sender, TimelineEventArgs e)
        {
            _casual.Focus();
        }
#else
        private void OnFadeInCompleted(object sender, EventArgs e)
        {
            Dispatcher.BeginInvoke(new Action(() =>
            {
                _casual.Focus();
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
                CommandHelper.TryExecute(_back.Command);
            }
        }

        #region Private members
        Storyboard _fadeIn;
        Storyboard _fadeOut;

        Storyboard _activateCasual;

        ToggleButton _casual;
        ToggleButton _back;
        #endregion
    }
}
