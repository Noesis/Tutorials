using System;
using System.Runtime.InteropServices;
using Noesis;

namespace VideoEffect
{
    public class ChromaticAberrationEffect : ShaderEffect
    {
        private static NoesisShader Shader;

        public ChromaticAberrationEffect()
        {
            if (Shader == null) Shader = CreateShader();

            SetShader(Shader);
            SetConstantBuffer(_constants);
        }

        #region Amount
        public float Amount
        {
            get { return (float)GetValue(AmountProperty); }
            set { SetValue(AmountProperty, value); }
        }

        public static readonly DependencyProperty AmountProperty = DependencyProperty.Register(
            "Amount", typeof(float), typeof(ChromaticAberrationEffect),
            new PropertyMetadata(0.0f, OnAmountChanged));

        private static void OnAmountChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            ChromaticAberrationEffect this_ = (ChromaticAberrationEffect)d;
            this_._constants.amount = (float)e.NewValue;
            this_.InvalidateConstantBuffer();
        }
        #endregion

        [StructLayout(LayoutKind.Sequential)]
        private class Constants
        {
            public float amount = 0.0f;
        }

        private Constants _constants = new Constants();
    }
}
