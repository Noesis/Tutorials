using System;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Effects;

namespace VideoEffect
{
    public class DirectionalBlurEffect : ShaderEffect
    {
        private static readonly PixelShader _pixelShader = new PixelShader();
        public DirectionalBlurEffect() { PixelShader = _pixelShader; }

        #region Angle
        public double Angle
        {
            get { return (double)GetValue(AngleProperty); }
            set { SetValue(AngleProperty, value); }
        }

        public static readonly DependencyProperty AngleProperty = DependencyProperty.Register(
            "Angle", typeof(double), typeof(DirectionalBlurEffect),
            new PropertyMetadata(0.0, PixelShaderConstantCallback(0)));
        #endregion

        #region Radius
        public double Radius
        {
            get { return (double)GetValue(RadiusProperty); }
            set { SetValue(RadiusProperty, value); }
        }

        public static readonly DependencyProperty RadiusProperty = DependencyProperty.Register(
            "Radius", typeof(double), typeof(DirectionalBlurEffect),
            new PropertyMetadata(0.0, PixelShaderConstantCallback(1)));
        #endregion
    }

    public class PixelateEffect : ShaderEffect
    {
        private static readonly PixelShader _pixelShader = new PixelShader();
        public PixelateEffect() { PixelShader = _pixelShader; }

        #region Size
        public double Size
        {
            get { return (double)GetValue(SizeProperty); }
            set { SetValue(SizeProperty, value); }
        }

        public static readonly DependencyProperty SizeProperty = DependencyProperty.Register(
            "Size", typeof(double), typeof(PixelateEffect),
            new PropertyMetadata(5.0, PixelShaderConstantCallback(0)));
        #endregion
    }

    public class TintEffect : ShaderEffect
    {
        private static readonly PixelShader _pixelShader = new PixelShader();
        public TintEffect() { PixelShader = _pixelShader; }

        #region Color
        public Color Color
        {
            get { return (Color)GetValue(ColorProperty); }
            set { SetValue(ColorProperty, value); }
        }

        public static readonly DependencyProperty ColorProperty = DependencyProperty.Register(
            "Color", typeof(Color), typeof(TintEffect),
            new PropertyMetadata(Colors.Black, PixelShaderConstantCallback(0)));
        #endregion
    }

    public class ChromaticAberrationEffect : ShaderEffect
    {
        private static PixelShader _pixelShader = new PixelShader();
        public ChromaticAberrationEffect() { PixelShader = _pixelShader; }

        #region Amount
        public double Amount
        {
            get { return (double)GetValue(AmountProperty); }
            set { SetValue(AmountProperty, value); }
        }

        public static readonly DependencyProperty AmountProperty = DependencyProperty.Register(
            "Amount", typeof(double), typeof(ChromaticAberrationEffect),
            new PropertyMetadata(0.0, PixelShaderConstantCallback(0)));
        #endregion
    }
}
