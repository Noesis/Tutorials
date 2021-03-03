#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
using System;
#else
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Media;
using System.Windows.Shapes;
#endif

namespace RadialMenu
{
    /// <summary>
    /// Panel to display items in a radial/arc.
    /// </summary>
    public class Arc : Decorator
    {
        #region Dependency Properties
        /// <summary>
        /// The center X coordinate of the circle from which this arc piece is cut
        /// </summary>
        public float CenterX
        {
            get { return (float)GetValue(CenterXProperty); }
            set { SetValue(CenterXProperty, value); }
        }

        public static readonly DependencyProperty CenterXProperty = DependencyProperty.Register(
            "CenterX", typeof(float), typeof(Arc), new FrameworkPropertyMetadata(0.0f, OnShapePropertyChanged));

        /// <summary>
        /// The center Y coordinate of the circle from which this arc piece is cut
        /// </summary>
        public float CenterY
        {
            get { return (float)GetValue(CenterYProperty); }
            set { SetValue(CenterYProperty, value); }
        }

        public static readonly DependencyProperty CenterYProperty = DependencyProperty.Register(
            "CenterY", typeof(float), typeof(Arc), new FrameworkPropertyMetadata(0.0f, OnShapePropertyChanged));

        /// <summary>
        /// The inner radius of this arc piece
        /// </summary>
        public float InnerRadius
        {
            get { return (float)GetValue(InnerRadiusProperty); }
            set { SetValue(InnerRadiusProperty, value); }
        }

        public static readonly DependencyProperty InnerRadiusProperty = DependencyProperty.Register(
            "InnerRadius", typeof(float), typeof(Arc), new FrameworkPropertyMetadata(0.0f, OnShapePropertyChanged));

        /// <summary>
        /// The outer radius of this arc piece
        /// </summary>
        public float OuterRadius
        {
            get { return (float)GetValue(OuterRadiusProperty); }
            set { SetValue(OuterRadiusProperty, value); }
        }

        public static readonly DependencyProperty OuterRadiusProperty = DependencyProperty.Register(
            "OuterRadius", typeof(float), typeof(Arc), new FrameworkPropertyMetadata(0.0f, OnShapePropertyChanged));

        /// <summary>
        /// The distance to translate this arc piece out from the center
        /// </summary>
        public float Offset
        {
            get { return (float)GetValue(OffsetProperty); }
            set { SetValue(OffsetProperty, value); }
        }

        public static readonly DependencyProperty OffsetProperty = DependencyProperty.Register(
            "Offset", typeof(float), typeof(Arc), new FrameworkPropertyMetadata(0.0f, OnShapePropertyChanged));

        /// <summary>
        /// The start angle from the Y axis vector of this arc piece in degrees
        /// </summary>
        public float AngleStart
        {
            get { return (float)GetValue(AngleStartProperty); }
            set { SetValue(AngleStartProperty, value); }
        }

        public static readonly DependencyProperty AngleStartProperty = DependencyProperty.Register(
            "AngleStart", typeof(float), typeof(Arc), new FrameworkPropertyMetadata(0.0f, OnShapePropertyChanged));

        /// <summary>
        /// The angle delta from the Y axis vector of this arc piece in degrees
        /// </summary>
        public float AngleDelta
        {
            get { return (float)GetValue(AngleDeltaProperty); }
            set { SetValue(AngleDeltaProperty, value); }
        }

        public static readonly DependencyProperty AngleDeltaProperty = DependencyProperty.Register(
            "AngleDelta", typeof(float), typeof(Arc), new FrameworkPropertyMetadata(0.0f, OnShapePropertyChanged));

        /// <summary>
        /// The padding around this arc piece
        /// </summary>
        public float Padding
        {
            get { return (float)GetValue(PaddingProperty); }
            set { SetValue(PaddingProperty, value); }
        }

        public static readonly DependencyProperty PaddingProperty = DependencyProperty.Register(
            "Padding", typeof(float), typeof(Arc), new FrameworkPropertyMetadata(0.0f, OnShapePropertyChanged));

        private static void OnShapePropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            ((Arc)d).InvalidateMeasure();
        }

        /// <summary>
        /// Brush that fills the arc
        /// </summary>
        public Brush Fill
        {
            get { return (Brush)GetValue(FillProperty); }
            set { SetValue(FillProperty, value); }
        }

        public static readonly DependencyProperty FillProperty = DependencyProperty.Register(
            "Fill", typeof(Brush), typeof(Arc), new PropertyMetadata(null));

        /// <summary>
        /// Brush used to stroke the arc
        /// </summary>
        public Brush Stroke
        {
            get { return (Brush)GetValue(StrokeProperty); }
            set { SetValue(StrokeProperty, value); }
        }

        public static readonly DependencyProperty StrokeProperty = DependencyProperty.Register(
            "Stroke", typeof(Brush), typeof(Arc), new PropertyMetadata(null));

