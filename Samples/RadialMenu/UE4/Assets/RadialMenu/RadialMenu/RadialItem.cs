using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Shapes;

namespace RadialMenu
{
    /// <summary>
    /// Panel to display items in a radial/arc.
    /// </summary>
    public class RadialItem : Decorator
    {
        #region Dependency Properties
        /// <summary>
        /// The center X coordinate of the circle from which this element is positioned
        /// </summary>
        public double CenterX
        {
            get { return (double)GetValue(CenterXProperty); }
            set { SetValue(CenterXProperty, value); }
        }

        public static readonly DependencyProperty CenterXProperty = DependencyProperty.Register(
            "CenterX", typeof(double), typeof(RadialItem), new FrameworkPropertyMetadata(0.0,
                FrameworkPropertyMetadataOptions.AffectsArrange));

        /// <summary>
        /// The center Y coordinate of the circle from which this element is positioned
        /// </summary>
        public double CenterY
        {
            get { return (double)GetValue(CenterYProperty); }
            set { SetValue(CenterYProperty, value); }
        }

        public static readonly DependencyProperty CenterYProperty = DependencyProperty.Register(
            "CenterY", typeof(double), typeof(RadialItem), new FrameworkPropertyMetadata(0.0,
                FrameworkPropertyMetadataOptions.AffectsArrange));

        /// <summary>
        /// The radius where this element is positioned
        /// </summary>
        public double Radius
        {
            get { return (double)GetValue(RadiusProperty); }
            set { SetValue(RadiusProperty, value); }
        }

        public static readonly DependencyProperty RadiusProperty = DependencyProperty.Register(
            "Radius", typeof(double), typeof(RadialItem), new FrameworkPropertyMetadata(0.0,
                FrameworkPropertyMetadataOptions.AffectsArrange));

        /// <summary>
        /// The distance to translate this element out from the center
        /// </summary>
        public double Offset
        {
            get { return (double)GetValue(OffsetProperty); }
            set { SetValue(OffsetProperty, value); }
        }

        public static readonly DependencyProperty OffsetProperty = DependencyProperty.Register(
            "Offset", typeof(double), typeof(RadialItem), new FrameworkPropertyMetadata(0.0,
                FrameworkPropertyMetadataOptions.AffectsArrange));

        /// <summary>
        /// The start angle from the Y axis vector of this element in degrees
        /// </summary>
        public double AngleStart
        {
            get { return (double)GetValue(AngleStartProperty); }
            set { SetValue(AngleStartProperty, value); }
        }

        public static readonly DependencyProperty AngleStartProperty = DependencyProperty.Register(
            "AngleStart", typeof(double), typeof(RadialItem), new FrameworkPropertyMetadata(0.0,
                FrameworkPropertyMetadataOptions.AffectsArrange));

        /// <summary>
        /// The angle delta from the Y axis vector of this element in degrees
        /// </summary>
        public double AngleDelta
        {
            get { return (double)GetValue(AngleDeltaProperty); }
            set { SetValue(AngleDeltaProperty, value); }
        }

        public static readonly DependencyProperty AngleDeltaProperty = DependencyProperty.Register(
            "AngleDelta", typeof(double), typeof(RadialItem), new FrameworkPropertyMetadata(0.0,
                FrameworkPropertyMetadataOptions.AffectsArrange));

        #endregion

        static RadialItem()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(RadialItem), new FrameworkPropertyMetadata(typeof(RadialItem)));
        }

        protected override Size ArrangeOverride(Size arrangeSize)
        {
            UIElement child = Child;
            if (child != null)
            {
                Point center = new Point(CenterX, CenterY);
                Point point = RadialPoint(center, AngleStart + AngleDelta * 0.5, Radius);

                var halfChildWidth = child.DesiredSize.Width / 2;
                var halfChildHeight = child.DesiredSize.Height / 2;

                var p0 = new Point(point.X - halfChildWidth, point.Y - halfChildHeight);
                var p1 = new Point(point.X + halfChildWidth, point.Y + halfChildHeight);
                var childRect = new Rect(p0, p1);

                child.Arrange(childRect);
            }

            return arrangeSize;
        }

        private static Point RadialPoint(Point center, double angle, double radius)
        {
            // Converts to radians
            double radiansAngle = (angle - 90) * Math.PI / 180.0;
            double x = radius * Math.Cos(radiansAngle);
            double y = radius * Math.Sin(radiansAngle);
            return new Point(center.X + x, center.Y + y);
        }
    }
}
