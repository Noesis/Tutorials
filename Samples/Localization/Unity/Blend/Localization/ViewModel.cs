using System;
using System.Windows;
using System.Collections.ObjectModel;

namespace Localization
{
    public class Language
    {
        public string Name { get; set; }
        public ResourceDictionary Resources { get; set; }
    }

    public class ViewModel : NotifyPropertyChangedBase
    {
        public ViewModel()
        {
            Languages = new ObservableCollection<Language>()
            {
                new Language
                {
                    Name = "English",
                    Resources = (ResourceDictionary)Application.LoadComponent(new Uri("/Localization;component/Assets/NoesisGUI/Samples/Localization/Language-en.xaml", UriKind.Relative))
                },

                new Language
                {
                    Name = "Français",
                    Resources = (ResourceDictionary)Application.LoadComponent(new Uri("/Localization;component/Assets/NoesisGUI/Samples/Localization/Language-fr.xaml", UriKind.Relative))
                },

                new Language
                {
                    Name = "日本語",
                    Resources = (ResourceDictionary)Application.LoadComponent(new Uri("/Localization;component/Assets/NoesisGUI/Samples/Localization/Language-jp.xaml", UriKind.Relative))
                }
            };

            SelectedLanguage = Languages[0];

            SoundLevel = 100.0f;
            MusicLevel = 80.0f;
        }

        public ObservableCollection<Language> Languages { get; private set; }

        private Language _selectedLanguage;
        public Language SelectedLanguage
        {
            get { return _selectedLanguage; }
            set
            {
                if (_selectedLanguage != value)
                {
                    _selectedLanguage = value;
                    OnPropertyChanged("SelectedLanguage");
                }
            }
        }

        private float _soundLevel;
        public float SoundLevel
        {
            get { return _soundLevel; }
            set
            {
                if (_soundLevel != value)
                {
                    _soundLevel = value;
                    OnPropertyChanged("SoundLevel");
                }
            }
        }

        private float _musicLevel;
        public float MusicLevel
        {
            get { return _musicLevel; }
            set
            {
                if (_musicLevel != value)
                {
                    _musicLevel = value;
                    OnPropertyChanged("MusicLevel");
                }
            }
        }
    }
}
