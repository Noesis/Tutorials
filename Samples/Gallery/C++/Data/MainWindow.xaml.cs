using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace Gallery
{
    public class ColorItem
    {
        public string Name { get; set; }
        public Color Color { get; set; }
    }

    public class Category
    {
        public string Name { get; set; }
        public List<Sample> Samples { get; set; }
    }

    public class Sample
    {
        public string Name { get; set; }
        public string Icon { get; set; }
    }

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            Categories = new List<Category>
            {
                new Category
                {
                    Name = "Basic input",
                    Samples = new List<Sample>
                    {
                        new Sample { Name = "Button", Icon = "A" },
                        new Sample { Name = "RepeatButton", Icon = "B" },
                        new Sample { Name = "ToggleButton", Icon = "C" },
                        new Sample { Name = "CheckBox", Icon = "D" },
                        new Sample { Name = "RadioButton", Icon = "E" },
                        new Sample { Name = "Slider", Icon = "F" }
                    }
                },
                new Category
                {
                    Name = "Text",
                    Samples = new List<Sample>
                    {
                        new Sample { Name = "TextBlock", Icon = "G" },
                        new Sample { Name = "TextBox", Icon = "H" },
                        new Sample { Name = "PasswordBox", Icon = "I" },
                        new Sample { Name = "Hyperlink", Icon = "J" }
                    }
                },
                new Category
                {
                    Name = "Collections",
                    Samples = new List<Sample>
                    {
                        new Sample { Name = "ItemsControl", Icon = "K" },
                        new Sample { Name = "ComboBox", Icon = "L" },
                        new Sample { Name = "ListBox", Icon = "M" },
                        new Sample { Name = "ListView", Icon = "N" },
                        new Sample { Name = "TreeView", Icon = "O" },
                        new Sample { Name = "TabControl", Icon = "P" }
                    }
                },
                new Category
                {
                    Name = "Layout",
                    Samples = new List<Sample>
                    {
                        new Sample { Name = "Canvas", Icon = "Q" },
                        new Sample { Name = "StackPanel", Icon = "R" },
                        new Sample { Name = "WrapPanel", Icon = "S" },
                        new Sample { Name = "DockPanel", Icon = "T" },
                        new Sample { Name = "Grid", Icon = "U" },
                        new Sample { Name = "UniformGrid", Icon = "V" },
                        new Sample { Name = "GroupBox", Icon = "W" },
                        new Sample { Name = "Expander", Icon = "X" },
                        new Sample { Name = "ScrollViewer", Icon = "Y" }
                    }
                },
                new Category
                {
                    Name = "Menus and Toolbars",
                    Samples = new List<Sample>
                    {
                        new Sample { Name = "Menu", Icon = "Z" },
                        new Sample { Name = "ContextMenu", Icon = "Z" },
                        new Sample { Name = "ToolBar", Icon = "a" }
                    }
                },
                new Category
                {
                    Name = "Status and Info",
                    Samples = new List<Sample>
                    {
                        new Sample { Name = "StatusBar", Icon = "b" },
                        new Sample { Name = "ProgressBar", Icon = "c" },
                        new Sample { Name = "ToolTip", Icon = "d" }
                    }
                },
                new Category
                {
                    Name = "Media",
                    Samples = new List<Sample>
                    {
                        new Sample { Name = "Brushes", Icon = "e" },
                        new Sample { Name = "Image", Icon = "f" },
                        new Sample { Name = "Effects", Icon = "g" },
                        new Sample { Name = "Animation", Icon = "h" }
                    }
                }
            };

            ThemeColors = new List<ColorItem>
            {
                new ColorItem { Name = "Dark", Color = Color.FromRgb(32, 40, 47) },
                new ColorItem { Name = "Light", Color = Color.FromRgb(246, 247, 248) }
            };

            ThemeAccents = new List<ColorItem>
            {
                new ColorItem { Name = "Red", Color = Color.FromRgb(222, 43, 16) },
                new ColorItem { Name = "Green", Color = Color.FromRgb(42, 166, 12) },
                new ColorItem { Name = "Blue", Color = Color.FromRgb(16, 152, 223) },
                new ColorItem { Name = "Orange", Color = Color.FromRgb(223, 153, 16) },
                new ColorItem { Name = "Emerald", Color = Color.FromRgb(16, 222, 98) },
                new ColorItem { Name = "Purple", Color = Color.FromRgb(137, 78, 237) },
                new ColorItem { Name = "Crimson", Color = Color.FromRgb(222, 16, 67) },
                new ColorItem { Name = "Lime", Color = Color.FromRgb(153, 223, 16) },
                new ColorItem { Name = "Aqua", Color = Color.FromRgb(16, 221, 223) }
            };

            SelectedThemeColor = ThemeColors[1];
            SelectedThemeAccent = ThemeAccents[2];

            UpdateTheme();

            DataContext = this;

            this.SizeChanged += (s, e) =>
            {
                if (ActualWidth > ActualHeight)
                {
                    this.SampleOffset.Width = 250.0;
                    this.SelectorExpanderButton.Visibility = Visibility.Hidden;
                    this.SelectorExpanderButton.IsChecked = false;
                    this.SelectorExpanderButton.IsChecked = true;

                    ScaleTransform dpi = (ScaleTransform)this.LayoutRoot.LayoutTransform;
                    dpi.ScaleX = dpi.ScaleY = Math.Max(1.0, e.NewSize.Width / 1280);
                }
                else
                {
                    this.SampleOffset.Width = 0;
                    this.SelectorExpanderButton.IsChecked = true;
                    this.SelectorExpanderButton.IsChecked = false;
                    this.SelectorExpanderButton.Visibility = Visibility.Visible;

                    ScaleTransform dpi = (ScaleTransform)this.LayoutRoot.LayoutTransform;
                    dpi.ScaleX = dpi.ScaleY = Math.Max(1.0, e.NewSize.Height / 720);
                }
            };
        }

        public double SampleAvailableWidth
        {
            get { return (double)GetValue(SampleAvailableWidthProperty); }
            set { SetValue(SampleAvailableWidthProperty, value); }
        }

        // Using a DependencyProperty as the backing store for SampleAvailableWidth.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty SampleAvailableWidthProperty =
            DependencyProperty.Register("SampleAvailableWidth", typeof(double), typeof(MainWindow), new PropertyMetadata(1280.0));

        public List<Category> Categories { get; private set; }

        private Sample _selectedSample;
        public Sample SelectedSample
        {
            get { return _selectedSample; }
            set
            {
                if (_selectedSample != value && value != null)
                {
                    _selectedSample = value;
                    UpdateSample();
                }
            }
        }

        public List<ColorItem> ThemeColors { get; private set; }
        public List<ColorItem> ThemeAccents { get; private set; }

        private ColorItem _selectedThemeColor;
        public ColorItem SelectedThemeColor
        {
            get { return _selectedThemeColor; }
            set
            {
                if (_selectedThemeColor != value)
                {
                    _selectedThemeColor = value;
                    UpdateTheme();
                }
            }
        }

        private ColorItem _selectedThemeAccent;
        public ColorItem SelectedThemeAccent
        {
            get { return _selectedThemeAccent; }
            set
            {
                if (_selectedThemeAccent != value)
                {
                    _selectedThemeAccent = value;
                    UpdateTheme();
                }
            }
        }

        void UpdateSample()
        {
            string sampleName = string.Format("Samples/{0}.xaml", _selectedSample.Name);
            FrameworkElement sample = (FrameworkElement)Application.LoadComponent(new Uri(sampleName, UriKind.Relative));

            if (sample != null)
            {
                if (this.SampleContainer1.Content == null)
                {
                    this.SampleContainer1.Content = sample;
                }
                else
                {
                    this.SampleContainer2.Content = sample;
                }
            }
        }

        void UpdateTheme()
        {
            if (SelectedThemeColor == null || SelectedThemeAccent == null || DesignerProperties.GetIsInDesignMode(this))
            {
                return;
            }

            ResourceDictionary theme = GetTheme(SelectedThemeColor.Name, SelectedThemeAccent.Name);

            ResourceDictionary resources = this.SamplePanel.Resources;
            resources.MergedDictionaries.Clear();
            resources.MergedDictionaries.Add(theme);
        }

        ResourceDictionary GetTheme(string color, string accent)
        {
            string themeName = string.Format("NoesisTheme.Brushes.{0}{1}.xaml", color, accent);

            ResourceDictionary theme;
            if (ThemeDictionaries.TryGetValue(themeName, out theme))
            {
                return theme;
            }

            Uri uri = new Uri("pack://application:,,,/Noesis.GUI.Extensions;component/Theme/" + themeName);
            theme = new ResourceDictionary { Source = uri };
            ThemeDictionaries.Add(themeName, theme);

            return theme;
        }

        private Dictionary<string, ResourceDictionary> ThemeDictionaries =
            new Dictionary<string, ResourceDictionary>();
    }
}
