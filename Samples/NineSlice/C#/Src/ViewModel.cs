#if NOESIS
using Noesis;
using System;
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
            Console.WriteLine("Start Game");
        }

        private void Settings(object parameter)
        {
            Console.WriteLine("Change Settings");
        }

        private void Exit(object parameter)
        {
            Console.WriteLine("Exit Game");
        }
    }
}
