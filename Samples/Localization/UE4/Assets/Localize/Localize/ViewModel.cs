#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
using System.Collections.ObjectModel;
#else
using System;
using System.Windows;
using System.Collections.ObjectModel;
using System.Windows.Media.Imaging;
#endif

namespace Localize
{
    public class Language
    {
        public string Name { get; set; }
        public string Culture { get; set; }
        public BitmapImage Flag { get; set; }
    }

    public class ViewModel : NotifyPropertyChangedBase
    {
        public ViewModel()
        {
            ChangeCulture = new DelegateCommand(OnChangeCulture);

            Languages = new ObservableCollection<Language>()
            {
                new Language
                {
                    Name = "English",
                    Culture = "en",
                    Flag = new BitmapImage(new Uri("pack://application:,,,/Localize;component/Localize/Flag-en.png", UriKind.RelativeOrAbsolute))
                },

                new Language
                {
                    Name = "Français",
                    Culture = "fr",
                    Flag = new BitmapImage(new Uri("pack://application:,,,/Localize;component/Localize/Flag-fr.png", UriKind.RelativeOrAbsolute))
                },

                new Language
                {
                    Name = "日本語",
                    Culture = "ja",
                    Flag = new BitmapImage(new Uri("pack://application:,,,/Localize;component/Localize/Flag-jp.png", UriKind.RelativeOrAbsolute))
                }
            };

            SelectedLanguage = Languages[0];

            SoundLevel = 100.0f;
            MusicLevel = 80.0f;
        }

        public DelegateCommand ChangeCulture { get; private set; }

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

        private void OnChangeCulture(object param)
        {
            Language language = param as Language;
            if (language != null)
            {

            }
        }
    }
}
