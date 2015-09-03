#if UNITY_STANDALONE || UNITY_ANDROID || UNITY_IOS || UNITY_WINRT_8_1
#define UNITY
#endif

#if UNITY
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

namespace MenuDemo
{
	/// <summary>
	/// Interaction logic for MainMenu.xaml
	/// </summary>
	#if UNITY
	[UserControlSource("Assets/MenuDemo/MainMenu.xaml")]
	#endif
	public partial class MainMenu : UserControl
	{
		Storyboard _fadeIn;
        Storyboard _fadeOut;

        ToggleButton _start;
        ToggleButton _settings;
        ToggleButton _exit;

        public void FadeIn()
        {
            _fadeIn.Begin();
        }

        public void FadeOut()
        {
            _fadeOut.Begin();
        }
		
		public MainMenu()
		{
			this.Initialized += OnInitialized;

			this.InitializeComponent();
		}
		
		private void OnInitialized(object sender, EventArgs e)
		{
			_fadeIn = (Storyboard)FindResource("FadeIn");
            _fadeOut = (Storyboard)FindResource("FadeOut");

            _fadeIn.Completed += OnFadeInCompleted;

            _start = (ToggleButton)FindName("Start");
            _settings = (ToggleButton)FindName("Settings");
            _exit = (ToggleButton)FindName("Exit");
			
			PreviewKeyDown += ProcessKeyDown;
		}
		
		#if !UNITY
		private void OnFadeInCompleted(object sender, EventArgs e)
		#else
		private void OnFadeInCompleted(object sender, TimelineEventArgs e)
		#endif
        {
            _start.Focus();
        }
		
		private void ProcessKeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Return)
            {
                if (_start.IsKeyboardFocused)
                {
                    CommandHelper.TryExecute(_start.Command);
                }
                else if (_settings.IsKeyboardFocused)
                {
                    CommandHelper.TryExecute(_settings.Command);
                }
                else if (_exit.IsKeyboardFocused)
                {
                    CommandHelper.TryExecute(_exit.Command);
                }
            }
            else if (e.Key == Key.Escape)
            {
                CommandHelper.TryExecute(_exit.Command);
            }
        }
	}
}
