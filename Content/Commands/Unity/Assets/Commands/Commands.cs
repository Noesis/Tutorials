using UnityEngine;
using System;
using System.Globalization;


namespace Noesis.Samples
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    public class DelegateCommand : System.Windows.Input.ICommand
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        private readonly Action<object> _action;
        
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        public DelegateCommand(Action<object> action)
        {
            _action = action;
        }

        public event EventHandler CanExecuteChanged
        {
            add { }
            remove { }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        public bool CanExecute(object parameter)
        {
            return true;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        public void Execute(object parameter)
        {
            _action(parameter);
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    public class CapsConverter : Noesis.IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            return value.ToString().ToUpper();
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    public class NotifyPropertyChangedBase : System.ComponentModel.INotifyPropertyChanged
    {
        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged(string name)
        {
            System.ComponentModel.PropertyChangedEventHandler handler = PropertyChanged;
            if (handler != null)
            {
                handler(this, new System.ComponentModel.PropertyChangedEventArgs(name));
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    public class ViewModel : NotifyPropertyChangedBase
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        public string Input  {  get; set; }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        private string _output = string.Empty;
        public string Output
        {
            get { return _output; }
            set
            {
                if (_output != value)
                {
                    _output = value;
                    OnPropertyChanged("Output");
                }
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        public Noesis.Samples.DelegateCommand SayHelloCommand { get; private set; }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        public ViewModel()
        {
            SayHelloCommand = new Noesis.Samples.DelegateCommand(SayHello);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        private void SayHello(object parameter)
        {
            string param = (string)parameter;
            Output = System.String.Format("Hello, {0} ({1})", Input, param);
        }
    }
}
