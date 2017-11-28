#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
using UnityEngine;
#else
using System;
using System.Windows.Controls;
#endif

namespace Login
{
    public class ViewModel : NotifyPropertyChangedBase
    {
        public ViewModel()
        {
            LoginCommand = new DelegateCommand(this.Login);
        }

        public DelegateCommand LoginCommand { get; private set; }

        public string AccountName { get; set; }

        private string _message;
        public string Message
        {
            get { return _message; }
            set
            {
                if (_message != value)
                {
                    _message = value;
                    OnPropertyChanged("Message");
                }
            }
        }

        private bool _notifyMessage;
        public bool NotifyMessage
        {
            get { return _notifyMessage; }
            set
            {
                if (_notifyMessage != value)
                {
                    _notifyMessage = value;
                    OnPropertyChanged("NotifyMessage");
                }
            }
        }

        private void Login(object parameter)
        {
            if (CheckCredentials((PasswordBox)parameter))
            {
                OnNotifyMessage("LOGIN SUCCESSFUL");
            }
        }

        private bool CheckCredentials(PasswordBox passwordBox)
        {
            string password = passwordBox.Password;
            if (string.IsNullOrEmpty(AccountName) && !string.IsNullOrEmpty(password))
            {
                OnNotifyMessage("ACCOUNT NAME CANNOT BE EMPTY");
                return false;
            }

            // Verify login and password
            if (AccountName != "NoesisGUI" || password != "noesis")
            {
                OnNotifyMessage("ACCOUNT NAME OR PASSWORD IS INCORRECT");
                return false;
            }

            return true;
        }

        private void OnNotifyMessage(string message)
        {
            Message = message;
            NotifyMessage = true;
            NotifyMessage = false;
        }
    }
}
