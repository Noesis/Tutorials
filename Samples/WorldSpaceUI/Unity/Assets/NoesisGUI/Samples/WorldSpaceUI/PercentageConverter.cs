#if UNITY_5_3_OR_NEWER
#define NOESIS
using System;
using System.Globalization;
using Noesis;
#else
using System;
using System.Globalization;
using System.Windows.Data;
#endif

namespace WorldSpaceUI
{
    public class PercentageConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value is float f)
            {
                float perc = Math.Max(Math.Min(f * 100.0f, 100.0f), 0.0f);
                return $"{perc.ToString("F0")} %";
            }

            return "0 %";
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
