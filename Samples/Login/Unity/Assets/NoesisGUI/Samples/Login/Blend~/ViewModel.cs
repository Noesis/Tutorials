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

        private void Login(object parameter)
        {
            if (CheckCredentials((PasswordBox)parameter))
            {
                Message = "LOGIN SUCCESSFUL";
            }
        }

        private bool CheckCredentials(PasswordBox passwordBox)
        {
            string password = passwordBox.Password;
            if (string.IsNullOrEmpty(AccountName) && !string.IsNullOrEmpty(password))
            {
                Message = "ACCOUNT NAME CANNOT BE EMPTY";
                return false;
            }

            // Verify login and password
            if (AccountName != "noesis" || password != "12345")
            {
                Message = "ACCOUNT NAME OR PASSWORD IS INCORRECT";
                return false;
            }

            return true;
        }
    }
}
