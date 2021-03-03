using System;
using System.Collections.ObjectModel;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace RadialMenu
{
    public class Weapon
    {
        public string Name { get; set; }
        public int Price { get; set; }
        public int Firepower { get; set; }
        public int FireRate { get; set; }
        public int Accuracy { get; set; }
        public int MovementRate { get; set; }
        public int Ammo { get; set; }
        public int Capacity { get; set; }
        public string Special { get; set; }
        public string Origin { get; set; }
        public ImageSource Icon { get; set; }
        public ImageSource Image { get; set; }
    }

    class ViewModel
    {
        public int BuyTimeLeft { get; set; }
        public int Money { get; set; }
        public ObservableCollection<Weapon> Weapons { get; private set; }

        public ViewModel()
        {
            BuyTimeLeft = 45;
            Money = 3250;

            Weapons = new ObservableCollection<Weapon>
            {
                new Weapon
                {
                    Name = "IDF Defender",
                    Price = 2000,
                    Firepower = 2,
                    FireRate = 7,
                    Accuracy = 2,
                    MovementRate = 7,
                    Ammo = 30,
                    Capacity = 90,
                    Special = "",
                    Origin = "Israel",
                    Icon = GetImage("IDF-Defender-Icon"),
                    Image = GetImage("IDF-Defender")
                },
                new Weapon
                {
                    Name = "FAMAS",
                    Price = 2250,
                    Firepower = 2,
                    FireRate = 8,
                    Accuracy = 6,
                    MovementRate = 7,
                    Ammo = 25,
                    Capacity = 90,
                    Special = "Burst-fire",
                    Origin = "France",
                    Icon = GetImage("FAMAS-Icon"),
                    Image = GetImage("FAMAS")
                },
                new Weapon
                {
                    Name = "AK-47",
                    Price = 2500,
                    Firepower = 3,
                    FireRate = 6,
                    Accuracy = 3,
                    MovementRate = 7,
                    Ammo = 30,
                    Capacity = 90,
                    Special = "",
                    Origin = "Rusia",
                    Icon = GetImage("AK-47-Icon"),
                    Image = GetImage("AK-47")
                },
                new Weapon
                {
                    Name = "M4A1",
                    Price = 3100,
                    Firepower = 2,
                    FireRate = 7,
                    Accuracy = 5,
                    MovementRate = 8,
                    Ammo = 30,
                    Capacity = 90,
                    Special = "Silencer",
                    Origin = "U.S.A.",
                    Icon = GetImage("M4A1-Icon"),
                    Image = GetImage("M4A1")
                },
                new Weapon
                {
                    Name = "AUG",
                    Price = 3300,
                    Firepower = 2,
                    FireRate = 6,
                    Accuracy = 5,
                    MovementRate = 7,
                    Ammo = 30,
                    Capacity = 90,
                    Special = "Silencer",
                    Origin = "Austria",
                    Icon = GetImage("AUG-Icon"),
                    Image = GetImage("AUG")
                },
                new Weapon
                {
                    Name = "Krieg 552",
                    Price = 3500,
                    Firepower = 3,
                    FireRate = 7,
                    Accuracy = 5,
                    MovementRate = 6,
                    Ammo = 30,
                    Capacity = 90,
                    Special = "Silencer",
                    Origin = "Switzerland",
                    Icon = GetImage("Krieg-552-Icon"),
                    Image = GetImage("Krieg-552")
                }
            };
        }

        private ImageSource GetImage(string name)
        {
            return new BitmapImage(new Uri(BaseUri + "Images/Weapons/" + name + ".png"));
        }

        private readonly string BaseUri = "pack://application:,,,/RadialMenu;component/RadialMenu/";
    }
}
