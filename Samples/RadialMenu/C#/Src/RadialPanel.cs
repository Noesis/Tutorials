#if NOESIS
using Noesis;
using System;
#else
using System;
using System.Windows;
using System.Windows.Controls;
#endif

namespace RadialMenu
{
    /// <summary>
    /// Panel to display items in a radial/arc.
    /// </summary>
    public class RadialPanel : Panel
    {
        #region Dependency Properties
        /// <summary>
        /// Gets or sets the arc angle covered by the children. A value between 0 and 360 degrees
        /// </summary>
        public float Angle
        {
            get { return (float)GetValue(AngleProperty); }
            set { SetValue(AngleProperty, value); }
        }

        public static readonly DependencyProperty AngleProperty = DependencyProperty.Register(
            "Angle", typeof(float), typeof(RadialPanel), new FrameworkPropertyMetadata(360.0f,
                FrameworkPropertyMetadataOptions.AffectsArrange));

        /// <summary>
        /// Gets or sets the angle offset where children start to be positioned
        /// </summary>
        public float AngleOffset
        {
            get { return (float)GetValue(AngleOffsetProperty); }
            set { SetValue(AngleOffsetProperty, value); }
        }

        public static readonly DependencyProperty AngleOffsetProperty = DependencyProperty.Register(
            "AngleOffset", typeof(float), typeof(RadialPanel), new FrameworkPropertyMetadata(0.0f,
                FrameworkPropertyMetadataOptions.AffectsArrange));

        /// <summary>
        /// Gets or sets the arc angle covered by the children. A value between 0 and 360 degrees
        /// </summary>
        public bool IsClockwise
        {
            get { return (bool)GetValue(IsClockwiseProperty); }
            set { SetValue(IsClockwiseProperty, value); }
        }

        public static readonly DependencyProperty IsClockwiseProperty = DependencyProperty.Register(
            "IsClockwise", typeof(bool), typeof(RadialPanel), new FrameworkPropertyMetadata(true,
                FrameworkPropertyMetadataOptions.AffectsArrange));
        #endregion

        #region Attached Properties
        public static float GetCenterX(UIElement obj) { return (float)obj.GetValue(CenterXProperty); }
        public static void SetCenterX(UIElement obj, float value) { obj.SetValue(CenterXProperty, value); }

        public static readonly DependencyProperty CenterXProperty = DependencyProperty.RegisterAttached(
            "CenterX", typeof(float), typeof(RadialPanel), new PropertyMetadata(0.0f));

        public static float GetCenterY(UIElement obj) { return (float)obj.GetValue(CenterYProperty); }
        public static void SetCenterY(UIElement obj, float value) { obj.SetValue(CenterYProperty, value); }

        public static readonly DependencyProperty CenterYProperty = DependencyProperty.RegisterAttached(
            "CenterY", typeof(float), typeof(RadialPanel), new PropertyMetadata(0.0f));

        public static float GetAngleStart(UIElement obj) { return (float)obj.GetValue(AngleStartProperty); }
        public static void SetAngleStart(UIElement obj, float value) { obj.SetValue(AngleStartProperty, value); }

        public static readonly DependencyProperty AngleStartProperty = DependencyProperty.RegisterAttached(
            "AngleStart", typeof(float), typeof(RadialPanel), new PropertyMetadata(0.0f));

        public static float GetAngleDelta(UIElement obj) { return (float)obj.GetValue(AngleDeltaProperty); }
        public static void SetAngleDelta(UIElement obj, float value) { obj.SetValue(AngleDeltaProperty, value); }

        public static readonly DependencyProperty AngleDeltaProperty = DependencyProperty.RegisterAttached(
            "AngleDelta", typeof(float), typeof(RadialPanel), new PropertyMetadata(0.0f));
        #endregion

        protected override Size MeasureOverride(Size availableSize)
        {
            Size desiredSize = new Size(0, 0);
            foreach (UIElement child in Children)
            {
                child.Measure(availableSize);

                if (desiredSize.Width < child.DesiredSize.Width) desiredSize.Width = child.DesiredSize.Width;
                if (desiredSize.Height < child.DesiredSize.Height) desiredSize.Height = child.DesiredSize.Height;
            }

            return desiredSize;
        }

        protected override Size ArrangeOverride(Size finalSize)
        {
            float diameter = (float)Math.Min(finalSize.Width, finalSize.Height);
            float radius = diameter * 0.5f;

            Point center = new Point(radius, radius);
            Size renderSize = new Size(diameter, diameter);
            Rect childRect = new Rect(renderSize);

            int childCount = Children.Count;
            float childAngleStart = AngleOffset;
            float childAngleDelta = Angle / childCount;

            foreach (UIElement child in Children)
            {
                child.Arrange(childRect);

                SetCenterX(child, (float)center.X);
                SetCenterY(child, (float)center.Y);
                SetAngleStart(child, childAngleStart);
                SetAngleDelta(child, childAngleDelta);

                childAngleStart += childAngleDelta;
            }

            return renderSize;
        }
    }
}
