using UnityEditor;
using UnityEngine;

[CustomEditor(typeof(NoesisWorldUI))]
public class NoesisWorldUIEditor : Editor
{
    public override void OnInspectorGUI()
    {
        NoesisWorldUI ui = (NoesisWorldUI)target;

        // Register changes in the component so scene can be saved, and Undo is also enabled
        Undo.RecordObject(ui, "Noesis World UI");

        bool enabled = UnityEngine.GUI.enabled;
        UnityEngine.GUI.enabled = true;

        ui.View = (NoesisView)EditorGUILayout.ObjectField(
            new GUIContent("View", "The View used to render the specified XAML"),
            ui.View, typeof(NoesisView), true);

        ui.Container = EditorGUILayout.TextField(
            new GUIContent("Container", "The name of the Panel container where the specified XAML will be inserted"),
            ui.Container);

        EditorGUILayout.Space();

        ui.Xaml = (NoesisXaml)EditorGUILayout.ObjectField(
            new GUIContent("XAML", "The UI placed in the GameObject position"),
            ui.Xaml, typeof(NoesisXaml), false);

        ui.Scale = EditorGUILayout.FloatField(
            new GUIContent("Scale", "Allows scaling UI pixels to scene units"),
            ui.Scale);

        ui.Offset = EditorGUILayout.Vector3Field(
            new GUIContent("Offset", "Adjust UI position relative to the GameObject"),
            ui.Offset);

        ui.Center = EditorGUILayout.Toggle(
            new GUIContent("Center", "If enabled centers UI in the GameObject position; otherwise anchors top-left corner of the UI to GameObject position"),
            ui.Center);

        UnityEngine.GUI.enabled = enabled;
    }
}
