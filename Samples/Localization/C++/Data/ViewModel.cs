#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
using System.Collections.ObjectModel;
#else
using System;
using System.Windows;
using System.Collections.ObjectModel;
#endif

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
                    Resources = (ResourceDictionary)GUI.LoadXaml("Language-en.xaml")
                },

                new Language
                {
                    Name = "Français",
                    Resources = (ResourceDictionary)GUI.LoadXaml("Language-fr.xaml")
                },

                new Language
                {
                    Name = "日本語",
                    Resources = (ResourceDictionary)GUI.LoadXaml("Language-jp.xaml")
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

#if !NOESIS
        private static class GUI
        {
            public static object LoadXaml(string filename)
            {
                return Application.LoadComponent(new Uri(filename, UriKind.Relative));
            }
        }
#endif
    }
}
