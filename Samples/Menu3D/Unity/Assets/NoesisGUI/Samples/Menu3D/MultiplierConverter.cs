#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
using System;
using System.Globalization;
using Float = System.Single;
#else
using System;
using System.Globalization;
using System.Windows.Data;
using Float = System.Double;
#endif

namespace Menu3D
{
    public class MultiplierConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (targetType == typeof(Float) && value != null && parameter != null)
            {
                Float input, multiplier;
                if (Float.TryParse(value.ToString(), out input) &&
                    Float.TryParse(parameter.ToString(), out multiplier))
                {
                    return input * multiplier;
                }
            }

            return value;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
