using System;
using System.Globalization;
using System.Windows.Data;

namespace Menu3D
{
    public class MultiplierConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (targetType == typeof(double) && value != null && parameter != null)
            {
                double input, multiplier;
                if (double.TryParse(value.ToString(), out input) &&
                    double.TryParse(parameter.ToString(), out multiplier))
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
