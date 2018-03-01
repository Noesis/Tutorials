#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
using System;
using System.Globalization;
#else
using System;
using System.Globalization;
using System.Windows.Data;
#endif

namespace NorthGame
{
    public class UppercaseConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value is string)
            {
                return ((string)value).ToUpper();
            }
            else
            {
                return "";
            }
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}