using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

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
        
        public static DependencyProperty ColorProperty = DependencyProperty.Register("Color", typeof(SolidColorBrush), typeof(ColorSelector),
            new PropertyMetadata(Brushes.Transparent, new PropertyChangedCallback(OnColorChanged)));
        
        public SolidColorBrush Color
        {
            get { return (SolidColorBrush)GetValue(ColorProperty); }
            set { SetValue(ColorProperty, value); }
        }
        
        private bool IsUpdatingColor = false;
        private bool IsUpdatingSliders = false;
        
        private static void OnColorChanged(object sender, System.Windows.DependencyPropertyChangedEventArgs e)
        {
            ColorSelector colorSelector = sender as ColorSelector;
            if (colorSelector != null && !colorSelector.IsUpdatingColor)
            {
                colorSelector.UpdateSliders(colorSelector.Color.Color);
            }
        }

        private void Slider_ValueChanged(object sender, System.Windows.RoutedPropertyChangedEventArgs<double> e)
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
        
        private void UpdateSliders(System.Windows.Media.Color color)
        {
            this.IsUpdatingSliders = true;
            this.R.Value = (Double)color.R;
            this.G.Value = (Double)color.G;
            this.B.Value = (Double)color.B;
            this.A.Value = (Double)color.A;
            this.IsUpdatingSliders = false;
        }
        
        private void UpdateColor(Double r, Double g, Double b, Double a)
        {
            this.IsUpdatingColor = true;
            this.Color.Color = System.Windows.Media.Color.FromArgb((byte)a, (byte)r, (byte)g, (byte)b);
            this.IsUpdatingColor = false;
        }
    }
}
