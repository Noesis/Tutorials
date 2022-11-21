#if NOESIS
using Noesis;
using Float = System.Single;
#else
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using Float = System.Double;
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

        private void Slider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<Float> e)
        {
            if (!this.IsUpdatingSliders)
            {
                if (this.Color == null || this.Color.IsFrozen)
                {
                    this.IsUpdatingColor = true;
                    this.Color = new SolidColorBrush();
                    this.IsUpdatingColor = false;
                }
            
                UpdateColor(this.R.Value, this.G.Value, this.B.Value, this.A.Value);
            }
        }
        
        private void UpdateSliders(Color color)
        {
            this.IsUpdatingSliders = true;
            this.R.Value = (Float)color.R;
            this.G.Value = (Float)color.G;
            this.B.Value = (Float)color.B;
            this.A.Value = (Float)color.A;
            this.IsUpdatingSliders = false;
        }
        
        private void UpdateColor(Float r, Float g, Float b, Float a)
        {
            this.IsUpdatingColor = true;
            this.Color.Color = new Color() { R = (byte)r, G = (byte)g, B = (byte)b, A = (byte)a };
            this.IsUpdatingColor = false;
        }

#if NOESIS
        private void InitializeComponent()
        {
            Noesis.GUI.LoadComponent(this, "/BlendTutorial;component/ColorSelector.xaml");

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

        private Slider R = null;
        private Slider G = null;
        private Slider B = null;
        private Slider A = null;
#endif
    }
}
