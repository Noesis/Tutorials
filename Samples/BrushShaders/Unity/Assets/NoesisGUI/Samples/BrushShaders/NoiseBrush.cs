using System;
using System.Runtime.InteropServices;
using Noesis;

namespace BrushShaders
{
    public class NoiseBrush : BrushShader
    {
        private static NoesisShader Shader;

        public NoiseBrush()
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
            "Color", typeof(Color), typeof(NoiseBrush), new PropertyMetadata(Colors.White, OnColorChanged));

        private static void OnColorChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            NoiseBrush brush = (NoiseBrush)d;
            brush._constants.color = (Color)e.NewValue;
            brush.InvalidateConstantBuffer();
        }
        #endregion

        #region ScaleX
        public float ScaleX
        {
            get { return (float)GetValue(ScaleXProperty); }
            set { SetValue(ScaleXProperty, value); }
        }

        public static readonly DependencyProperty ScaleXProperty = DependencyProperty.Register(
            "ScaleX", typeof(float), typeof(NoiseBrush),
            new PropertyMetadata(0.0f, OnScaleXChanged));

        private static void OnScaleXChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            NoiseBrush brush = (NoiseBrush)d;
            brush._constants.scaleX = (float)e.NewValue;
            brush.InvalidateConstantBuffer();
        }
        #endregion

        #region ScaleY
        public float ScaleY
        {
            get { return (float)GetValue(ScaleYProperty); }
            set { SetValue(ScaleYProperty, value); }
        }

        public static readonly DependencyProperty ScaleYProperty = DependencyProperty.Register(
            "ScaleY", typeof(float), typeof(NoiseBrush),
            new PropertyMetadata(0.0f, OnScaleYChanged));

        private static void OnScaleYChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            NoiseBrush brush = (NoiseBrush)d;
            brush._constants.scaleY = (float)e.NewValue;
            brush.InvalidateConstantBuffer();
        }
        #endregion

        #region Time
        public float Time
        {
            get { return (float)GetValue(TimeProperty); }
            set { SetValue(TimeProperty, value); }
        }

        public static readonly DependencyProperty TimeProperty = DependencyProperty.Register(
            "Time", typeof(float), typeof(NoiseBrush), new PropertyMetadata(0.0f, OnTimeChanged));

        private static void OnTimeChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            NoiseBrush brush = (NoiseBrush)d;
            brush._constants.time = (float)e.NewValue;
            brush.InvalidateConstantBuffer();
        }
        #endregion

        #region Seed
        public float Seed
        {
            get { return (float)GetValue(SeedProperty); }
            set { SetValue(SeedProperty, value); }
        }

        public static readonly DependencyProperty SeedProperty = DependencyProperty.Register(
            "Seed", typeof(float), typeof(NoiseBrush), new PropertyMetadata(0.0f, OnSeedChanged));

        private static void OnSeedChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            if (d is NoiseBrush brush)
            {
                brush._constants.seed = (float)e.NewValue;
                brush.InvalidateConstantBuffer();
            }
        }
        #endregion

        [StructLayout(LayoutKind.Sequential)]
        private class Constants
        {
            public Color color = Colors.White;
            public float scaleX = 1.0f;
            public float scaleY = 1.0f;
            public float time = 0.0f;
            public float seed = 0.0f;
        }

        private Constants _constants = new Constants();
    }
}
