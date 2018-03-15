#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
#else
using System;
using System.Windows;
using System.Windows.Controls;
#endif

namespace NorthGame
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Grid
    {
        public MainWindow()
        {
            Initialized += OnInitialized;
            InitializeComponent();

            UIElement cursor = (UIElement)FindName("Cursor");

            PreviewMouseMove += (o, e) =>
            {
                Point p = e.GetPosition(this);
                Canvas.SetLeft(cursor, p.X);
                Canvas.SetTop(cursor, p.Y);
            };
        }

#if NOESIS
        private void InitializeComponent()
        {
            Noesis.GUI.LoadComponent(this, "Assets/NoesisGUI/Samples/NorthGame/MainWindow.xaml");

            UnityEngine.Cursor.visible = false;
        }
#endif

        private void OnInitialized(object sender, EventArgs e)
        {
            DataContext = new ViewModel(this);
        }
    }
}
