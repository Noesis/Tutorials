using UnityEngine;
using Noesis;
using System.ComponentModel;

public class LoginViewModel : MonoBehaviour, INotifyPropertyChanged
{
    public string _account;
    public string _password;

    public NoesisEventCommand _loginCommand;
    public NoesisEventCommand LoginCommand { get => _loginCommand; }

    public string AccountName { get; set; }

    private string _message;
    public string Message
    {
        get => _message;
        set { if (_message != value) { _message = value; OnPropertyChanged("Message"); } }
    }

    void Reset()
    {
         _account = "noesis";
        _password = "12345";
    }

    void Start()
    {
        NoesisView view = GetComponent<NoesisView>();
        view.Content.DataContext = this;
    }

    // Update is called once per frame
    public void OnLogin(object parameter)
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
        if (AccountName != _account || password != _password)
        {
            Message = "ACCOUNT NAME OR PASSWORD IS INCORRECT";
            return false;
        }

        return true;
    }

    #region INotifyPropertyChanged
    public event PropertyChangedEventHandler PropertyChanged;

    void OnPropertyChanged(string name)
    {
        PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
    }
    #endregion
}
