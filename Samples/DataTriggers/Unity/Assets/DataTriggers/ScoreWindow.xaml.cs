#if UNITY_STANDALONE || UNITY_ANDROID || UNITY_IOS || UNITY_WINRT_8_1
#define UNITY
#endif

#if UNITY
using Noesis;
#else
using System;
using System.Windows;
using System.Windows.Controls;
#endif


namespace DataTriggers
{
	/// <summary>
	/// Interaction logic for ScoreWindow.xaml
	/// </summary>
	#if UNITY
	[UserControlSource("Assets/DataTriggers/ScoreWindow.xaml")]
	#endif
	public partial class ScoreWindow : UserControl
	{
		public ScoreWindow()
		{
			this.InitializeComponent();
		}
	}
}