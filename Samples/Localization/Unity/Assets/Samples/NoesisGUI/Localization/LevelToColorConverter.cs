#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
using System;
using System.Globalization;
#else
using System;
using System.Globalization;
using System.Windows.Data;
using System.Windows.Media;
#endif

namespace Localization
{
    class LevelToColorConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            float level = (float)value;
            float perc = level / 100.0f;
            byte red = (byte)(255 * Math.Min(1.0f, 0.4f + 1.0f - perc));
            byte green = (byte)(255 * Math.Min(1.0f, 0.4f + perc));
            return Color.FromRgb(red, green, 0);
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
