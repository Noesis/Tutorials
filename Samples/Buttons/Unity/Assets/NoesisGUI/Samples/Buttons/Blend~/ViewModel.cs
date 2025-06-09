using System;

namespace Buttons
{
    /// <summary>
    /// Buttons sample view model
    /// </summary>
    public class ViewModel
    {
        public ViewModel()
        {
            StartCommand = new DelegateCommand(OnStart);
            SettingsCommand = new DelegateCommand(OnSettings);
            ExitCommand = new DelegateCommand(OnExit);
        }

        public DelegateCommand StartCommand { get; private set; }
        public DelegateCommand SettingsCommand { get; private set; }
        public DelegateCommand ExitCommand { get; private set; }
        
        private void OnStart(object parameter)
        {
            Console.WriteLine("Start Game");
        }

        private void OnSettings(object parameter)
        {
            Console.WriteLine("Change Settings");
        }

        private void OnExit(object parameter)
        {
            Console.WriteLine("Exit Game");
        }
    }
}
