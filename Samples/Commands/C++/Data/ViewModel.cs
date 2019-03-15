using System.ComponentModel;
using System.Windows.Input;

namespace Commands
{
    public class ViewModel : INotifyPropertyChanged
    {
        private string _input;
        public string Input
        {
            get { return _input; }
            set
            {
                if (_input != value)
                {
                    _input = value;
                    OnPropertyChanged("Input");
                }
            }
        }

        private string _output;
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

        public ICommand SayHelloCommand { get; private set; }

        public ViewModel()
        {
            SayHelloCommand = new DelegateCommand(SayHello);
        }

        private void SayHello(object param)
        {
            Output = string.Format("Hello, {0} ({1})", Input, (string)param);
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string name)
        {
            PropertyChangedEventHandler handler = PropertyChanged;
            if (handler != null)
            {
                handler(this, new PropertyChangedEventArgs(name));
            }
        }
    }
}
