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

namespace Touch
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private int _index = 0;

        protected override void OnManipulationStarting(ManipulationStartingEventArgs e)
        {
            Rectangle rectangle = e.Source as Rectangle;

            if (rectangle != null)
            {
                Panel.SetZIndex(rectangle, ++_index);
                rectangle.Stroke = Brushes.White;
                e.Mode = ManipulationModes.All;
                e.ManipulationContainer = (IInputElement)FindName("root");
                e.Handled = true;
            }

            base.OnManipulationStarting(e);
        }

        protected override void OnManipulationInertiaStarting(ManipulationInertiaStartingEventArgs e)
        {
            Rectangle rectangle = e.Source as Rectangle;

            if (rectangle != null)
            {
                e.TranslationBehavior.DesiredDeceleration = 360.0f / (100.0f * 1000.0f);
                e.RotationBehavior.DesiredDeceleration = 360.0f / (100.0f * 1000.0f);
                e.ExpansionBehavior.DesiredDeceleration = 360.0f / (100.0f * 1000.0f);
                e.Handled = true;
            }

            base.OnManipulationInertiaStarting(e);
        }

        protected override void OnManipulationDelta(ManipulationDeltaEventArgs e)
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

            base.OnManipulationDelta(e);
        }

        protected override void OnManipulationCompleted(ManipulationCompletedEventArgs e)
        {
            Rectangle rectangle = e.Source as Rectangle;

            if (rectangle != null)
            {
                rectangle.Stroke = null;
                e.Handled = true;
            }

            base.OnManipulationCompleted(e);
        }
    }
}
