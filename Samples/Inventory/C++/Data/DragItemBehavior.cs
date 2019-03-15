using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Interactivity;
using System.Windows.Media;

namespace Inventory
{
    class DragItemBehavior : Behavior<ContentControl>
    {
        protected override void OnAttached()
        {
            base.OnAttached();

            this.AssociatedObject.GiveFeedback += OnGiveFeedback;
            this.AssociatedObject.PreviewMouseLeftButtonDown += OnMouseDown;
            this.AssociatedObject.PreviewMouseLeftButtonUp += OnMouseUp;
            this.AssociatedObject.PreviewMouseMove += OnMouseMove;
            this.AssociatedObject.PreviewKeyDown += OnKeyDown;
        }

        private void OnKeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Space || e.Key == Key.Enter)
            {
                Slot slot = (Slot)this.AssociatedObject.Content;
                ViewModel.Instance.SelectSlot(slot);
            }
            else if (e.Key == Key.Escape)
            {
                ViewModel.Instance.SelectSlot(null);
            }
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
            if (_mouseClicked)
            {
                Slot slot = (Slot)this.AssociatedObject.Content;
                if (slot != null && slot.Item != null)
                {
                    ViewModel.Instance.StartDragging(slot, e.GetPosition(null));
                    DragDropEffects effects = DragDrop.DoDragDrop(this.AssociatedObject, slot, DragDropEffects.Move);
                    ViewModel.Instance.EndDragging(effects == DragDropEffects.None);
                }

                _mouseClicked = false;
            }
        }

        private bool _mouseClicked = false;
    }
}
