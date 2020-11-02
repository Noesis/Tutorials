#if NOESIS
using Noesis;
using NoesisApp;
#else
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Shapes;
using System.Windows.Input;
using System.Windows.Media;
#endif

namespace Touch
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            System.WeakReference wr = new System.WeakReference(this);
            ManipulationStarting += (s, e) => { ((MainWindow)wr.Target).OnManipulationStarting(s, e); };
            ManipulationInertiaStarting += (s, e) => { ((MainWindow)wr.Target).OnManipulationInertiaStarting(s, e); };
            ManipulationDelta += (s, e) => { ((MainWindow)wr.Target).OnManipulationDelta(s, e); };
            ManipulationCompleted += (s, e) => { ((MainWindow)wr.Target).OnManipulationCompleted(s, e); };

            InitializeComponent();
        }

#if NOESIS
        private void InitializeComponent()
        {
            Noesis.GUI.LoadComponent(this, "MainWindow.xaml");

            root = (Canvas)FindName("root");
        }

        Canvas root;
#endif

        private void OnManipulationStarting(object sender, ManipulationStartingEventArgs e)
        {
            Rectangle rectangle = e.Source as Rectangle;
            if (rectangle != null)
            {
                Panel.SetZIndex(rectangle, ++_index);
                rectangle.Stroke = Brushes.White;
                e.Mode = ManipulationModes.All;
                e.ManipulationContainer = this.root;
                e.Handled = true;
            }
        }

        private void OnManipulationInertiaStarting(object sender, ManipulationInertiaStartingEventArgs e)
        {
            Rectangle rectangle = e.Source as Rectangle;
            if (rectangle != null)
            {
                e.TranslationBehavior.DesiredDeceleration = 360.0f / (100.0f * 1000.0f);
                e.RotationBehavior.DesiredDeceleration = 360.0f / (100.0f * 1000.0f);
                e.ExpansionBehavior.DesiredDeceleration = 300.0f / (100.0f * 1000.0f);
                e.Handled = true;
            }
        }

        private void OnManipulationDelta(object sender, ManipulationDeltaEventArgs e)
        {
            Rectangle rectangle = e.Source as Rectangle;
            if (rectangle != null)
            {
                MatrixTransform transform = (MatrixTransform)rectangle.RenderTransform;
                Matrix mtx = transform.Matrix;

                ManipulationDelta d = e.DeltaManipulation;
                Point o = e.ManipulationOrigin;

                mtx.RotateAt(d.Rotation, o.X, o.Y);
                mtx.ScaleAt(d.Scale.X, d.Scale.Y, o.X, o.Y);
                mtx.Translate(d.Translation.X, d.Translation.Y);

                transform.Matrix = mtx;
                e.Handled = true;
            }
        }

        private void OnManipulationCompleted(object sender, ManipulationCompletedEventArgs e)
        {
            System.Console.WriteLine("ManipulationCompleted");

            Rectangle rectangle = e.Source as Rectangle;
            if (rectangle != null)
            {
                rectangle.Stroke = null;
                e.Handled = true;
            }
        }

        private int _index = 0;
    }
}
