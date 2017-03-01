#if UNITY_5_3_OR_NEWER
#define NOESIS
#endif

#if NOESIS
using Noesis;
#else
using System;
using System.Windows;
using System.Windows.Controls;
#endif

namespace Noesis.Samples
{
    /// <summary>
    /// Interaction logic for QuestLogWindow.xaml
    /// </summary>
    public partial class QuestLogWindow : UserControl
    {
        public QuestLogWindow()
        {
            this.Initialized += OnInitialized;
            this.InitializeComponent();
        }

#if NOESIS
        void InitializeComponent()
        {
            Noesis.GUI.LoadComponent(this, "Assets/NoesisGUI/Samples/QuestLog/QuestLogWindow.xaml");
        }
#endif

        private void OnInitialized(object sender, EventArgs args)
        {
            this.DataContext = new QuestLogViewModel((ResourceDictionary)Resources.MergedDictionaries[0]);
        }
    }
}
