#if UNITY_5_3_OR_NEWER
#define NOESIS
#endif

#if NOESIS
using Noesis;
using UnityEngine;
#else
using System;
#endif

namespace Noesis.Samples
{
	public class LoginViewModel : NotifyPropertyChangedBase
	{
		public LoginViewModel()
		{
			LoginCommand = new DelegateCommand(this.CanLogin, this.Login);
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
		
		private bool _notifyInvalidCredentials;
		public bool NotifyInvalidCredentials
		{
			get { return _notifyInvalidCredentials; }
			set
			{
				if (_notifyInvalidCredentials != value)
				{
					_notifyInvalidCredentials = value;
					OnPropertyChanged("NotifyInvalidCredentials");
				}
			}
		}
		
		private bool CanLogin(object parameter)
		{
			bool invalidCredentials = string.IsNullOrEmpty(AccountName) && !string.IsNullOrEmpty(AccountPassword);
			ValidationText = invalidCredentials ? "ACCOUNT NAME CANNOT BE EMPTY" : "";
			NotifyInvalidCredentials = invalidCredentials;
			NotifyInvalidCredentials = false;
			
			//return !invalidCredentials;
            return true;
		}
		
		private void Login(object parameter)
		{
			if (TryLogin(AccountName, AccountPassword))
			{
				#if NOESIS
				Debug.Log("Login succesfully");
				#endif
			}
			else
			{
				ValidationText = "ACCOUNT NAME OR PASSWORD IS INCORRECT";
				NotifyInvalidCredentials = true;
				NotifyInvalidCredentials = false;
			}
		}
		
		private bool TryLogin(string accountName, string accountPassword)
		{
			return accountName == "NoesisGUI" && accountPassword == "noesis";
		}
	}
}