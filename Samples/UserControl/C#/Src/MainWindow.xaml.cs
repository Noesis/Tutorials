#if NOESIS
using Noesis;
using NoesisApp;
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
        }

#if NOESIS
        private SolidColorBrush BgColor;
        private SolidColorBrush FgColor;

        private void InitializeComponent()
        {
            GUI.LoadComponent(this, "MainWindow.xaml");

            this.BgColor = (SolidColorBrush)FindName("BgColor");
            this.FgColor = (SolidColorBrush)FindName("FgColor");
        }

        protected override bool ConnectEvent(object source, string eventName, string handlerName)
        {
            if (eventName == "ValueChanged" && handlerName == "BgR_ValueChanged")
            {
                System.WeakReference wr = new System.WeakReference(this);
                ((NumericUpDown)source).ValueChanged += (s, e) => { ((MainWindow)wr.Target).BgR_ValueChanged(s, e); };
                return true;
            }
            if (eventName == "ValueChanged" && handlerName == "BgG_ValueChanged")
            {
                System.WeakReference wr = new System.WeakReference(this);
                ((NumericUpDown)source).ValueChanged += (s, e) => { ((MainWindow)wr.Target).BgG_ValueChanged(s, e); };
                return true;
            }
            if (eventName == "ValueChanged" && handlerName == "BgB_ValueChanged")
            {
                System.WeakReference wr = new System.WeakReference(this);
                ((NumericUpDown)source).ValueChanged += (s, e) => { ((MainWindow)wr.Target).BgB_ValueChanged(s, e); };
                return true;
            }
            if (eventName == "ValueChanged" && handlerName == "FgR_ValueChanged")
            {
                System.WeakReference wr = new System.WeakReference(this);
                ((NumericUpDown)source).ValueChanged += (s, e) => { ((MainWindow)wr.Target).FgR_ValueChanged(s, e); };
                return true;
            }
            if (eventName == "ValueChanged" && handlerName == "FgG_ValueChanged")
            {
                System.WeakReference wr = new System.WeakReference(this);
                ((NumericUpDown)source).ValueChanged += (s, e) => { ((MainWindow)wr.Target).FgG_ValueChanged(s, e); };
                return true;
            }
            if (eventName == "ValueChanged" && handlerName == "FgB_ValueChanged")
            {
                System.WeakReference wr = new System.WeakReference(this);
                ((NumericUpDown)source).ValueChanged += (s, e) => { ((MainWindow)wr.Target).FgB_ValueChanged(s, e); };
                return true;
            }
            return false;
        }
#endif

        private void BgR_ValueChanged(object sender, ValueChangedEventArgs e)
        {
            if (this.BgColor != null)
            {
                this.BgColor.Color = Color.FromRgb((byte)e.NewValue, this.BgColor.Color.G, this.BgColor.Color.B);
            }
        }

        private void BgG_ValueChanged(object sender, ValueChangedEventArgs e)
        {
            if (this.BgColor != null)
            {
                this.BgColor.Color = Color.FromRgb(this.BgColor.Color.R, (byte)e.NewValue, this.BgColor.Color.B);
            }
        }

        private void BgB_ValueChanged(object sender, ValueChangedEventArgs e)
        {
            if (this.BgColor != null)
            {
                this.BgColor.Color = Color.FromRgb(this.BgColor.Color.R, this.BgColor.Color.G, (byte)e.NewValue);
            }
        }

        private void FgR_ValueChanged(object sender, ValueChangedEventArgs e)
        {
            if (this.FgColor != null)
            {
                this.FgColor.Color = Color.FromRgb((byte)e.NewValue, this.FgColor.Color.G, this.FgColor.Color.B);
            }
        }

        private void FgG_ValueChanged(object sender, ValueChangedEventArgs e)
        {
            if (this.FgColor != null)
            {
                this.FgColor.Color = Color.FromRgb(this.FgColor.Color.R, (byte)e.NewValue, this.FgColor.Color.B);
            }
        }

        private void FgB_ValueChanged(object sender, ValueChangedEventArgs e)
        {
            if (this.FgColor != null)
            {
                this.FgColor.Color = Color.FromRgb(this.FgColor.Color.R, this.FgColor.Color.G, (byte)e.NewValue);
            }
        }
    }
}
