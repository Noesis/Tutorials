#if NOESIS
using Noesis;
#else
using System;
using System.Windows;
using System.Windows.Controls;
#endif

namespace CustomControl
{
    public class DateTime : Control
    {
        #region Day property
        public static readonly DependencyProperty DayProperty = DependencyProperty.Register(
            "Day", typeof(int), typeof(DateTime), new PropertyMetadata(1));

        public int Day
        {
            get { return (int)GetValue(DayProperty); }
            set { SetValue(DayProperty, value); }
        }
        #endregion

        #region Month property
        public static readonly DependencyProperty MonthProperty = DependencyProperty.Register(
            "Month", typeof(int), typeof(DateTime), new PropertyMetadata(1));

        public int Month
        {
            get { return (int)GetValue(MonthProperty); }
            set { SetValue(MonthProperty, value); }
        }
        #endregion

        #region Year property
        public static readonly DependencyProperty YearProperty = DependencyProperty.Register(
            "Year", typeof(int), typeof(DateTime), new PropertyMetadata(2000));

        public int Year
        {
            get { return (int)GetValue(YearProperty); }
            set { SetValue(YearProperty, value); }
        }
        #endregion

        #region Hour property
        public static readonly DependencyProperty HourProperty = DependencyProperty.Register(
            "Hour", typeof(int), typeof(DateTime), new PropertyMetadata(0));

        public int Hour
        {
            get { return (int)GetValue(HourProperty); }
            set { SetValue(HourProperty, value); }
        }
        #endregion

        #region Minute property
        public static readonly DependencyProperty MinuteProperty = DependencyProperty.Register(
            "Minute", typeof(int), typeof(DateTime), new PropertyMetadata(0));

        public int Minute
        {
            get { return (int)GetValue(MinuteProperty); }
            set { SetValue(MinuteProperty, value); }
        }
        #endregion

        #region Second property
        public int Second
        {
            get { return (int)GetValue(SecondProperty); }
            set { SetValue(SecondProperty, value); }
        }

        public static readonly DependencyProperty SecondProperty = DependencyProperty.Register(
            "Second", typeof(int), typeof(DateTime), new PropertyMetadata(0));
        #endregion
    }
}
