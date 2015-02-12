using System;
using System.Collections.Generic;
using System.Text;
using System.Globalization;
using Noesis;
using UnityEngine;

namespace PlanetsListBox
{
    public class ConvertURI : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            Uri uri = (Uri)value;
            Texture2D texture = (UnityEngine.Texture2D)Resources.Load(uri.OriginalString);
            return new TextureSource(texture);
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotSupportedException("This method should never be called");
        }
    }
}
