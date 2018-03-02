using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.ComponentModel;

public class ViewModel : MonoBehaviour, INotifyPropertyChanged
{
    public Light redLight;
    public Light greenLight;

    private bool _redLightOn = false;
    public bool RedLightOn
    {
        get { return _redLightOn; }
        set
        {
            if (_redLightOn != value)
            {
                _redLightOn = value;
                OnPropertyChanged("RedLightOn");

                redLight.enabled = _redLightOn;
            }
        }
    }

    private float _redLightIntensity = 1f;
    public float RedLightIntensity
    {
        get { return _redLightIntensity; }
        set
        {
            if (_redLightIntensity != value)
            {
                _redLightIntensity = value;
                OnPropertyChanged("RedLightIntensity");

                redLight.intensity = _redLightIntensity;
            }
        }
    }

    private bool _greenLightOn = false;
    public bool GreenLightOn
    {
        get { return _greenLightOn; }
        set
        {
            if (_greenLightOn != value)
            {
                _greenLightOn = value;
                OnPropertyChanged("GreenLightOn");

                greenLight.enabled = _greenLightOn;
            }
        }
    }

    private float _greenLightIntensity = 1f;
    public float GreenLightIntensity
    {
        get { return _greenLightIntensity; }
        set
        {
            if (_greenLightIntensity != value)
            {
                _greenLightIntensity = value;
                OnPropertyChanged("GreenLightIntensity");

                greenLight.intensity = _greenLightIntensity;
            }
        }
    }

    private void Start()
    {
        NoesisView view = GetComponent<NoesisView>();
        view.Content.DataContext = this;
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
