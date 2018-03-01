#if NOESIS
using Noesis;
using System;
using System.ComponentModel;
using System.Windows.Input;
#else
using System;
using System.Windows;
using System.ComponentModel;
using System.Windows.Input;
#endif

namespace Menu3D
{
    public enum State
    {
        Main,
        Start,
        Settings
    }

    public class ViewModel : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        public ICommand Start { get; private set; }
        public ICommand StartCasual { get; private set; }
        public ICommand StartNormal { get; private set; }
        public ICommand StartVeteran { get; private set; }
        public ICommand Settings { get; private set; }
        public ICommand Exit { get; private set; }
        public ICommand Back { get; private set; }
        public ICommand FadeInCompleted { get; private set; }

        public ViewModel()
        {
            Start = new DelegateCommand(OnStart);
            StartCasual = new DelegateCommand(OnStartCasual);
            StartNormal = new DelegateCommand(OnStartNormal);
            StartVeteran = new DelegateCommand(OnStartVeteran);
            Settings = new DelegateCommand(OnSettings);
            Exit = new DelegateCommand(OnExit);
            Back = new DelegateCommand(OnBack);
            FadeInCompleted = new DelegateCommand(OnFadeInCompleted);

            State = State.Main;
        }

        private State _state;
        public State State
        {
            get { return _state; }
            set
            {
                if (_state != value)
                {
                    _state = value;
                    OnPropertyChanged("State");
                }
            }
        }

        private void OnPropertyChanged(string name)
        {
            PropertyChangedEventHandler handler = PropertyChanged;
            if (handler != null)
            {
                handler(this, new PropertyChangedEventArgs(name));
            }
        }

        private void OnStart(object parameter)
        {
            State = State.Start;
        }

        private void OnStartCasual(object parameter)
        {
            Console.WriteLine("Start Casual");
        }

        private void OnStartNormal(object parameter)
        {
            Console.WriteLine("Start Normal");
        }

        private void OnStartVeteran(object parameter)
        {
            Console.WriteLine("Start Veteran");
        }

        private void OnSettings(object parameter)
        {
            State = State.Settings;
        }

        private void OnExit(object parameter)
        {
            Application.Current.Shutdown(0);
        }

        private void OnBack(object parameter)
        {
            switch (State)
            {
                case State.Main:
                {
                    OnExit(null);
                    break;
                }
                case State.Start:
                case State.Settings:
                {
                    State = State.Main;
                    break;
                }
            }
        }

        private void OnFadeInCompleted(object parameter)
        {
            UIElement target = (UIElement)parameter;
#if NOESIS
            target.Focus();
#else
            target.Dispatcher.BeginInvoke(new Action(() =>
            {
                target.Focus();
            }));
#endif
        }
    }
}
