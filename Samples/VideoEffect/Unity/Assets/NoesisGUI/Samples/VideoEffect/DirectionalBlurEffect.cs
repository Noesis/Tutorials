using System;
using System.Runtime.InteropServices;
using Noesis;

namespace VideoEffect
{
    public class DirectionalBlurEffect : ShaderEffect
    {
        private static NoesisShader Shader;

        public DirectionalBlurEffect()
        {
            if (Shader == null) Shader = CreateShader();

            SetShader(Shader);
            SetConstantBuffer(_constants);
        }

        #region Angle
        public float Angle
        {
            get { return (float)GetValue(AngleProperty); }
            set { SetValue(AngleProperty, value); }
        }

        public static readonly DependencyProperty AngleProperty = DependencyProperty.Register(
            "Angle", typeof(float), typeof(DirectionalBlurEffect),
            new PropertyMetadata(0.0f, OnAngleChanged));

        private static void OnAngleChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            DirectionalBlurEffect this_ = (DirectionalBlurEffect)d;
            this_._constants.dirX = UnityEngine.Mathf.Cos((float)e.NewValue * UnityEngine.Mathf.Deg2Rad);
            this_._constants.dirY = UnityEngine.Mathf.Sin((float)e.NewValue * UnityEngine.Mathf.Deg2Rad);
            this_.InvalidateConstantBuffer();
        }
        #endregion

        #region Radius
        public float Radius
        {
            get { return (float)GetValue(RadiusProperty); }
            set { SetValue(RadiusProperty, value); }
        }

        public static readonly DependencyProperty RadiusProperty = DependencyProperty.Register(
            "Radius", typeof(float), typeof(DirectionalBlurEffect),
            new PropertyMetadata(0.0f, OnRadiusChanged));

        private static void OnRadiusChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            DirectionalBlurEffect this_ = (DirectionalBlurEffect)d;
            this_._constants.scale = (float)e.NewValue / 17.5f;
            this_.InvalidateConstantBuffer();
        }
        #endregion

        [StructLayout(LayoutKind.Sequential)]
        private class Constants
        {
            public float dirX = 1.0f;
            public float dirY = 0.0f;
            public float scale = 0.0f;
        }

        private Constants _constants = new Constants();
    }
}
