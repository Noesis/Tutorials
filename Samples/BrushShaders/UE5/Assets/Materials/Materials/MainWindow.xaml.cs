using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Materials
{
    public class Noise : NoesisGUIExtensions.BrushShader
    {
        public Color Color
        {
            get { return (Color)GetValue(ColorProperty); }
            set { SetValue(ColorProperty, value); }
        }

        public static readonly DependencyProperty ColorProperty = DependencyProperty.Register(
            "Color", typeof(Color), typeof(Noise), new PropertyMetadata(Colors.White));

        public static int GetSeed(DependencyObject obj)
        {
            return (int)obj.GetValue(SeedProperty);
        }

        public static void SetSeed(DependencyObject obj, int value)
        {
            obj.SetValue(SeedProperty, value);
        }

        public static readonly DependencyProperty SeedProperty = DependencyProperty.RegisterAttached(
            "Seed", typeof(int), typeof(Noise), new PropertyMetadata(0));
    }

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : UserControl
    {
        public MainWindow()
        {
            InitializeComponent();
        }
    }
}
