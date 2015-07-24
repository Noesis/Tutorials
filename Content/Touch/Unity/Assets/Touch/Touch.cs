using UnityEngine;
using Noesis;


public class Touch: MonoBehaviour
{
    Grid _root;

    void Start()
    {
        _root = (Grid)GetComponent<NoesisGUIPanel>().GetContent();
        _root.ManipulationStarting += this.ManipulationStarting;
        _root.ManipulationInertiaStarting += this.ManipulationInertiaStarting;
        _root.ManipulationDelta += this.ManipulationDelta;
    }

    void ManipulationStarting(object sender, ManipulationStartingEventArgs e)
    {
        e.Mode = Noesis.ManipulationModes.All;
        e.ManipulationContainer = (UIElement)_root.FindName("root");
        e.Handled = true;
    }

    void ManipulationInertiaStarting(object sender, ManipulationInertiaStartingEventArgs e)
    {
        e.TranslationBehavior.DesiredDeceleration = 100.0f / (1000.0f * 1000.0f);
        e.RotationBehavior.DesiredDeceleration = 360.0f / (1000.0f * 1000.0f);
        e.ExpansionBehavior.DesiredDeceleration = 300.0f / (1000.0f * 1000.0f);
        e.Handled = true;
    }

    void ManipulationDelta(object sender, ManipulationDeltaEventArgs e)
    {
        var rectangle = (Rectangle)e.Source;
        var transform = (MatrixTransform)rectangle.RenderTransform;
        var matrix = transform.Matrix;

        float rotation = e.DeltaManipulation.Rotation * Mathf.Deg2Rad;
        float originX = e.ManipulationOrigin.X;
        float originY = e.ManipulationOrigin.Y;
        float scale = e.DeltaManipulation.Scale;
        float translationX = e.DeltaManipulation.Translation.X;
        float translationY = e.DeltaManipulation.Translation.Y;

        matrix.RotateAt(rotation, originX, originY);
        matrix.ScaleAt(scale, scale, originX, originY);
        matrix.Translate(translationX, translationY);

        transform.Matrix = matrix;
        e.Handled = true;
    }
}