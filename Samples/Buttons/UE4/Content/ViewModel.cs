#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
using UnityEngine;
#else
using System;
#endif

namespace Buttons
{
    /// <summary>
    /// Buttons sample view model
    /// </summary>
    public class ViewModel
    {
        public ViewModel()
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
            #else
            Console.WriteLine("Start Game");
            #endif
        }

        private void Settings(object parameter)
        {
            #if NOESIS
            Debug.Log("Change Settings");
            #else
            Console.WriteLine("Change Settings");
            #endif
        }

        private void Exit(object parameter)
        {
            #if NOESIS
            Debug.Log("Exit Game");
            #else
            Console.WriteLine("Exit Game");
            #endif
        }
    }
}
