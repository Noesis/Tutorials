#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
#else
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
#endif

namespace Buttons
{
    public class ElementExtensions: DependencyObject
    {
        public ElementExtensions()
        {
        }

        #region FocusOnLoaded
        public static DependencyProperty FocusOnLoadedProperty = DependencyProperty.RegisterAttached(
            "FocusOnLoaded", typeof(bool), typeof(ElementExtensions), new PropertyMetadata(false, OnFocusOnLoadedChanged));

        public static bool GetFocusOnLoaded(DependencyObject d)
        {
            return (bool)d.GetValue(FocusOnLoadedProperty);
        }

        public static void SetFocusOnLoaded(DependencyObject d, bool value)
        {
            d.SetValue(FocusOnLoadedProperty, value);
        }

        private static void OnFocusOnLoadedChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            FrameworkElement element = d as FrameworkElement;
            if (element != null && (bool)e.NewValue == true)
            {
                element.Loaded += (s, a) => element.Focus();
            }
        }
        #endregion

        #region FocusOnHover
        public static DependencyProperty FocusOnHoverProperty = DependencyProperty.RegisterAttached(
            "FocusOnHover", typeof(bool), typeof(ElementExtensions), new PropertyMetadata(false, OnFocusOnHoverChanged));

        public static bool GetFocusOnHover(DependencyObject d)
        {
            return (bool)d.GetValue(FocusOnHoverProperty);
        }

        public static void SetFocusOnHover(DependencyObject d, bool value)
        {
            d.SetValue(FocusOnHoverProperty, value);
        }

        private static void OnFocusOnHoverChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            UIElement element = d as UIElement;
            if (element != null && (bool)e.NewValue == true)
            {
                element.Focus();
            }
        }
        #endregion

        #region SelectOnHover
        public static DependencyProperty SelectOnHoverProperty = DependencyProperty.RegisterAttached(
            "SelectOnHover", typeof(bool), typeof(ElementExtensions), new PropertyMetadata(false, OnSelectOnHoverChanged));

        public static bool GetSelectOnHover(DependencyObject d)
        {
            return (bool)d.GetValue(SelectOnHoverProperty);
        }

        public static void SetSelectOnHover(DependencyObject d, bool value)
        {
            d.SetValue(SelectOnHoverProperty, value);
        }

        private static void OnSelectOnHoverChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            UIElement element = d as UIElement;
            if (element != null && (bool)e.NewValue == true)
            {
                Selector.SetIsSelected(element, true);
            }
        }
        #endregion

        #region SelectAllOnFocus
        public static DependencyProperty SelectAllOnFocusProperty = DependencyProperty.RegisterAttached(
            "SelectAllOnFocus", typeof(bool), typeof(ElementExtensions), new PropertyMetadata(false, OnSelectAllOnFocusChanged));

        public static bool GetSelectAllOnFocus(DependencyObject d)
        {
            return (bool)d.GetValue(SelectOnHoverProperty);
        }

        public static void SetSelectAllOnFocus(DependencyObject d, bool value)
        {
            d.SetValue(SelectOnHoverProperty, value);
        }

        private static void OnSelectAllOnFocusChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            UIElement element = d as UIElement;
            if (element != null && (bool)e.NewValue == true)
            {
                element.GotFocus += (sender, args) =>
                {
                    if (sender is TextBox)
                    {
                        ((TextBox)sender).SelectAll();
                    }
                    else if (sender is PasswordBox)
                    {
                        ((PasswordBox)sender).SelectAll();
                    }
                };
            }
        }
        #endregion
    }
}
