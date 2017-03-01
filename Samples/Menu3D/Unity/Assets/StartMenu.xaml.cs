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
            Noesis.GUI.LoadComponent(this, "Assets/StartMenu.xaml");
        }
#endif

        private void OnInitialized(object sender, EventArgs e)
        {
            _fadeIn = (Storyboard)FindResource("FadeIn");
            _fadeOut = (Storyboard)FindResource("FadeOut");

            _activateCasual = (Storyboard)FindResource("ActivateCasual");

            _fadeIn.Completed += OnFadeInCompleted;

            _casual = (ToggleButton)FindName("Casual");
            _normal = (ToggleButton)FindName("Normal");
            _veteran = (ToggleButton)FindName("Veteran");
            _back = (ToggleButton)FindName("Back");
            
            PreviewKeyDown += ProcessKeyDown;
        }

#if NOESIS
        private void OnFadeInCompleted(object sender, TimelineEventArgs e)
#else
        private void OnFadeInCompleted(object sender, EventArgs e)
#endif
        {
            _casual.Focus();
        }
        
        private void ProcessKeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Return)
            {
                if (_casual.IsKeyboardFocused)
                {
                    CommandHelper.TryExecute(_casual.Command);
                }
                else if (_normal.IsKeyboardFocused)
                {
                    CommandHelper.TryExecute(_normal.Command);
                }
                else if (_veteran.IsKeyboardFocused)
                {
                    CommandHelper.TryExecute(_veteran.Command);
                }
                else if (_back.IsKeyboardFocused)
                {
                    CommandHelper.TryExecute(_back.Command);
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
        ToggleButton _normal;
        ToggleButton _veteran;
        ToggleButton _back;
        #endregion
    }
}
