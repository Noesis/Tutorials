using System;
using System.Globalization;
using System.Windows.Data;

namespace DataBinding
{
    public class OrbitConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (targetType == typeof(double) && value is double && parameter is string)
            {
                double orbit = (double)value;
                double factor = double.Parse((string)parameter, CultureInfo.InvariantCulture);
                return (double)(Math.Pow(orbit / 40, 0.4) * 770.0 * factor);
            }

            return default(double);
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
