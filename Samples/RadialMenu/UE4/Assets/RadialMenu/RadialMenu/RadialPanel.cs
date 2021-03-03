using System;
using System.Windows;
using System.Windows.Controls;

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
        public double Angle
        {
            get { return (double)GetValue(AngleProperty); }
            set { SetValue(AngleProperty, value); }
        }

        public static readonly DependencyProperty AngleProperty = DependencyProperty.Register(
            "Angle", typeof(double), typeof(RadialPanel), new FrameworkPropertyMetadata(360.0,
                FrameworkPropertyMetadataOptions.AffectsArrange));

        /// <summary>
        /// Gets or sets the angle offset where children start to be positioned
        /// </summary>
        public double AngleOffset
        {
            get { return (double)GetValue(AngleOffsetProperty); }
            set { SetValue(AngleOffsetProperty, value); }
        }

        public static readonly DependencyProperty AngleOffsetProperty = DependencyProperty.Register(
            "AngleOffset", typeof(double), typeof(RadialPanel), new FrameworkPropertyMetadata(0.0,
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
        public static double GetCenterX(UIElement obj) { return (double)obj.GetValue(CenterXProperty); }
        public static void SetCenterX(UIElement obj, double value) { obj.SetValue(CenterXProperty, value); }

        public static readonly DependencyProperty CenterXProperty = DependencyProperty.RegisterAttached(
            "CenterX", typeof(double), typeof(RadialPanel), new PropertyMetadata(0.0));

        public static double GetCenterY(UIElement obj) { return (double)obj.GetValue(CenterYProperty); }
        public static void SetCenterY(UIElement obj, double value) { obj.SetValue(CenterYProperty, value); }

        public static readonly DependencyProperty CenterYProperty = DependencyProperty.RegisterAttached(
            "CenterY", typeof(double), typeof(RadialPanel), new PropertyMetadata(0.0));

        public static double GetAngleStart(UIElement obj) { return (double)obj.GetValue(AngleStartProperty); }
        public static void SetAngleStart(UIElement obj, double value) { obj.SetValue(AngleStartProperty, value); }

        public static readonly DependencyProperty AngleStartProperty = DependencyProperty.RegisterAttached(
            "AngleStart", typeof(double), typeof(RadialPanel), new PropertyMetadata(0.0));

        public static double GetAngleDelta(UIElement obj) { return (double)obj.GetValue(AngleDeltaProperty); }
        public static void SetAngleDelta(UIElement obj, double value) { obj.SetValue(AngleDeltaProperty, value); }

        public static readonly DependencyProperty AngleDeltaProperty = DependencyProperty.RegisterAttached(
            "AngleDelta", typeof(double), typeof(RadialPanel), new PropertyMetadata(0.0));
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
            var diameter = Math.Min(finalSize.Width, finalSize.Height);
            var radius = diameter * 0.5;

            Point center = new Point(radius, radius);
            Size renderSize = new Size(diameter, diameter);
            Rect childRect = new Rect(renderSize);

            int childCount = Children.Count;
            double childAngleStart = AngleOffset;
            double childAngleDelta = Angle / childCount;

            foreach (UIElement child in Children)
            {
                child.Arrange(childRect);

                SetCenterX(child, center.X);
                SetCenterY(child, center.Y);
                SetAngleStart(child, childAngleStart);
                SetAngleDelta(child, childAngleDelta);

                childAngleStart += childAngleDelta;
            }

            return renderSize;
        }
    }
}
