using System;
using System.Windows;
using System.Collections.ObjectModel;

namespace Localization
{
    public class Language
    {
        public string Name { get; set; }
        public Uri Source { get; set; }
        public FlowDirection FlowDirection { get; set; }
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
                    Source = new Uri("/Localization;component/Language-en.xaml", UriKind.Relative),
                    FlowDirection = FlowDirection.LeftToRight
                },

                new Language
                {
                    Name = "Français",
                    Source = new Uri("/Localization;component/Language-fr.xaml", UriKind.Relative),
                    FlowDirection = FlowDirection.LeftToRight
                },

                new Language
                {
                    Name = "日本語",
                    Source = new Uri("/Localization;component/Language-jp.xaml", UriKind.Relative),
                    FlowDirection = FlowDirection.LeftToRight
                },

                new Language
                {
                    Name = "عربي",
                    Source = new Uri("/Localization;component/Language-ar.xaml", UriKind.Relative),
                    FlowDirection = FlowDirection.RightToLeft
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
