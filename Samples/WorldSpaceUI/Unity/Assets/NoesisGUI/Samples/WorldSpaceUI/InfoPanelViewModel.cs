using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using UnityEngine;
using Noesis;
using System;
using System.Globalization;

namespace InWorldUI
{
    public class PercentageConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value is float f)
            {
                float perc = Math.Clamp(f * 100.0f, 0.0f, 100.0f);
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

public class InfoPanelViewModel : MonoBehaviour
{
    public string _name;
    public string Name { get => _name; }

    public float _energy;
    public float Energy { get => _energy; }

    void Start()
    {
        NoesisWorldUI ui = GetComponent<NoesisWorldUI>();
        ui.Content.DataContext = this;
    }
}
