#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
#else
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Input;
using System.Windows.Media.Animation;
#endif

namespace ControlGallery
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : UserControl
    {
        public MainWindow()
        {
            this.Initialized += OnInitialized;
            this.InitializeComponent();
        }

#if NOESIS
        private void InitializeComponent()
        {
            Noesis.GUI.LoadComponent(this, "Assets/NoesisGUI/Samples/ControlGallery/MainWindow.xaml");
        }
#endif

        private void OnInitialized(object sender, EventArgs args)
        {
            SizeChanged += OnSizeChanged;

            _styleSelector = (ComboBox)FindName("StyleSelector");
            _styleSelector.SelectionChanged += OnStyleSelectionChanged;

            _noesisStyleResources = (ResourceDictionary)LoadXaml("NoesisStyle");
            _simpleStyleResources = (ResourceDictionary)LoadXaml("SimpleStyle");
            _windowsStyleResources = (ResourceDictionary)LoadXaml("WindowsStyle");

            _selector = (Grid)FindName("Selector");
            _sampleSelector = (TreeView)FindName("SampleSelector");
            _sampleSelector.SelectedItemChanged += OnSamplesSelectionChanged;

            _sampleContainer = (Viewbox)FindName("SampleContainer");
            _sampleContainer1 = (Border)FindName("SampleContainer1");
            _sampleContainer2 = (Border)FindName("SampleContainer2");

            _sampleContainer.Resources = _noesisStyleResources;

            _sampleOverlay = (Grid)FindName("SampleOverlay");
            _sampleOverlay.MouseDown += OnSampleOverlayMouseDown;

            _showContainer1 = (Storyboard)Resources["ShowContainer1"];
            _showContainer2 = (Storyboard)Resources["ShowContainer2"];

            _selectorTopContainer = (Border)FindName("SelectorTopContainer");
            _selectorTop = (StackPanel)FindName("SelectorTop");
            _selectorTopExpand = (ToggleButton)FindName("SelectorTopExpand");

            _selectorLeftContainer = (Border)FindName("SelectorLeftContainer");
            _selectorLeft = (StackPanel)FindName("SelectorLeft");
            _selectorLeftExpand = (ToggleButton)FindName("SelectorLeftExpand");

            _itemHeight = (Decorator)FindName("ItemHeight");
        }

        void OnStyleSelectionChanged(object sender, SelectionChangedEventArgs args)
        {
            switch (_styleSelector.SelectedIndex)
            {
                case 0:
                    _sampleContainer.Resources = _noesisStyleResources;
                    break;

                case 1:
                    _sampleContainer.Resources = _simpleStyleResources;
                    break;

                case 2:
                    _sampleContainer.Resources = _windowsStyleResources;
                    break;
            }

            args.Handled = true;
        }

        void OnSamplesSelectionChanged(object sender, RoutedPropertyChangedEventArgs<object> args)
        {
            object newValue = args.NewValue;
            TreeViewItem tvi = (TreeViewItem)newValue;
            if (tvi != null && !tvi.HasItems)
            {
                string sampleName = (string)tvi.Tag;
                if (_lastSample != sampleName)
                {
                    LoadSample(sampleName);
                    _lastSample = sampleName;
                }
            }
        }

        void LoadSample(string sampleName)
        {
            _sampleSelector.IsEnabled = false;

            UIElement sample = (UIElement)LoadXaml(sampleName);

            if (_sampleContainer1.Child == null)
            {
                // Show container 1
                _sampleContainer1.Child = sample;
                _showContainer1.Completed += OnShowSampleCompleted;
                _showContainer1.Begin();
            }
            else
            {
                // Show container 2
                _sampleContainer2.Child = sample;
                _showContainer2.Completed += OnShowSampleCompleted;
                _showContainer2.Begin();
            }
        }

        object LoadXaml(string xaml)
        {
#if NOESIS
            return Noesis.GUI.LoadXaml("Assets/NoesisGUI/Samples/ControlGallery/Data/" + xaml + ".xaml");
#else
            string path = "/Assets/NoesisGUI/Samples/ControlGallery/Data/" + xaml + ".xaml";
            return Application.LoadComponent(new Uri(path, UriKind.Relative));
#endif
        }

        void OnShowSampleCompleted(object sender, EventArgs e)
        {
            if (_sampleContainer1.Visibility == Visibility.Visible)
            {
                // Container 1 shown
                _showContainer1.Completed -= OnShowSampleCompleted;
                _sampleContainer2.Child = null;
            }
            else
            {
                // Container 2 shown
                _showContainer2.Completed -= OnShowSampleCompleted;
                _sampleContainer1.Child = null;
            }

            _sampleSelector.IsEnabled = true;
        }

        void OnSizeChanged(object sender, SizeChangedEventArgs e)
        {
            Size newSize = e.NewSize;
            if (newSize.Width > newSize.Height)
            {
                // Landscape
                _selectorTopContainer.Child = null;
                _selectorLeftContainer.Child = _selector;
                _selectorTop.Visibility = Visibility.Collapsed;
                _selectorLeft.Visibility = Visibility.Visible;
                _selectorTopExpand.IsChecked = false;
                _itemHeight.Height = newSize.Width * 0.05f;
            }
            else
            {
                // Portrait
                _selectorLeftContainer.Child = null;
                _selectorTopContainer.Child = _selector;
                _selectorLeft.Visibility = Visibility.Collapsed;
                _selectorTop.Visibility = Visibility.Visible;
                _selectorLeftExpand.IsChecked = false;
                _itemHeight.Height = newSize.Height * 0.05f;
            }
        }

        void OnSampleOverlayMouseDown(object sender, MouseButtonEventArgs e)
        {
            _selectorLeftExpand.IsChecked = false;
            _selectorTopExpand.IsChecked = false;
        }

#region Private members
        ComboBox _styleSelector;
        ResourceDictionary _noesisStyleResources;
        ResourceDictionary _simpleStyleResources;
        ResourceDictionary _windowsStyleResources;

        Grid _selector;
        TreeView _sampleSelector;
        string _lastSample;

        Viewbox _sampleContainer;
        Border _sampleContainer1;
        Border _sampleContainer2;
        Grid _sampleOverlay;

        Storyboard _showContainer1;
        Storyboard _showContainer2;

        Border _selectorTopContainer;
        StackPanel _selectorTop;
        ToggleButton _selectorTopExpand;

        Border _selectorLeftContainer;
        StackPanel _selectorLeft;
        ToggleButton _selectorLeftExpand;

        Decorator _itemHeight;
#endregion
    }
}
