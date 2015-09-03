#if UNITY_STANDALONE || UNITY_ANDROID || UNITY_IOS || UNITY_WINRT_8_1
#define UNITY
#endif

#if UNITY
using Noesis;
#else
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
#endif
using System.Linq;

namespace ActionBar
{
	/// <summary>
	/// Interaction logic for ActionBarControl.xaml
	/// </summary>
	#if UNITY
	[UserControlSource("Assets/ActionBar/ActionBarControl.xaml")]
	#endif
	public partial class ActionBarControl : UserControl
	{
		Canvas _canvas;
    	Point _offset;
    	Border _floating;
		
	    const int NumSlots = 6;
    	Border[] _slots = new Border[NumSlots];

		public ActionBarControl()
		{
			this.Initialized += OnInitialized;
			
			this.InitializeComponent();
		}
		
		private void OnInitialized(object sender, EventArgs e)
		{
			_canvas = (Canvas)FindName("Canvas");
			_floating = (Border)FindName("Floating");
	
			var spells = (Panel)FindName("Spells");
			foreach (var spell in spells.Children.Cast<UIElement>())
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
				_floating.Background = spell.Background;
				_floating.BorderBrush = spell.BorderBrush;
				_floating.Visibility = Visibility.Visible;
	
				_offset = e.GetPosition(spell);
				Point canvasPos = e.GetPosition(_canvas);
				Canvas.SetLeft(_floating, canvasPos.X - _offset.X);
				Canvas.SetTop(_floating, canvasPos.Y - _offset.Y);
	
				if (_floating.CaptureMouse())
				{
					_floating.MouseMove += OnFloatingDrag;
					_floating.MouseUp += OnFloatingDrop;
				}
			}
		}
		
		void OnFloatingDrag(object sender, MouseEventArgs e)
		{
			Point canvasPos = e.GetPosition(_canvas);
			Canvas.SetLeft(_floating, canvasPos.X - _offset.X);
			Canvas.SetTop(_floating, canvasPos.Y - _offset.Y);
		}
	
		void OnFloatingDrop(object sender, MouseButtonEventArgs e)
		{
			_floating.ReleaseMouseCapture();
			_floating.MouseMove -= OnFloatingDrag;
			_floating.MouseUp -= OnFloatingDrop;
	
			_floating.Visibility = Visibility.Collapsed;
	
			for (uint i = 0; i < NumSlots; ++i)
			{
				Border slot = _slots[i];
				Point pos = e.GetPosition(slot);
				Size size = slot.RenderSize;
	
				if (pos.X >= 0.0f && pos.X < size.Width &&
					pos.Y >= 0.0f && pos.Y < size.Height)
				{
					slot.Background = _floating.Background;
					slot.BorderBrush = _floating.BorderBrush;
					break;
				}
			}
		}
	}
}