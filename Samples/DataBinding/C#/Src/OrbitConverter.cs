#if NOESIS
using Noesis;
using NoesisApp;
using System;
using System.Globalization;
using Float = System.Single;
#else
using System;
using System.Globalization;
using System.Windows.Data;
using Float = System.Double;
#endif

namespace DataBinding
{
    public class OrbitConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (targetType == typeof(Float) && value is Float && parameter is string)
            {
                Float orbit = (Float)value;
                Float factor = Float.Parse((string)parameter, CultureInfo.InvariantCulture);
                return (Float)(Math.Pow(orbit / 40, 0.4) * 770.0 * factor);
            }

            return default(Float);
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
