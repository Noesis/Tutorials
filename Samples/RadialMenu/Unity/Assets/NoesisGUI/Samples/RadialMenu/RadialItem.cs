#if UNITY_5_3_OR_NEWER
#define NOESIS
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
    public class RadialItem : Decorator
    {
        #region Dependency Properties
        /// <summary>
        /// The center X coordinate of the circle from which this element is positioned
        /// </summary>
        public float CenterX
        {
            get { return (float)GetValue(CenterXProperty); }
            set { SetValue(CenterXProperty, value); }
        }

        public static readonly DependencyProperty CenterXProperty = DependencyProperty.Register(
            "CenterX", typeof(float), typeof(RadialItem), new FrameworkPropertyMetadata(0.0f,
                FrameworkPropertyMetadataOptions.AffectsArrange));

        /// <summary>
        /// The center Y coordinate of the circle from which this element is positioned
        /// </summary>
        public float CenterY
        {
            get { return (float)GetValue(CenterYProperty); }
            set { SetValue(CenterYProperty, value); }
        }

        public static readonly DependencyProperty CenterYProperty = DependencyProperty.Register(
            "CenterY", typeof(float), typeof(RadialItem), new FrameworkPropertyMetadata(0.0f,
                FrameworkPropertyMetadataOptions.AffectsArrange));

        /// <summary>
        /// The radius where this element is positioned
        /// </summary>
        public float Radius
        {
            get { return (float)GetValue(RadiusProperty); }
            set { SetValue(RadiusProperty, value); }
        }

        public static readonly DependencyProperty RadiusProperty = DependencyProperty.Register(
            "Radius", typeof(float), typeof(RadialItem), new FrameworkPropertyMetadata(0.0f,
                FrameworkPropertyMetadataOptions.AffectsArrange));

        /// <summary>
        /// The distance to translate this element out from the center
        /// </summary>
        public float Offset
        {
            get { return (float)GetValue(OffsetProperty); }
            set { SetValue(OffsetProperty, value); }
        }

        public static readonly DependencyProperty OffsetProperty = DependencyProperty.Register(
            "Offset", typeof(float), typeof(RadialItem), new FrameworkPropertyMetadata(0.0f,
                FrameworkPropertyMetadataOptions.AffectsArrange));

        /// <summary>
        /// The start angle from the Y axis vector of this element in degrees
        /// </summary>
        public float AngleStart
        {
            get { return (float)GetValue(AngleStartProperty); }
            set { SetValue(AngleStartProperty, value); }
        }

        public static readonly DependencyProperty AngleStartProperty = DependencyProperty.Register(
            "AngleStart", typeof(float), typeof(RadialItem), new FrameworkPropertyMetadata(0.0f,
                FrameworkPropertyMetadataOptions.AffectsArrange));

        /// <summary>
        /// The angle delta from the Y axis vector of this element in degrees
        /// </summary>
        public float AngleDelta
        {
            get { return (float)GetValue(AngleDeltaProperty); }
            set { SetValue(AngleDeltaProperty, value); }
        }

        public static readonly DependencyProperty AngleDeltaProperty = DependencyProperty.Register(
            "AngleDelta", typeof(float), typeof(RadialItem), new FrameworkPropertyMetadata(0.0f,
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
                Point point = RadialPoint(center, AngleStart + AngleDelta * 0.5f, Radius);

                var halfChildWidth = child.DesiredSize.Width / 2;
                var halfChildHeight = child.DesiredSize.Height / 2;

                var p0 = new Point(point.X - halfChildWidth, point.Y - halfChildHeight);
                var p1 = new Point(point.X + halfChildWidth, point.Y + halfChildHeight);
                var childRect = new Rect(p0, p1);

                child.Arrange(childRect);
            }

            return arrangeSize;
        }

        private static Point RadialPoint(Point center, float angle, float radius)
        {
            // Converts to radians
            float radiansAngle = (angle - 90.0f) * (float)Math.PI / 180.0f;
            float x = radius * (float)Math.Cos(radiansAngle);
            float y = radius * (float)Math.Sin(radiansAngle);
            return new Point(center.X + x, center.Y + y);
        }
    }
}
