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
    class DropItemBehavior : Behavior<FrameworkElement>
    {
        public bool IsDragOver
        {
            get { return (bool)GetValue(IsDragOverProperty); }
            set { SetValue(IsDragOverProperty, value); }
        }

        public static readonly DependencyProperty IsDragOverProperty = DependencyProperty.Register(
            "IsDragOver", typeof(bool), typeof(DropItemBehavior), new PropertyMetadata(false));

        public ICommand DropCommand
        {
            get { return (ICommand)GetValue(DropCommandProperty); }
            set { SetValue(DropCommandProperty, value); }
        }

        public static readonly DependencyProperty DropCommandProperty = DependencyProperty.Register(
            "DropCommand", typeof(ICommand), typeof(DropItemBehavior), new PropertyMetadata(null));

        protected override void OnAttached()
        {
            base.OnAttached();

            FrameworkElement element = AssociatedObject;
            if (element != null)
            {
                element.AllowDrop = true;
                element.PreviewDragEnter += OnDragEnter;
                element.PreviewDragLeave += OnDragLeave;
                element.PreviewDrop += OnDrop;
            }
        }

        protected override void OnDetaching()
        {
            FrameworkElement element = AssociatedObject;
            if (element != null)
            {
                element.AllowDrop = false;
                element.PreviewDragEnter -= OnDragEnter;
                element.PreviewDragLeave -= OnDragLeave;
                element.PreviewDrop -= OnDrop;
            }

            base.OnDetaching();
        }

        private void OnDragEnter(object sender, DragEventArgs e)
        {
            IsDragOver = true;
            e.Handled = true;
        }

        private void OnDragLeave(object sender, DragEventArgs e)
        {
            IsDragOver = false;
            e.Handled = true;
        }

        private void OnDrop(object sender, DragEventArgs e)
        {
            IsDragOver = false;

            object item = this.AssociatedObject.DataContext;
            if (item != null && DropCommand != null && DropCommand.CanExecute(item))
            {
                DropCommand.Execute(item);
            }
            else
            {
                e.Effects = DragDropEffects.None;
            }

            e.Handled = true;
        }
    }
}
