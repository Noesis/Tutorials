#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
using System;
using System.Globalization;
#else
using System;
using System.Windows.Data;
using System.Globalization;
#endif

namespace Scoreboard
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