        /// <summary>
        /// The thickness of the stroke applied to the arc
        /// </summary>
        public float StrokeThickness
        {
            get { return (float)GetValue(StrokeThicknessProperty); }
            set { SetValue(StrokeThicknessProperty, value); }
        }

        public static readonly DependencyProperty StrokeThicknessProperty = DependencyProperty.Register(
            "StrokeThickness", typeof(float), typeof(Arc), new PropertyMetadata(1.0f));
        #endregion

        static Arc()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(Arc), new FrameworkPropertyMetadata(typeof(Arc)));
        }

        protected override Size MeasureOverride(Size constraint)
        {
            BuildArcGeometry();

            return base.MeasureOverride(constraint);
        }

        private void EnsurePath()
        {
            if (Child == null)
            {
                Path path = new Path() { Data = new StreamGeometry { FillRule = FillRule.EvenOdd } };
                path.SetBinding(Shape.FillProperty, new Binding("Fill") { Source = this });
                path.SetBinding(Shape.StrokeProperty, new Binding("Stroke") { Source = this });
                path.SetBinding(Shape.StrokeThicknessProperty, new Binding("StrokeThickness") { Source = this });

                Child = path;
            }
        }

        private void BuildArcGeometry()
        {
            EnsurePath();

            StreamGeometry geometry = ((Path)Child).Data as StreamGeometry;

            using (StreamGeometryContext context = geometry.Open())
            {
                if (AngleDelta > 0 && Math.Abs(OuterRadius - InnerRadius) > float.Epsilon)
                {
                    float outerStartAngle = AngleStart;
                    float outerAngleDelta = AngleDelta;
                    float innerStartAngle = AngleStart;
                    float innerAngleDelta = AngleDelta;
                    Point center = new Point(CenterX, CenterY);
                    Size outerArcSize = new Size(OuterRadius, OuterRadius);
                    Size innerArcSize = new Size(InnerRadius, InnerRadius);

                    // If we have to draw a full-circle, we do it with two semi-circles, because 'ArcTo()' can
                    // not draw a full-circle
                    if (AngleDelta >= 360 && Padding <= 0)
                    {
                        Point outerTop = RadialPoint(center, outerStartAngle, OuterRadius + Offset);
                        Point outerBottom = RadialPoint(center, outerStartAngle + 180, OuterRadius + Offset);
                        Point innerTop = RadialPoint(center, innerStartAngle, InnerRadius + Offset);
                        Point innerBottom = RadialPoint(center, innerStartAngle + 180, InnerRadius + Offset);

                        context.BeginFigure(innerTop, true, true);
                        context.LineTo(outerTop, true, true);
                        context.ArcTo(outerBottom, outerArcSize, 0, false, SweepDirection.Clockwise, true, true);
                        context.ArcTo(outerTop, outerArcSize, 0, false, SweepDirection.Clockwise, true, true);
                        context.LineTo(innerTop, true, true);
                        context.ArcTo(innerBottom, innerArcSize, 0, false, SweepDirection.Counterclockwise, true, true);
                        context.ArcTo(innerTop, innerArcSize, 0, false, SweepDirection.Counterclockwise, true, true);
                    }
                    else
                    {
                        if (Padding > 0)
                        {
                            // Offsets the angle by the padding
                            float outerAngleVariation = (180.0f * (Padding / OuterRadius)) / (float)Math.PI;
                            float innerAngleVariation = (180.0f * (Padding / InnerRadius)) / (float)Math.PI;

                            outerStartAngle += outerAngleVariation;
                            outerAngleDelta -= outerAngleVariation * 2;
                            innerStartAngle += innerAngleVariation;
                            innerAngleDelta -= innerAngleVariation * 2;
                        }

                        Point outerStart = RadialPoint(center, outerStartAngle, OuterRadius + Offset);
                        Point outerEnd = RadialPoint(center, outerStartAngle + outerAngleDelta, OuterRadius + Offset);
                        Point innerStart = RadialPoint(center, innerStartAngle, InnerRadius + Offset);
                        Point innerEnd = RadialPoint(center, innerStartAngle + innerAngleDelta, InnerRadius + Offset);

                        bool largeArcOuter = outerAngleDelta > 180.0;
                        bool largeArcInner = innerAngleDelta > 180.0;

                        context.BeginFigure(innerStart, true, true);
                        context.LineTo(outerStart, true, true);
                        context.ArcTo(outerEnd, outerArcSize, 0, largeArcOuter, SweepDirection.Clockwise, true, true);
                        context.LineTo(innerEnd, true, true);
                        context.ArcTo(innerStart, innerArcSize, 0, largeArcInner, SweepDirection.Counterclockwise, true, true);
                    }
                }
            }
        }

        private static Point RadialPoint(Point center, float angle, float radius)
        {
            // Converts to radians
            float radiansAngle = (angle - 90) * (float)Math.PI / 180.0f;
            float x = radius * (float)Math.Cos(radiansAngle);
            float y = radius * (float)Math.Sin(radiansAngle);
            return new Point(x + center.X, y + center.Y);
        }
    }
}
