#if NOESIS
using Noesis;
using System;
using System.Globalization;
#else
using System;
using System.Globalization;
using System.Windows.Data;
#endif

namespace CustomControl
{
    public class HoursConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            int hours = (int)value;
            return hours * 30.0f;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    public class MinutesConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            int minutes = (int)value;
            return minutes * 6.0f;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    public class SecondsConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            int seconds = (int)value;
            return seconds * 6.0f;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
