#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
using NoesisApp;
using System.Windows.Input;
#else
using System;
using System.Windows;
using System.Windows.Input;
using Microsoft.Xaml.Behaviors;
#endif

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

            FrameworkElement element = AssociatedObject;
            if (element != null)
            {
                element.GiveFeedback += OnGiveFeedback;
                element.PreviewMouseLeftButtonDown += OnMouseDown;
                element.PreviewMouseLeftButtonUp += OnMouseUp;
                element.PreviewMouseMove += OnMouseMove;
            }
        }

        protected override void OnDetaching()
        {
            FrameworkElement element = AssociatedObject;
            if (element != null)
            {
                element.GiveFeedback -= OnGiveFeedback;
                element.PreviewMouseLeftButtonDown -= OnMouseDown;
                element.PreviewMouseLeftButtonUp -= OnMouseUp;
                element.PreviewMouseMove -= OnMouseMove;
            }

            base.OnDetaching();
        }

        private void OnGiveFeedback(object sender, GiveFeedbackEventArgs e)
        {
            e.UseDefaultCursors = false;
            e.Handled = true;
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

#if NOESIS
                    DragDrop.DoDragDrop(this.AssociatedObject, item, DragDropEffects.Move,
                        (source, data, target, dropPoint, effects) =>
                        {
                            bool dragSuccess = effects != DragDropEffects.None;
                            if (EndDragCommand != null && EndDragCommand.CanExecute(dragSuccess))
                            {
                                EndDragCommand.Execute(dragSuccess);
                            }
                        });
#else
                    DragDropEffects effects = DragDrop.DoDragDrop(this.AssociatedObject, item, DragDropEffects.Move);

                    bool dragSuccess = effects != DragDropEffects.None;
                    if (EndDragCommand != null && EndDragCommand.CanExecute(dragSuccess))
                    {
                        EndDragCommand.Execute(dragSuccess);
                    }
#endif
                }
            }
        }

        private bool _mouseClicked = false;
    }
}
