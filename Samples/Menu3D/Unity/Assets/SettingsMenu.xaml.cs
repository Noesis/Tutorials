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
        Storyboard _fadeIn;
        Storyboard _fadeOut;

        HeaderedContentControl _texDetail;
        HeaderedContentControl _aalias;
        HeaderedContentControl _soundVol;
        HeaderedContentControl _videoRes;
        HeaderedContentControl _gamma;
        HeaderedContentControl _subtitles;
        ToggleButton _back;
        
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
            Noesis.GUI.LoadComponent(this, "Assets/SettingsMenu.xaml");
        }
#endif

        private void OnInitialized(object sender, EventArgs e)
        {
            _fadeIn = (Storyboard)FindResource("FadeIn");
            _fadeOut = (Storyboard)FindResource("FadeOut");

            _fadeIn.Completed += OnFadeInCompleted;

            _texDetail = (HeaderedContentControl)FindName("TexDetail");
            _aalias = (HeaderedContentControl)FindName("AAlias");
            _soundVol = (HeaderedContentControl)FindName("SoundVol");
            _videoRes = (HeaderedContentControl)FindName("VideoRes");
            _gamma = (HeaderedContentControl)FindName("Gamma");
            _subtitles = (HeaderedContentControl)FindName("Subtitles");
            _back = (ToggleButton)FindName("Back");
            
            PreviewKeyDown += ProcessKeyDown;
        }

#if NOESIS
        private void OnFadeInCompleted(object sender, TimelineEventArgs e)
#else
        private void OnFadeInCompleted(object sender, EventArgs e)
#endif
        {
            _texDetail.Focus();
        }
        
        private void TryCycleOption(HeaderedContentControl control)
        {
            OptionSelector selector = control.Content as OptionSelector;
            if (selector != null)
            {
                selector.SelectedIndex++;
                if (selector.SelectedIndex >= selector.Options.Count)
                {
                    selector.SelectedIndex = 0;
                }
            }
        }
        
        private void TryToggleCheck(HeaderedContentControl control)
        {
            CheckBox check = control.Content as CheckBox;
            if (check != null)
            {
                check.IsChecked = !check.IsChecked;
            }
        }
        
        private void ProcessKeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Return)
            {
                if (_texDetail.IsKeyboardFocused)
                {
                    TryCycleOption(_texDetail);
                }
                else if (_aalias.IsKeyboardFocused)
                {
                    TryToggleCheck(_aalias);
                }
                else if (_soundVol.IsKeyboardFocused)
                {
                    TryCycleOption(_soundVol);
                }
                else if (_videoRes.IsKeyboardFocused)
                {
                    TryCycleOption(_videoRes);
                }
                else if (_gamma.IsKeyboardFocused)
                {
                    TryCycleOption(_gamma);
                }
                else if (_subtitles.IsKeyboardFocused)
                {
                    TryToggleCheck(_subtitles);
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
    }
}
