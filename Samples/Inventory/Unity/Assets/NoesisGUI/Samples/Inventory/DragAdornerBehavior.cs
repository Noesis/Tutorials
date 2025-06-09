#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
using NoesisApp;
#else
using System;
using System.Windows;
using Microsoft.Xaml.Behaviors;
#endif

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
            private set { SetValue(DraggedItemXProperty, value); }
        }

        private static readonly DependencyProperty DraggedItemXProperty =
            DependencyProperty.Register("DraggedItemX",
                typeof(double), typeof(DragAdornerBehavior), new PropertyMetadata(0.0));

        public double DraggedItemY
        {
            get { return (double)GetValue(DraggedItemYProperty); }
            private set { SetValue(DraggedItemYProperty, value); }
        }

        private static readonly DependencyProperty DraggedItemYProperty =
            DependencyProperty.Register("DraggedItemY",
                typeof(double), typeof(DragAdornerBehavior), new PropertyMetadata(0.0));

        protected override void OnAttached()
        {
            base.OnAttached();

            FrameworkElement element = AssociatedObject;
            if (element != null)
            {
                element.AllowDrop = true;
                element.DragOver += OnDragOver;
                element.Drop += OnDrop;
            }
        }

        protected override void OnDetaching()
        {
            FrameworkElement element = AssociatedObject;
            if (element != null)
            {
                element.AllowDrop = false;
                element.DragOver -= OnDragOver;
                element.Drop -= OnDrop;
            }

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
