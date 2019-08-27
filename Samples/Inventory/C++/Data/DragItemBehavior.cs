using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Interactivity;
using System.Windows.Media;

namespace Inventory
{
    class DragItemBehavior : Behavior<FrameworkElement>
    {
        public Point DragStartOffset
        {
            get { return (Point)GetValue(DragStartOffsetProperty); }
            set { SetValue(DragStartOffsetProperty, value); }
        }

        public static readonly DependencyProperty DragStartOffsetProperty = DependencyProperty.Register(
            "DragStartOffset", typeof(Point), typeof(DragItemBehavior),
            new PropertyMetadata(new Point(0, 0)));

        public ICommand StartDragCommand
        {
            get { return (ICommand)GetValue(StartDragCommandProperty); }
            set { SetValue(StartDragCommandProperty, value); }
        }

        public static readonly DependencyProperty StartDragCommandProperty = DependencyProperty.Register(
            "StartDragCommand", typeof(ICommand), typeof(DragItemBehavior),
            new PropertyMetadata(null));

        public ICommand EndDragCommand
        {
            get { return (ICommand)GetValue(EndDragCommandProperty); }
            set { SetValue(EndDragCommandProperty, value); }
        }

        public static readonly DependencyProperty EndDragCommandProperty = DependencyProperty.Register(
            "EndDragCommand", typeof(ICommand), typeof(DragItemBehavior),
            new PropertyMetadata(null));

        protected override void OnAttached()
        {
            base.OnAttached();

            this.AssociatedObject.GiveFeedback += OnGiveFeedback;
            this.AssociatedObject.PreviewMouseLeftButtonDown += OnMouseDown;
            this.AssociatedObject.PreviewMouseLeftButtonUp += OnMouseUp;
            this.AssociatedObject.PreviewMouseMove += OnMouseMove;
        }

        private void OnGiveFeedback(object sender, GiveFeedbackEventArgs e)
        {
            e.UseDefaultCursors = false;
            e.Handled = true;
        }

        protected override void OnDetaching()
        {
            this.AssociatedObject.GiveFeedback -= OnGiveFeedback;
            this.AssociatedObject.PreviewMouseLeftButtonDown -= OnMouseDown;
            this.AssociatedObject.PreviewMouseLeftButtonUp -= OnMouseUp;
            this.AssociatedObject.PreviewMouseMove -= OnMouseMove;

            base.OnDetaching();
        }

        private void OnMouseDown(object sender, MouseButtonEventArgs e)
        {
            _mouseClicked = true;
        }

        private void OnMouseUp(object sender, MouseButtonEventArgs e)
        {
            _mouseClicked = false;
        }

        private void OnMouseMove(object sender, MouseEventArgs e)
        {
            if (!_mouseClicked)
            {
                return;
            }

            _mouseClicked = false;

            object item = this.AssociatedObject.DataContext;
            if (item != null)
            {
                if (StartDragCommand != null && StartDragCommand.CanExecute(item))
                {
                    DragStartOffset = e.GetPosition(this.AssociatedObject);

                    StartDragCommand.Execute(item);

                    DragDropEffects effects = DragDrop.DoDragDrop(this.AssociatedObject, item, DragDropEffects.Move);

                    bool dragSuccess = effects != DragDropEffects.None;
                    if (EndDragCommand != null && EndDragCommand.CanExecute(dragSuccess))
                    {
                        EndDragCommand.Execute(dragSuccess);
                    }
                }
            }
        }

        private bool _mouseClicked = false;
    }
}
