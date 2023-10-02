using System;
using System.Windows;
using System.Windows.Media;

namespace BrushShaders
{
    public class NoiseBrush : NoesisGUIExtensions.BrushShader
    {
        public Color Color
        {
            get { return (Color)GetValue(ColorProperty); }
            set { SetValue(ColorProperty, value); }
        }

        public static readonly DependencyProperty ColorProperty = DependencyProperty.Register(
            "Color", typeof(Color), typeof(NoiseBrush), new PropertyMetadata(Colors.White));

        public double ScaleX
        {
            get { return (double)GetValue(ScaleXProperty); }
            set { SetValue(ScaleXProperty, value); }
        }

        public static readonly DependencyProperty ScaleXProperty = DependencyProperty.Register(
            "ScaleX", typeof(double), typeof(NoiseBrush), new PropertyMetadata(1.0));

        public double ScaleY
        {
            get { return (double)GetValue(ScaleYProperty); }
            set { SetValue(ScaleYProperty, value); }
        }

        public static readonly DependencyProperty ScaleYProperty = DependencyProperty.Register(
            "ScaleY", typeof(double), typeof(NoiseBrush), new PropertyMetadata(1.0));

        public double Time
        {
            get { return (double)GetValue(TimeProperty); }
            set { SetValue(TimeProperty, value); }
        }

        public static readonly DependencyProperty TimeProperty = DependencyProperty.Register(
            "Time", typeof(double), typeof(NoiseBrush), new PropertyMetadata(0.0));

        public double Seed
        {
            get { return (double)GetValue(SeedProperty); }
            set { SetValue(SeedProperty, value); }
        }

        public static double GetSeed(DependencyObject obj)
        {
            return (double)obj.GetValue(SeedProperty);
        }

        public static void SetSeed(DependencyObject obj, double value)
        {
            obj.SetValue(SeedProperty, value);
        }

        public static readonly DependencyProperty SeedProperty = DependencyProperty.RegisterAttached(
            "Seed", typeof(double), typeof(NoiseBrush), new PropertyMetadata(0.0));
    }
}
