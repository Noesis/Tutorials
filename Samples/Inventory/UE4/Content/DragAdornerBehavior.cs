using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Interactivity;

namespace Inventory
{
    class DragAdornerBehavior : Behavior<ContentControl>
    {
        protected override void OnAttached()
        {
            base.OnAttached();

            this.AssociatedObject.AllowDrop = true;
            this.AssociatedObject.DragEnter += OnDragEnter;
            this.AssociatedObject.DragOver += OnDragOver;
            this.AssociatedObject.DragLeave += OnDragLeave;
            this.AssociatedObject.Drop += OnDrop;
        }

        protected override void OnDetaching()
        {
            this.AssociatedObject.AllowDrop = false;
            this.AssociatedObject.DragEnter -= OnDragEnter;
            this.AssociatedObject.DragLeave -= OnDragLeave;
            this.AssociatedObject.Drop -= OnDrop;

            base.OnDetaching();
        }

        private void OnDragEnter(object sender, DragEventArgs e)
        {
        }

        private void OnDragOver(object sender, DragEventArgs e)
        {
            Point position = e.GetPosition(this.AssociatedObject);
            ViewModel.Instance.DraggedItemX = position.X;
            ViewModel.Instance.DraggedItemY = position.Y;
        }

        private void OnDragLeave(object sender, DragEventArgs e)
        {
        }

        private void OnDrop(object sender, DragEventArgs e)
        {
            e.Effects = DragDropEffects.None;
        }
    }
}
