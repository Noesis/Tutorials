using System;
using System.ComponentModel;
using System.Windows.Input;
using System.Windows;

namespace LayeredUI
{
    public class DelegateCommand : ICommand
    {
        public DelegateCommand(Func<object, bool> canExecute, Action<object> execute)
        {
            _canExecute = canExecute;
            _execute = execute;
        }

        public bool CanExecute(object parameter)
        {
            return _canExecute?.Invoke(parameter) ?? true;
        }

        public void Execute(object parameter)
        {
            _execute?.Invoke(parameter);
        }

        public event System.EventHandler CanExecuteChanged;

        private Func<object, bool> _canExecute;
        private Action<object> _execute;
    }

    public class MainViewModel : INotifyPropertyChanged
    {
        public HUDViewModel HUD { get { return _hud; } }
        public MenuViewModel Menu { get { return _menu; } }

        public DelegateCommand ToggleMenu { get; private set; }

        public MainViewModel()
        {
            _hud = new HUDViewModel();

            ToggleMenu = new DelegateCommand(null, OnToggleMenu);
        }

        private void OnToggleMenu(object param)
        {
            _menu = _menu == null ? new MenuViewModel() : null;
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Menu"));
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private HUDViewModel _hud;
        private MenuViewModel _menu;
    }

    /// <summary>
    /// Interaction logic for MainPage.xaml
    /// </summary>
    public partial class MainPage : Window
    {
        public MainPage()
        {
            InitializeComponent();

            DataContext = new MainViewModel();
        }

#if NOESIS
        private void InitializeComponent()
        {
            NoesisUnity.LoadComponent(this);
        }
#endif
    }
}
