#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
#else
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Windows.Media;
using System.Windows.Media.Imaging;
#endif

namespace SciFi
{
    public class Gun
    {
        public string Name { get; internal set; }
        public int Speed { get; internal set; }
        public int Accuracy { get; internal set; }
        public int Damage { get; internal set; }
        public int Ammo { get; internal set; }
        public bool Unlocked { get; internal set; }
        public ImageSource Image { get; internal set; }
    }

    public class ViewModel : INotifyPropertyChanged
    {
        public ViewModel()
        {
            Guns = new ObservableCollection<Gun>();

            Guns.Add(new Gun
            {
                Name = "Proton Phase Blaster", Speed = 8, Accuracy = 75, Damage = 993, Ammo = 50, Unlocked = true,
                Image = new BitmapImage(new Uri("pack://application:,,,/SciFi;component/Assets/NoesisGUI/Samples/SciFi/Images/HandGun2.png"))
            });
            Guns.Add(new Gun
            {
                Name = "Freeze Gun", Speed = 2, Accuracy = 48, Damage = 1428, Ammo = 20, Unlocked = true,
                Image = new BitmapImage(new Uri("pack://application:,,,/SciFi;component/Assets/NoesisGUI/Samples/SciFi/Images/FreezeGun.png"))
            });
            Guns.Add(new Gun
            {
                Name = "Fusion Ray Pistol", Speed = 6, Accuracy = 85, Damage = 657, Ammo = 100, Unlocked = true,
                Image = new BitmapImage(new Uri("pack://application:,,,/SciFi;component/Assets/NoesisGUI/Samples/SciFi/Images/HandGun1.png"))
            });
            Guns.Add(new Gun
            {
                Name = "Automatic Colt Revolver", Speed = 7, Accuracy = 80, Damage = 576, Ammo = 75, Unlocked = false,
                Image = new BitmapImage(new Uri("pack://application:,,,/SciFi;component/Assets/NoesisGUI/Samples/SciFi/Images/HandGun3.png"))
            });
            Guns.Add(new Gun
            {
                Name = "Proton Phase Blaster Plus", Speed = 9, Accuracy = 82, Damage = 1004, Ammo = 50, Unlocked = false,
                Image = new BitmapImage(new Uri("pack://application:,,,/SciFi;component/Assets/NoesisGUI/Samples/SciFi/Images/HandGun2.png"))
            });

            SelectedGun = Guns[0];
        }

        public ObservableCollection<Gun> Guns { get; private set; }

        private Gun _selectedGun;
        public Gun SelectedGun
        {
            get { return _selectedGun; }
            set
            {
                if (_selectedGun != value)
                {
                    _selectedGun = value;
                    OnPropertyChanged("SelectedGun");
                }
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName)
        {
            PropertyChangedEventHandler handler = PropertyChanged;
            if (handler != null)
            {
                handler(this, new PropertyChangedEventArgs(propertyName));
            }
        }
    }
}
