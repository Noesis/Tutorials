#if UNITY_5_3_OR_NEWER
#define NOESIS
#endif

#if NOESIS
using Noesis;
#else
using System;
using System.Windows;
using System.Windows.Controls;
#endif


namespace Noesis.Samples
{
	public class PasswordHelper : DependencyObject
	{
		public static DependencyProperty PasswordProperty = DependencyProperty.RegisterAttached(
			"Password", typeof(string), typeof(PasswordHelper),
			new FrameworkPropertyMetadata(string.Empty, OnPasswordPropertyChanged));
	
		public static DependencyProperty AttachProperty = DependencyProperty.RegisterAttached(
			"Attach", typeof(bool), typeof(PasswordHelper), new PropertyMetadata(false, Attach));
	
		private static DependencyProperty IsUpdatingProperty = DependencyProperty.RegisterAttached(
			"IsUpdating", typeof(bool), typeof(PasswordHelper));
	
		public static void SetAttach(DependencyObject dp, bool value)
		{
			dp.SetValue(AttachProperty, value);
		}
	
		public static bool GetAttach(DependencyObject dp)
		{
			return (bool)dp.GetValue(AttachProperty);
		}
	
		public static string GetPassword(DependencyObject dp)
		{
			return (string)dp.GetValue(PasswordProperty);
		}
	
		public static void SetPassword(DependencyObject dp, string value)
		{
			dp.SetValue(PasswordProperty, value);
		}
	
		private static bool GetIsUpdating(DependencyObject dp)
		{
			return (bool)dp.GetValue(IsUpdatingProperty);
		}
	
		private static void SetIsUpdating(DependencyObject dp, bool value)
		{
			dp.SetValue(IsUpdatingProperty, value);
		}
	
		private static void OnPasswordPropertyChanged(DependencyObject sender, DependencyPropertyChangedEventArgs e)
		{
			PasswordBox passwordBox = sender as PasswordBox;
			passwordBox.PasswordChanged -= PasswordChanged;
	
			if (!(bool)GetIsUpdating(passwordBox))
			{
				passwordBox.Password = (string)e.NewValue;
			}
			passwordBox.PasswordChanged += PasswordChanged;
		}
	
		private static void Attach(DependencyObject sender, DependencyPropertyChangedEventArgs e)
		{
			PasswordBox passwordBox = sender as PasswordBox;
	
			if (passwordBox == null)
				return;
	
			if ((bool)e.OldValue)
			{
				passwordBox.PasswordChanged -= PasswordChanged;
			}
	
			if ((bool)e.NewValue)
			{
				passwordBox.PasswordChanged += PasswordChanged;
			}
		}
	
		private static void PasswordChanged(object sender, RoutedEventArgs e)
		{
			PasswordBox passwordBox = sender as PasswordBox;
			SetIsUpdating(passwordBox, true);
			SetPassword(passwordBox, passwordBox.Password);
			SetIsUpdating(passwordBox, false);
		}
	}
}