#if UNITY_5_3_OR_NEWER
using Noesis;
#else
using System.Windows.Data;
#endif
using System;
using System.Globalization;

namespace DataBinding
{
    public class OrbitConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value is float && parameter is string)
            {
                float orbit = (float)value;
                float factor = float.Parse((string)parameter, CultureInfo.InvariantCulture);
                return (float)(Math.Pow(orbit / 40, 0.4) * 770.0 * factor);
            }

            return default(float);
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
