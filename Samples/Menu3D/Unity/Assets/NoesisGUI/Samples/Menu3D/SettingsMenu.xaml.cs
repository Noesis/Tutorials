#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
#else
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
#endif

namespace Menu3D
{
    /// <summary>
    /// Interaction logic for SettingsMenu.xaml
    /// </summary>
    public partial class SettingsMenu : UserControl
    {
        public SettingsMenu()
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
            Noesis.GUI.LoadComponent(this, "Assets/NoesisGUI/Samples/Menu3D/SettingsMenu.xaml");
        }
#endif

        private void OnInitialized(object sender, EventArgs e)
        {
            _fadeIn = (Storyboard)FindResource("FadeIn");
            _fadeOut = (Storyboard)FindResource("FadeOut");

            _fadeIn.Completed += OnFadeInCompleted;

            _texDetail = (HeaderedContentControl)FindName("TexDetail");
            _back = (ToggleButton)FindName("Back");

            PreviewKeyDown += ProcessKeyDown;
        }

#if NOESIS
        private void OnFadeInCompleted(object sender, TimelineEventArgs e)
        {
            _texDetail.Focus();
        }
#else
        private void OnFadeInCompleted(object sender, EventArgs e)
        {
            Dispatcher.BeginInvoke(new Action(() =>
            {
                _texDetail.Focus();
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

                HeaderedContentControl control = source as HeaderedContentControl;
                if (control != null)
                {
                    OptionSelector selector = control.Content as OptionSelector;
                    if (selector != null)
                    {
                        selector.CycleNext();
                        return;
                    }

                    CheckBox check = control.Content as CheckBox;
                    if (check != null)
                    {
                        check.IsChecked = !check.IsChecked;
                        return;
                    }

                    return;
                }

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

        HeaderedContentControl _texDetail;
        ToggleButton _back;
        #endregion
    }
}
