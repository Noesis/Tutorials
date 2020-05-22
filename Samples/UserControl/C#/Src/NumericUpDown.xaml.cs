#if NOESIS
using Noesis;
#else
using System;
using System.Windows;
using System.Windows.Controls;
#endif

namespace UserControls
{
    public class ValueChangedEventArgs : EventArgs
    {
        public int OldValue { get; internal set; }
        public int NewValue { get; internal set; }
    }

    public delegate void ValueChangedEventHandler(object sender, ValueChangedEventArgs e);

    /// <summary>
    /// NumericUpDown control
    /// </summary>
    public partial class NumericUpDown : UserControl
    {
        public NumericUpDown()
        {
            InitializeComponent();
        }

#if NOESIS
        private void InitializeComponent()
        {
            GUI.LoadComponent(this, "NumericUpDown.xaml");
        }

        protected override bool ConnectEvent(object source, string eventName, string handlerName)
        {
            if (eventName == "Click" && handlerName == "UpButton_Click")
            {
                System.WeakReference wr = new System.WeakReference(this);
                ((RepeatButton)source).Click += (s, e) => { ((NumericUpDown)wr.Target).UpButton_Click(s, e); };
                return true;
            }
            if (eventName == "Click" && handlerName == "DownButton_Click")
            {
                System.WeakReference wr = new System.WeakReference(this);
                ((RepeatButton)source).Click += (s, e) => { ((NumericUpDown)wr.Target).DownButton_Click(s, e); };
                return true;
            }
            return false;
        }
#endif

        #region Value property
        public static readonly DependencyProperty ValueProperty = DependencyProperty.Register(
            "Value", typeof(int), typeof(NumericUpDown),
            new PropertyMetadata(0, StaticOnValueChanged));

        public int Value
        {
            get { return (int)GetValue(ValueProperty); }
            set { SetValue(ValueProperty, value); }
        }

        private static void StaticOnValueChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            NumericUpDown control = (NumericUpDown)d;

            int newValue = (int)CoerceValue(d, e.NewValue);
            if (newValue != (int)e.NewValue)
            {
                control.Value = newValue;
            }

            int oldValue = (int)CoerceValue(d, e.OldValue);
            if (newValue != oldValue)
            {
                ValueChangedEventArgs args = new ValueChangedEventArgs
                {
                    OldValue = oldValue,
                    NewValue = newValue
                };
                control.OnValueChanged(args);
            }
        }

        private static object CoerceValue(DependencyObject d, object baseValue)
        {
            NumericUpDown control = (NumericUpDown)d;
            return System.Math.Max(control.MinValue, System.Math.Min((int)baseValue, control.MaxValue));
        }
        #endregion

        #region MinValue property
        public static readonly DependencyProperty MinValueProperty = DependencyProperty.Register(
            "MinValue", typeof(int), typeof(NumericUpDown),
            new PropertyMetadata(int.MinValue));

        public int MinValue
        {
            get { return (int)GetValue(MinValueProperty); }
            set { SetValue(MinValueProperty, value); }
        }
        #endregion

        #region MaxValue property
        public static readonly DependencyProperty MaxValueProperty = DependencyProperty.Register(
            "MaxValue", typeof(int), typeof(NumericUpDown),
            new PropertyMetadata(int.MaxValue));

        public int MaxValue
        {
            get { return (int)GetValue(MaxValueProperty); }
            set { SetValue(MaxValueProperty, value); }
        }
        #endregion

        #region StepValue property
        public static readonly DependencyProperty StepValueProperty = DependencyProperty.Register(
            "StepValue", typeof(int), typeof(NumericUpDown),
            new PropertyMetadata(1));

        public int StepValue
        {
            get { return (int)GetValue(StepValueProperty); }
            set { SetValue(StepValueProperty, value); }
        }
        #endregion

        #region ValueChanged event
        public event ValueChangedEventHandler ValueChanged;

        protected virtual void OnValueChanged(ValueChangedEventArgs e)
        {
            ValueChanged?.Invoke(this, e);
        }
        #endregion

        #region Button handlers
        void UpButton_Click(object sender, RoutedEventArgs e)
        {
            Value += StepValue;
        }

        void DownButton_Click(object sender, RoutedEventArgs e)
        {
            Value -= StepValue;
        }
        #endregion
    }
}
