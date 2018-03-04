using System;
using System.Collections.Generic;
using System.Text;
using System.Globalization;
using Noesis;

namespace PlanetsListBox
{
    public class ConvertOrbit : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            float orbit = (float)value;
            float factor = (float)System.Convert.ToDouble(parameter, culture.NumberFormat);
            return (float)Math.Pow(orbit / 40, 0.4) * 770 * factor;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotSupportedException("This method should never be called");
        }
    }
}
