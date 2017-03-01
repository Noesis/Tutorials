#if UNITY_5_3_OR_NEWER
#define NOESIS
#endif

#if NOESIS
using Noesis;
using UnityEngine;
#else
using System;
#endif

namespace Noesis.Samples
{
	/// <summary>
	/// Buttons sample view model
	/// </summary>
	public class ButtonsViewModel
	{
		public ButtonsViewModel()
		{
			StartCommand = new DelegateCommand(this.Start);
			SettingsCommand = new DelegateCommand(this.Settings);
			ExitCommand = new DelegateCommand(this.Exit);
		}
		
		public DelegateCommand StartCommand { get; private set; }
		public DelegateCommand SettingsCommand { get; private set; }
		public DelegateCommand ExitCommand { get; private set; }
		
		private void Start(object parameter)
		{
			#if NOESIS
			Debug.Log("Start Game");
			#endif
		}
		
		private void Settings(object parameter)
		{
			#if NOESIS
			Debug.Log("Change Settings");
			#endif
		}
		
		private void Exit(object parameter)
		{
			#if NOESIS
			Debug.Log("Exit Game");
			#endif
		}
	}
}