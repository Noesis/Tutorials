#if UNITY_5_3_OR_NEWER
#define NOESIS
using System;
using Noesis;
using NoesisApp;
using System.Globalization;
#else
using System;
using System.Windows;
using System.Windows.Media;
using System.Globalization;
using System.Windows.Data;
using System.Windows.Controls;
#endif

namespace UserControls
{
    public class ColorConverter : IMultiValueConverter
    {
        public object Convert(object[] values, Type targetType, object parameter, CultureInfo culture)
        {
            if (values.Length == 3 && values[0] is int r && values[1] is int g && values[2] is int b)
            {
                return Color.FromRgb((byte)r, (byte)g, (byte)b);
            }

            return Colors.Black;
        }

        public object[] ConvertBack(object value, Type[] targetTypes, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Page
    {
        public MainWindow()
        {
            InitializeComponent();
        }

#if NOESIS
        private void InitializeComponent()
        {
            GUI.LoadComponent(this, "Assets/NoesisGUI/Samples/UserControl/MainWindow.xaml");
        }
#endif
    }
}
