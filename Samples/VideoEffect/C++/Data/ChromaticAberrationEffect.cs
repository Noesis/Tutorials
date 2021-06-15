using System;
using System.Windows;
using System.Windows.Media.Effects;

namespace VideoEffect
{
    public class ChromaticAberrationEffect : ShaderEffect
    {
        private static PixelShader _pixelShader = new PixelShader();

        public ChromaticAberrationEffect()
        {
            PixelShader = _pixelShader;
        }

        public double Amount
        {
            get { return (double)GetValue(AmountProperty); }
            set { SetValue(AmountProperty, value); }
        }

        public static readonly DependencyProperty AmountProperty = DependencyProperty.Register(
            "Amount", typeof(double), typeof(ChromaticAberrationEffect),
            new PropertyMetadata(0.0, PixelShaderConstantCallback(0)));
    }
}
