#if NOESIS
using Noesis;
#else
using System.Windows;
using System.Windows.Media;
#endif

namespace UserControls
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            _bg = (SolidColorBrush)FindName("BgColor");
            _fg = (SolidColorBrush)FindName("FgColor");
        }

#if NOESIS
        private void InitializeComponent()
        {
            GUI.LoadComponent(this, "MainWindow.xaml");
        }

        protected override bool ConnectEvent(object source, string eventName, string handlerName)
        {
            if (eventName == "ValueChanged" && handlerName == "BgR_ValueChanged")
            {
                ((NumericUpDown)source).ValueChanged += BgR_ValueChanged;
                return true;
            }
            if (eventName == "ValueChanged" && handlerName == "BgG_ValueChanged")
            {
                ((NumericUpDown)source).ValueChanged += BgG_ValueChanged;
                return true;
            }
            if (eventName == "ValueChanged" && handlerName == "BgB_ValueChanged")
            {
                ((NumericUpDown)source).ValueChanged += BgB_ValueChanged;
                return true;
            }
            if (eventName == "ValueChanged" && handlerName == "FgR_ValueChanged")
            {
                ((NumericUpDown)source).ValueChanged += FgR_ValueChanged;
                return true;
            }
            if (eventName == "ValueChanged" && handlerName == "FgG_ValueChanged")
            {
                ((NumericUpDown)source).ValueChanged += FgG_ValueChanged;
                return true;
            }
            if (eventName == "ValueChanged" && handlerName == "FgB_ValueChanged")
            {
                ((NumericUpDown)source).ValueChanged += FgB_ValueChanged;
                return true;
            }
            return false;
        }
#endif

        private void BgR_ValueChanged(object sender, ValueChangedEventArgs e)
        {
            if (_bg != null)
            {
                _bg.Color = Color.FromRgb((byte)e.NewValue, _bg.Color.G, _bg.Color.B);
            }
        }

        private void BgG_ValueChanged(object sender, ValueChangedEventArgs e)
        {
            if (_bg != null)
            {
                _bg.Color = Color.FromRgb(_bg.Color.R, (byte)e.NewValue, _bg.Color.B);
            }
        }

        private void BgB_ValueChanged(object sender, ValueChangedEventArgs e)
        {
            if (_bg != null)
            {
                _bg.Color = Color.FromRgb(_bg.Color.R, _bg.Color.G, (byte)e.NewValue);
            }
        }

        private void FgR_ValueChanged(object sender, ValueChangedEventArgs e)
        {
            if (_fg != null)
            {
                _fg.Color = Color.FromRgb((byte)e.NewValue, _fg.Color.G, _fg.Color.B);
            }
        }

        private void FgG_ValueChanged(object sender, ValueChangedEventArgs e)
        {
            if (_fg != null)
            {
                _fg.Color = Color.FromRgb(_fg.Color.R, (byte)e.NewValue, _fg.Color.B);
            }
        }

        private void FgB_ValueChanged(object sender, ValueChangedEventArgs e)
        {
            if (_fg != null)
            {
                _fg.Color = Color.FromRgb(_fg.Color.R, _fg.Color.G, (byte)e.NewValue);
            }
        }

        private SolidColorBrush _bg;
        private SolidColorBrush _fg;
    }
}
