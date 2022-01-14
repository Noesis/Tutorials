using System;
using System.Runtime.InteropServices;
using Noesis;

namespace VideoEffect
{
    public class PixelateEffect : ShaderEffect
    {
        private static NoesisShader Shader;

        public PixelateEffect()
        {
            if (Shader == null) Shader = CreateShader();

            SetShader(Shader);
            SetConstantBuffer(_constants);
        }

        #region Size
        public float Size
        {
            get { return (float)GetValue(SizeProperty); }
            set { SetValue(SizeProperty, value); }
        }

        public static readonly DependencyProperty SizeProperty = DependencyProperty.Register(
            "Size", typeof(float), typeof(PixelateEffect),
            new PropertyMetadata(5.0f, OnSizeChanged));

        private static void OnSizeChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            PixelateEffect this_ = (PixelateEffect)d;
            this_._constants.size = (float)e.NewValue;
            this_.InvalidateConstantBuffer();
        }
        #endregion

        [StructLayout(LayoutKind.Sequential)]
        private class Constants
        {
            public float size = 5.0f;
        }

        private Constants _constants = new Constants();
    }
}
