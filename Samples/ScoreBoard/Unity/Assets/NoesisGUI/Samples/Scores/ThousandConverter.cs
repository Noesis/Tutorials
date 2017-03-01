#if UNITY_5_3_OR_NEWER
#define NOESIS
#endif

#if NOESIS
using Noesis;
#else
using System.Windows.Data;
#endif
using System;
using System.Globalization;

namespace Noesis.Samples
{
	public class ThousandConverter: IValueConverter
	{
		public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
		{
			return string.Format("{0:F2} K", (float)((int)value / 1000.0f));
		}
		
        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
		{
			throw new NotImplementedException();
		}
	}
}