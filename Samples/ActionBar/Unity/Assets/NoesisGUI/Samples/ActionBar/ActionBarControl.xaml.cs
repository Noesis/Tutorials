#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
using System.Linq;
#else
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Linq;
#endif

namespace ActionBar
{
    /// <summary>
    /// Interaction logic for ActionBarControl.xaml
    /// </summary>
    public partial class ActionBarControl : UserControl
    {
        public ActionBarControl()
        {
            Initialized += OnInitialized;
            InitializeComponent();
        }

        private void OnInitialized(object sender, EventArgs e)
        {
            foreach (UIElement spell in this.Spells.Children)
            {
                spell.MouseDown += OnSpellMouseDown;
            }

            for (uint i = 0; i < NumSlots; ++i)
            {
                _slots[i] = (Border)FindName(string.Format("Slot{0}", i + 1));
            }
        }
        
        void OnSpellMouseDown(object sender, MouseButtonEventArgs e)
        {
            Border spell = sender as Border;
            if (spell != null)
            {
                // Initiate drag
                this.Floating.Background = spell.Background;
                this.Floating.BorderBrush = spell.BorderBrush;
                this.Floating.Visibility = Visibility.Visible;
    
                _offset = e.GetPosition(spell);
                Point screenPos = e.GetPosition(this.Screen);
                Canvas.SetLeft(this.Floating, screenPos.X - _offset.X);
                Canvas.SetTop(this.Floating, screenPos.Y - _offset.Y);
    
                if (this.Floating.CaptureMouse())
                {
                    this.Floating.MouseMove += OnFloatingDrag;
                    this.Floating.MouseUp += OnFloatingDrop;
                }
            }
        }
        
        void OnFloatingDrag(object sender, MouseEventArgs e)
        {
            Point screenPos = e.GetPosition(this.Screen);
            Canvas.SetLeft(this.Floating, screenPos.X - _offset.X);
            Canvas.SetTop(this.Floating, screenPos.Y - _offset.Y);
        }
    
        void OnFloatingDrop(object sender, MouseButtonEventArgs e)
        {
            this.Floating.ReleaseMouseCapture();
            this.Floating.MouseMove -= OnFloatingDrag;
            this.Floating.MouseUp -= OnFloatingDrop;
    
            this.Floating.Visibility = Visibility.Collapsed;
    
            for (uint i = 0; i < NumSlots; ++i)
            {
                Border slot = _slots[i];
                Point pos = e.GetPosition(slot);
                Size size = slot.RenderSize;
    
                if (pos.X >= 0.0f && pos.X < size.Width &&
                    pos.Y >= 0.0f && pos.Y < size.Height)
                {
                    slot.Background = this.Floating.Background;
                    slot.BorderBrush = this.Floating.BorderBrush;
                    break;
                }
            }
        }

#if NOESIS
        private void InitializeComponent()
        {
            Noesis.GUI.LoadComponent(this, "Assets/NoesisGUI/Samples/ActionBar/ActionBarControl.xaml");

            Screen = (Canvas)FindName("Screen");
            Spells = (WrapPanel)FindName("Spells");
            Floating = (Border)FindName("Floating");
        }

        Canvas Screen;
        WrapPanel Spells;
        Border Floating;
#endif

        #region Private members
        Point _offset;

        const int NumSlots = 6;
        Border[] _slots = new Border[NumSlots];
        #endregion
    }
}