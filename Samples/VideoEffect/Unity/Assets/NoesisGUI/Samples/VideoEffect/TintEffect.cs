using System;
using System.Runtime.InteropServices;
using Noesis;

namespace VideoEffect
{
    public class TintEffect : ShaderEffect
    {
        private static NoesisShader Shader;

        public TintEffect()
        {
            if (Shader == null) Shader = CreateShader();

            SetShader(Shader);
            SetConstantBuffer(_constants);
        }

        #region Color
        public Color Color
        {
            get { return (Color)GetValue(ColorProperty); }
            set { SetValue(ColorProperty, value); }
        }

        public static readonly DependencyProperty ColorProperty = DependencyProperty.Register(
            "Color", typeof(Color), typeof(TintEffect),
            new PropertyMetadata(Colors.Blue, OnColorChanged));

        private static void OnColorChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            TintEffect this_ = (TintEffect)d;
            this_._constants.color = (Color)e.NewValue;
            this_.InvalidateConstantBuffer();
        }
        #endregion

        [StructLayout(LayoutKind.Sequential)]
        private class Constants
        {
            public Color color = Colors.Blue;
        }

        private Constants _constants = new Constants();
    }
}
