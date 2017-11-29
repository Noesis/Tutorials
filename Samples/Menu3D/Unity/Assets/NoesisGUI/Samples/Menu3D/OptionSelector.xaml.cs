#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
#else
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
#endif
using System.Collections.ObjectModel;
using System.Collections.Specialized;

namespace Menu3D
{
    /// <summary>
    /// Interaction logic for OptionSelector.xaml
    /// </summary>
    public partial class OptionSelector : UserControl
    {
        public OptionSelector()
        {
            this.Initialized += OnInitialized;
            
            this.InitializeComponent();
        }

#if NOESIS
        private void InitializeComponent()
        {
            Noesis.GUI.LoadComponent(this, "Assets/NoesisGUI/Samples/Menu3D/OptionSelector.xaml");
        }
#endif

        private void OnInitialized(object sender, EventArgs e)
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
                    _options.CollectionChanged += OnOptionsChanged;
                }
                return _options;
            }
            set
            {
                if (_options != null)
                {
                    _options.CollectionChanged -= OnOptionsChanged;
                }

                _options = value;

                if (_options != null)
                {
                    _options.CollectionChanged += OnOptionsChanged;
                }
            }
        }

        private int NumOptions { get { return _options == null ? 0 : _options.Count; } }

        private void OnOptionsChanged(object sender, NotifyCollectionChangedEventArgs e)
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
                sel.UpdateSelectedOption();
                sel.UpdateButtons();
            }
        }

        private int LastIndex { get { return NumOptions - 1; } }

        private int Index { get { return NumOptions == 0 ? -1 : System.Math.Max(0, System.Math.Min(SelectedIndex, LastIndex)); } }

        public void CycleNext()
        {
            if (NumOptions > 0)
            {
                SelectedIndex = Index < LastIndex ? Index + 1 : 0;
            }
        }

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

        #region Private members
        RepeatButton _prevButton;
        RepeatButton _nextButton;
        #endregion
    }
}