#if NOESIS
using Noesis;
#else
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
#endif

namespace BlendTutorial
{
    /// <summary>
    /// Interaction logic for ColorSelector.xaml
    /// </summary>
    public partial class ColorSelector : UserControl
    {
        public ColorSelector()
        {
            this.InitializeComponent();
        }

#if NOESIS
        private Slider R = null;
        private Slider G = null;
        private Slider B = null;
        private Slider A = null;

        private void InitializeComponent()
        {
            Noesis.GUI.LoadComponent(this, "ColorSelector.xaml");

            this.R = (Slider)FindName("R");
            this.G = (Slider)FindName("G");
            this.B = (Slider)FindName("B");
            this.A = (Slider)FindName("A");
        }

        protected override bool ConnectEvent(object source, string eventName, string handlerName)
        {
            if (eventName == "ValueChanged" && handlerName == "Slider_ValueChanged")
            {
                ((UserControl)source).AddHandler(Slider.ValueChangedEvent,
                    new RoutedPropertyChangedEventHandler<float>(Slider_ValueChanged));
                return true;
            }
            return false;
        }
#endif

        public static DependencyProperty ColorProperty = DependencyProperty.Register(
            "Color", typeof(SolidColorBrush), typeof(ColorSelector),
            new PropertyMetadata(Brushes.Transparent, new PropertyChangedCallback(OnColorChanged)));

        public SolidColorBrush Color
        {
            get { return (SolidColorBrush)GetValue(ColorProperty); }
            set { SetValue(ColorProperty, value); }
        }
        
        private bool IsUpdatingColor = false;
        private bool IsUpdatingSliders = false;
        
        private static void OnColorChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            ColorSelector colorSelector = sender as ColorSelector;
            if (colorSelector != null && !colorSelector.IsUpdatingColor)
            {
                colorSelector.UpdateSliders(colorSelector.Color.Color);
            }
        }

#if NOESIS
        private void Slider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<float> e)
#else
        private void Slider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
#endif
        {
            if (!this.IsUpdatingSliders)
            {
                if (this.Color == null || this.Color.IsFrozen)
                {
                    this.IsUpdatingColor = true;
                    this.Color = new SolidColorBrush();
                    this.IsUpdatingColor = false;
                }
            
                UpdateColor((float)this.R.Value, (float)this.G.Value, (float)this.B.Value, (float)this.A.Value);
            }
        }
        
        private void UpdateSliders(Color color)
        {
            this.IsUpdatingSliders = true;
            this.R.Value = (float)color.R;
            this.G.Value = (float)color.G;
            this.B.Value = (float)color.B;
            this.A.Value = (float)color.A;
            this.IsUpdatingSliders = false;
        }
        
        private void UpdateColor(float r, float g, float b, float a)
        {
            this.IsUpdatingColor = true;
            this.Color.Color = new Color() { R = (byte)r, G = (byte)g, B = (byte)b, A = (byte)a };
            this.IsUpdatingColor = false;
        }
    }
}
