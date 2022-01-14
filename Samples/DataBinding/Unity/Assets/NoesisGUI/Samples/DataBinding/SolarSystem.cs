using System;
using System.Collections.Generic;
using System.ComponentModel;
using UnityEngine;

[Serializable]
public class SolarSystemObject
{
    public string _name;
    public string Name { get => _name; }

    public float _orbit;
    public float Orbit { get => _orbit; }

    public float _diameter;
    public float Diameter { get => _diameter; }

    public string _details;
    public string Details { get => _details; }

    public Texture2D _image;
    public Texture2D Image { get => _image; }
}

public class SolarSystem : MonoBehaviour, INotifyPropertyChanged
{
    public List<SolarSystemObject> _solarSystemObjects = new List<SolarSystemObject>();
    public List<SolarSystemObject> SolarSystemObjects { get => _solarSystemObjects; }

    private void Start()
    {
        NoesisView view = GetComponent<NoesisView>();
        view.Content.DataContext = this;
    }

    private void OnValidate()
    {
        _solarSystemObjects = new List<SolarSystemObject>(_solarSystemObjects);
        OnPropertyChanged("SolarSystemObjects");
    }

    #region INotifyPropertyChanged
    public event PropertyChangedEventHandler PropertyChanged;

    void OnPropertyChanged(string name)
    {
        PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
    }
    #endregion
}
