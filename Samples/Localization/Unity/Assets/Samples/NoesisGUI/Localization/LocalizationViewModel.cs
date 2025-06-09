using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using UnityEngine;
using Noesis;

namespace Localization
{
    [Serializable]
    public class Language
    {
        public string _name;
        public string Name { get => _name; }

        public NoesisXaml _resources;
        private ResourceDictionary _resourceDictionary;
        public string Source
        {
            get
            {
                if (_resourceDictionary == null && _resources != null)
                {
                    _resourceDictionary = (ResourceDictionary)_resources.Load();
                }
                return _resources?.uri;
            }
        }

        public FlowDirection _flowDirection;
        public FlowDirection FlowDirection { get => _flowDirection; }
    }
}

public class LocalizationViewModel : MonoBehaviour, INotifyPropertyChanged
{
    public List<Localization.Language> _languages = new List<Localization.Language>();
    public List<Localization.Language> Languages { get => _languages; }

    private Localization.Language _selectedLanguage;
    public Localization.Language SelectedLanguage
    {
        get => _selectedLanguage;
        set { if (_selectedLanguage != value) { _selectedLanguage = value; OnPropertyChanged("SelectedLanguage"); } }
    }

    private float _soundLevel;
    public float SoundLevel
    {
        get => _soundLevel;
        set { if (_soundLevel != value) { _soundLevel = value; OnPropertyChanged("SoundLevel"); } }
    }

    private float _musicLevel;
    public float MusicLevel
    {
        get => _musicLevel;
        set { if (_musicLevel != value) { _musicLevel = value; OnPropertyChanged("MusicLevel"); } }
    }

    void Start()
    {
        SelectedLanguage = Languages.FirstOrDefault();

        SoundLevel = 100.0f;
        MusicLevel = 80.0f;

        NoesisView view = GetComponent<NoesisView>();
        view.Content.DataContext = this;
    }

    private void OnValidate()
    {
        _languages = new List<Localization.Language>(_languages);
        OnPropertyChanged("Languages");

        SelectedLanguage = Languages.FirstOrDefault();
    }

    #region INotifyPropertyChanged
    public event PropertyChangedEventHandler PropertyChanged;

    void OnPropertyChanged(string name)
    {
        PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
    }
    #endregion
}
