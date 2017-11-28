#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
using UnityEngine;
#else
using System;
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
        public string AccountPassword { get; set; }

        private string _validationText;
        public string ValidationText
        {
            get { return _validationText; }
            set
            {
                if (_validationText != value)
                {
                    _validationText = value;
                    OnPropertyChanged("ValidationText");
                }
            }
        }

        private bool _invalidCredentials;
        public bool InvalidCredentials
        {
            get { return _invalidCredentials; }
            set
            {
                if (_invalidCredentials != value)
                {
                    _invalidCredentials = value;
                    OnPropertyChanged("InvalidCredentials");
                }
            }
        }

        private void Login(object parameter)
        {
            if (CheckCredentials())
            {
                #if NOESIS
                Debug.Log("Login succesfully");
                #else
                Console.WriteLine("Login succesfully");
                #endif
            }
        }

        private bool CheckCredentials()
        {
            if (string.IsNullOrEmpty(AccountName) && !string.IsNullOrEmpty(AccountPassword))
            {
                NotifyInvalidCredentials("ACCOUNT NAME CANNOT BE EMPTY");
                return false;
            }

            // Verify login and password
            if (AccountName != "NoesisGUI" || AccountPassword != "noesis")
            {
                NotifyInvalidCredentials("ACCOUNT NAME OR PASSWORD IS INCORRECT");
                return false;
            }

            return true;
        }

        private void NotifyInvalidCredentials(string message)
        {
            ValidationText = message;
            InvalidCredentials = true;
            InvalidCredentials = false;
        }
    }
}
