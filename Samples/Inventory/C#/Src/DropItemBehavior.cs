#if NOESIS
using Noesis;
using NoesisApp;
#else
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Interactivity;
#endif

namespace Inventory
{
    class DropItemBehavior : Behavior<ContentControl>
    {
        protected override void OnAttached()
        {
            base.OnAttached();

            this.AssociatedObject.AllowDrop = true;
            this.AssociatedObject.PreviewDragEnter += OnDragEnter;
            this.AssociatedObject.PreviewDragLeave += OnDragLeave;
            this.AssociatedObject.PreviewDrop += OnDrop;
        }

        protected override void OnDetaching()
        {
            this.AssociatedObject.AllowDrop = false;
            this.AssociatedObject.PreviewDragEnter -= OnDragEnter;
            this.AssociatedObject.PreviewDragLeave -= OnDragLeave;
            this.AssociatedObject.PreviewDrop -= OnDrop;

            base.OnDetaching();
        }

        private void OnDragEnter(object sender, DragEventArgs e)
        {
            ContentControl control = (ContentControl)sender;
            Slot slot = (Slot)control.Content;

            slot.IsDragOver = true;

            e.Handled = true;
        }

        private void OnDragLeave(object sender, DragEventArgs e)
        {
            ContentControl control = (ContentControl)sender;
            Slot slot = (Slot)control.Content;

            slot.IsDragOver = false;

            e.Handled = true;
        }

        private void OnDrop(object sender, DragEventArgs e)
        {
            Slot sourceSlot = (Slot)e.Data.GetData(typeof(Slot));
            Slot targetSlot = (Slot)this.AssociatedObject.Content;
            targetSlot.IsDragOver = false;

            if (targetSlot.IsDropAllowed)
            {
                // Move any item in target slot to the source slot
                sourceSlot.Item = targetSlot.Item;

                // Move dragged item to the target slot
                targetSlot.Item = ViewModel.Instance.DraggedItem;
            }
            else
            {
                e.Effects = DragDropEffects.None;
            }

            e.Handled = true;
        }
    }
}
