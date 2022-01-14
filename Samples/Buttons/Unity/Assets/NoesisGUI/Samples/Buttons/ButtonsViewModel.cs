using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ButtonsViewModel : MonoBehaviour
{
    public NoesisEventCommand _startCommand;
    public NoesisEventCommand _settingsCommand;
    public NoesisEventCommand _exitCommand;

    public NoesisEventCommand StartCommand { get => _startCommand; }
    public NoesisEventCommand SettingsCommand { get => _settingsCommand; }
    public NoesisEventCommand ExitCommand { get => _exitCommand; }

    void Start()
    {
        NoesisView view = GetComponent<NoesisView>();
        view.Content.DataContext = this;
    }

    public void OnStart(object parameter)
    {
        Debug.Log("Start Game");
    }

    public void OnSettings(object parameter)
    {
        Debug.Log("Change Settings");
    }

    public void OnExit(object parameter)
    {
        Debug.Log("Exit Game");
    }
}
