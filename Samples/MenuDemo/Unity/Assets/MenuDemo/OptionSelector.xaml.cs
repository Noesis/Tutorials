#if UNITY_STANDALONE || UNITY_ANDROID || UNITY_IOS || UNITY_WINRT_8_1
#define UNITY
#endif

#if UNITY
using Noesis;
#else
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
#endif
using System;
using System.Collections.ObjectModel;
using System.Collections.Specialized;

namespace MenuDemo
{
	/// <summary>
	/// Interaction logic for OptionSelector.xaml
	/// </summary>
	#if UNITY
	[UserControlSource("Assets/MenuDemo/OptionSelector.xaml")]
	#endif
	public partial class OptionSelector : UserControl
	{
		RepeatButton _prevButton;
		RepeatButton _nextButton;
		
		public OptionSelector()
		{			
			#if !UNITY
			this.Initialized += OnInitialized;
			#endif
			
			this.InitializeComponent();
		}
		
		#if !UNITY
		private void OnInitialized(object sender, EventArgs e)
		#else
		public void OnPostInit()
		#endif
		{
			_prevButton = (RepeatButton)FindName("PrevButton");
			_nextButton = (RepeatButton)FindName("NextButton");
			
			_prevButton.Click += OnPrev;
			_nextButton.Click += OnNext;

			UpdateSelectedOption();
			UpdateButtons();
		}
		
		ObservableCollection<UIElement> _options;
		public ObservableCollection<UIElement> Options
		{
			get
			{
				if (_options == null)
				{
					_options = new ObservableCollection<UIElement>();
					_options.CollectionChanged += OnCollectionChanged;
				}
				return _options;
			}
			set
			{
				_options = value;
				_options.CollectionChanged += OnCollectionChanged;
			}
		}
		
		private int NumOptions { get { return _options == null ? 0 : _options.Count; } }

        private void OnCollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
        	UpdateSelectedOption();
            UpdateButtons();
        }

		private static DependencyProperty SelectedIndexProperty = DependencyProperty.Register(
			"SelectedIndex", typeof(int), typeof(OptionSelector),
			new PropertyMetadata(-1, new PropertyChangedCallback(OnIndexChanged)));
		
		public int SelectedIndex
		{
			get { return (int)GetValue(SelectedIndexProperty); }
			set { SetValue(SelectedIndexProperty, value); }
		}
		
		private static void OnIndexChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
		{
            OptionSelector sel = d as OptionSelector;
            if (sel != null)
            {
                sel.OnIndexChanged();
            }
		}
		
		private void OnIndexChanged()
		{
            UpdateSelectedOption();
            UpdateButtons();
		}
		
		private int LastIndex { get { return NumOptions - 1; } }
		
		private int Index { get { return NumOptions == 0 ? -1 : Math.Max(0, Math.Min(SelectedIndex, LastIndex)); } }
		
		private static DependencyProperty SelectedOptionProperty = DependencyProperty.Register(
            "SelectedOption", typeof(object), typeof(OptionSelector),
			new PropertyMetadata(null));

        public object SelectedOption
        {
            get { return GetValue(SelectedOptionProperty); }
            private set { SetValue(SelectedOptionProperty, value); }
        }
		
		private void OnPrev(object sender, RoutedEventArgs e)
		{
			--SelectedIndex;
		}
		
		private void OnNext(object sender, RoutedEventArgs e)
		{
			++SelectedIndex;
		}
		
		private void UpdateSelectedOption()
        {
            SelectedOption = Index < 0 ? null : Options[Index];
        }

        private void UpdateButtons()
        {
            if (_prevButton != null)
            {
                _prevButton.IsEnabled = Index > 0;
            }
            if (_nextButton != null)
            {
                _nextButton.IsEnabled = Index < LastIndex;
            }
        }
	}
}