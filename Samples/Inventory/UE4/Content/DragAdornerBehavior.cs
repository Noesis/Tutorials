using System;
using System.Windows;
using System.Windows.Interactivity;
using System.Windows.Media;

namespace Inventory
{
    class DragAdornerBehavior : Behavior<FrameworkElement>
    {
        public Point DragStartOffset
        {
            get { return (Point)GetValue(DragStartOffsetProperty); }
            set { SetValue(DragStartOffsetProperty, value); }
        }

        public static readonly DependencyProperty DragStartOffsetProperty = DependencyProperty.Register(
            "DragStartOffset", typeof(Point), typeof(DragAdornerBehavior),
            new PropertyMetadata(new Point(0, 0)));

        public double DraggedItemX
        {
            get { return (double)GetValue(DraggedItemXProperty); }
            private set { SetValue(DraggedItemXPropertyKey, value); }
        }

        private static readonly DependencyPropertyKey DraggedItemXPropertyKey =
            DependencyProperty.RegisterReadOnly("DraggedItemX",
                typeof(double), typeof(DragAdornerBehavior), new PropertyMetadata(0.0));

        public static readonly DependencyProperty DraggedItemXProperty =
            DraggedItemXPropertyKey.DependencyProperty;

        public double DraggedItemY
        {
            get { return (double)GetValue(DraggedItemYProperty); }
            private set { SetValue(DraggedItemYPropertyKey, value); }
        }

        private static readonly DependencyPropertyKey DraggedItemYPropertyKey =
            DependencyProperty.RegisterReadOnly("DraggedItemY",
                typeof(double), typeof(DragAdornerBehavior), new PropertyMetadata(0.0));

        public static readonly DependencyProperty DraggedItemYProperty =
            DraggedItemYPropertyKey.DependencyProperty;

        protected override void OnAttached()
        {
            base.OnAttached();

            this.AssociatedObject.AllowDrop = true;
            this.AssociatedObject.DragOver += OnDragOver;
            this.AssociatedObject.Drop += OnDrop;
        }

        protected override void OnDetaching()
        {
            this.AssociatedObject.AllowDrop = false;
            this.AssociatedObject.DragOver -= OnDragOver;
            this.AssociatedObject.Drop -= OnDrop;

            base.OnDetaching();
        }

        private void OnDragOver(object sender, DragEventArgs e)
        {
            Point position = e.GetPosition(this.AssociatedObject);
            DraggedItemX = position.X - DragStartOffset.X;
            DraggedItemY = position.Y - DragStartOffset.Y;
        }

        private void OnDrop(object sender, DragEventArgs e)
        {
            e.Effects = DragDropEffects.None;
        }
    }
}
