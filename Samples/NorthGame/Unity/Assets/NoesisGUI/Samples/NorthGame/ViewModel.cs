#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
using System;
using System.Collections.Generic;
using System.Windows.Input;
#else
using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media.Animation;
#endif

namespace NorthGame
{
    public static class Randomizer
    {
        public static Random r = new Random(DateTime.Now.Ticks.GetHashCode());
    }

    public enum State
    {
        Menu,
        Play,
        Options
    }

    public enum PlayScreenDirection
    {
        Current,
        Next,
        Prev
    }

    public class Race
    {
        public string Name { get; set; }
        public List<RaceClass> Classes { get; private set; }

        public Race() { Classes = new List<RaceClass>(); }

        public override string ToString() { return Name; }
    }

    public class RaceClass
    {
        public string Name { get; set; }
        public string Image { get; set; }
    }

    public class WeaponCategory : NotifyPropertyChangedBase
    {
        public string Name { get; set; }
        public List<Weapon> Weapons { get; set; }

        private Weapon _selectedWeapon;
        public Weapon SelectedWeapon
        {
            get { return _selectedWeapon; }
            set
            {
                if (!Weapons.Contains(value))
                {
                    return;
                }

                if (_selectedWeapon != value)
                {
                    _selectedWeapon = value;
                    OnPropertyChanged("SelectedWeapon");
                }
            }
        }

        public WeaponCategory() { Weapons = new List<Weapon>(); }

        public override string ToString() { return Name; }
    }

    public class Weapon
    {
        public string Name { get; set; }
        public string Image { get; set; }
    }

    public enum RaidType
    {
        Arena,
        Explore,
        Defend
    }

    public enum RaidDifficulty
    {
        Easy,
        Normal,
        Hard
    }

    public class Location
    {
        public string Name { get; set; }
        public int Members { get; set; }
        public RaidType Type { get; set; }
        public RaidDifficulty Difficulty { get; set; }
        public string Image { get; set; }
    }

    public class PlayerInfo : NotifyPropertyChangedBase
    {
        public string Name { get;  set; }

        private Race _race;
        public Race Race
        {
            get { return _race; }
            set
            {
                if (_race != value)
                {
                    _race = value;
                    Class = _race.Classes[0];
                    OnPropertyChanged("Race");
                }
            }
        }

        private RaceClass _class;
        public RaceClass Class
        {
            get { return _class; }
            set
            {
                if (_class != value)
                {
                    _class = value;
                    OnPropertyChanged("Class");

                    GenerateAttributes();
                }
            }
        }

        private void GenerateAttributes()
        {
            Strength = Randomizer.r.Next(40, 100);
            Dexterity = Randomizer.r.Next(40, 100);
            Constitution = Randomizer.r.Next(40, 100);
            Intelligence = Randomizer.r.Next(40, 100);
            Wisdom = Randomizer.r.Next(40, 100);
            Charisma = Randomizer.r.Next(40, 100);
        }

        public int Strength { get; set; }
        public int Dexterity { get; set; }
        public int Constitution { get; set; }
        public int Intelligence { get; set; }
        public int Wisdom { get; set; }
        public int Charisma { get; set; }

        public List<WeaponCategory> WeaponCategories { get; private set; }

        private WeaponCategory _selectedCategory;
        public WeaponCategory SelectedCategory
        {
            get { return _selectedCategory; }
            set
            {
                if (_selectedCategory != value)
                {
                    _selectedCategory = value;
                    OnPropertyChanged("SelectedCategory");
                }
            }
        }

        public Location SelectedLocation { get; set; }

        public int Initiative { get; set; }
        public int Wins { get; set; }
        public int Losses { get; set; }
        public int WinPercentage { get { return (int)(100 * Wins / (float)(Wins + Losses)); } }
        public string WinRecord { get { return string.Format("{0} ({1}%)", Wins, WinPercentage); } }

        public int Odds { get; set; }

        public PlayerInfo() { WeaponCategories = new List<WeaponCategory>(); }
    }

    public class ViewModel : NotifyPropertyChangedBase
    {
        public ICommand MenuCommand { get; private set; }
        public ICommand PlayCommand { get; private set; }
        public ICommand OptionsCommand { get; private set; }
        public ICommand QuitCommand { get; private set; }
        public ICommand FightCommand { get; private set; }

        public ICommand PrevCommand { get; private set; }
        public ICommand NextCommand { get; private set; }

        public ICommand FadeCompletedCommand { get; private set; }
        public ICommand SlideCompletedCommand { get; private set; }

        public List<Race> Races { get; private set; }

        public List<Location> Locations { get; private set; }

        public PlayerInfo Player { get; private set; }

        public PlayerInfo Opponent { get; private set; }

        public int Initiative { get { return (int)(100.0f * Player.Initiative / (float)(Player.Initiative + Opponent.Initiative)); } }

        public State State { get; private set; }

        public int NewMessages { get; private set; }

        public int Credits { get; private set; }

        public string NextGame { get; private set; }

        public List<string> PlayScreens { get; private set; }

        private int _selectedPlayScreen = -1;
        public int SelectedPlayScreen
        {
            get { return _selectedPlayScreen; }
            set
            {
                if (_selectedPlayScreen != value)
                {
                    int oldPlayScreen = _selectedPlayScreen;

                    _selectedPlayScreen = value;
                    OnPropertyChanged("SelectedPlayScreen");

                    ShowPlayScreen(oldPlayScreen, _selectedPlayScreen);
                }
            }
        }

        public PlayScreenDirection PlayScreenDirection { get; private set; }

        public ViewModel(FrameworkElement root)
        {
            MenuCommand = new DelegateCommand(OnMenu);
            PlayCommand = new DelegateCommand(OnPlay);
            OptionsCommand = new DelegateCommand(OnOptions);
            QuitCommand = new DelegateCommand(OnQuit);
            FightCommand = new DelegateCommand(OnFight);

            PrevCommand = new DelegateCommand(OnPrev);
            NextCommand = new DelegateCommand(OnNext);

            FadeCompletedCommand = new DelegateCommand(OnFadeCompleted);
            SlideCompletedCommand = new DelegateCommand(OnSlideCompleted);

            Race human = new Race { Name = "Human" };
            human.Classes.Add(new RaceClass { Name = "Knight", Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/ClassHumanKnight.png" });
            human.Classes.Add(new RaceClass { Name = "Thief", Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/ClassHumanThief.png" });
            human.Classes.Add(new RaceClass { Name = "Cleric", Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/ClassHumanCleric.png" });

            Race orc = new Race { Name = "Orc" };
            orc.Classes.Add(new RaceClass { Name = "Warrior", Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/ClassOrcWarrior.png" });
            orc.Classes.Add(new RaceClass { Name = "Hunter", Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/ClassOrcHunter.png" });
            orc.Classes.Add(new RaceClass { Name = "Shaman", Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/ClassOrcShaman.png" });

            Race elf = new Race { Name = "Elf" };
            elf.Classes.Add(new RaceClass { Name = "Ranger", Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/ClassElfRanger.png" });
            elf.Classes.Add(new RaceClass { Name = "Priest", Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/ClassElfPriest.png" });
            elf.Classes.Add(new RaceClass { Name = "Wizard", Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/ClassElfWizard.png" });

            Races = new List<Race> { human, orc, elf };

            WeaponCategory closeRange = new WeaponCategory { Name = "Close Range" };
            closeRange.Weapons.Add(new Weapon { Name = "Double Axe", Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/WeaponDoubleAxe.png" });
            closeRange.Weapons.Add(new Weapon { Name = "Long Sword", Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/WeaponLongSword.png" });
            closeRange.Weapons.Add(new Weapon { Name = "Hand Axe", Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/WeaponHandAxe.png" });
            closeRange.Weapons.Add(new Weapon { Name = "Double Sword", Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/WeaponDoubleSword.png" });
            closeRange.Weapons.Add(new Weapon { Name = "Mace", Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/WeaponMace.png" });
            closeRange.SelectedWeapon = closeRange.Weapons[0];

            WeaponCategory longRange = new WeaponCategory { Name = "Long Range" };
            longRange.Weapons.Add(new Weapon { Name = "Long Bow", Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/WeaponLongBow.png" });
            longRange.Weapons.Add(new Weapon { Name = "Crossbow", Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/WeaponCrossbow.png" });
            longRange.Weapons.Add(new Weapon { Name = "Sling", Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/WeaponSling.png" });
            longRange.Weapons.Add(new Weapon { Name = "Spear", Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/WeaponSpear.png" });
            longRange.SelectedWeapon = longRange.Weapons[0];

            WeaponCategory armor = new WeaponCategory { Name = "Armor" };
            armor.Weapons.Add(new Weapon { Name = "Round Shield", Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/WeaponRoundShield.png" });
            armor.Weapons.Add(new Weapon { Name = "Chain Mail", Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/WeaponChainMail.png" });
            armor.Weapons.Add(new Weapon { Name = "Big Shield", Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/WeaponBigShield.png" });
            armor.Weapons.Add(new Weapon { Name = "Breastplate", Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/WeaponBreastplate.png" });
            armor.Weapons.Add(new Weapon { Name = "Helmet", Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/WeaponHelmet.png" });
            armor.SelectedWeapon = armor.Weapons[0];

            WeaponCategory magic = new WeaponCategory { Name = "Magic" };
            magic.Weapons.Add(new Weapon { Name = "Wand", Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/WeaponWand.png" });
            magic.Weapons.Add(new Weapon { Name = "Staff", Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/WeaponStaff.png" });
            magic.Weapons.Add(new Weapon { Name = "Spell Book", Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/WeaponSpellBook.png" });
            magic.SelectedWeapon = magic.Weapons[0];

            Locations = new List<Location>();
            Locations.Add(new Location { Name = "The Spark Range", Members = 45, Type = RaidType.Defend, Difficulty = RaidDifficulty.Hard, Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/Location1.jpg" });
            Locations.Add(new Location { Name = "Frirf Woods", Members = 20, Type = RaidType.Explore, Difficulty = RaidDifficulty.Easy, Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/Location2.jpg" });
            Locations.Add(new Location { Name = "The Ymart Plains", Members = 30, Type = RaidType.Arena, Difficulty = RaidDifficulty.Normal, Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/Location3.jpg" });
            Locations.Add(new Location { Name = "Rusty Wallaby Grove", Members = 5, Type = RaidType.Defend, Difficulty = RaidDifficulty.Normal, Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/Location4.jpg" });
            Locations.Add(new Location { Name = "Sapphire Shallows", Members = 40, Type = RaidType.Arena, Difficulty = RaidDifficulty.Hard, Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/Location5.jpg" });
            Locations.Add(new Location { Name = "The Seagrass Islet", Members = 25, Type = RaidType.Explore, Difficulty = RaidDifficulty.Easy, Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/Location6.jpg" });
            Locations.Add(new Location { Name = "The Spark Range", Members = 45, Type = RaidType.Arena, Difficulty = RaidDifficulty.Easy, Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/Location1.jpg" });
            Locations.Add(new Location { Name = "Frirf Woods", Members = 20, Type = RaidType.Defend, Difficulty = RaidDifficulty.Normal, Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/Location2.jpg" });
            Locations.Add(new Location { Name = "The Ymart Plains", Members = 30, Type = RaidType.Explore, Difficulty = RaidDifficulty.Normal, Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/Location3.jpg" });
            Locations.Add(new Location { Name = "Rusty Wallaby Grove", Members = 5, Type = RaidType.Defend, Difficulty = RaidDifficulty.Hard, Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/Location4.jpg" });
            Locations.Add(new Location { Name = "Sapphire Shallows", Members = 40, Type = RaidType.Arena, Difficulty = RaidDifficulty.Easy, Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/Location5.jpg" });
            Locations.Add(new Location { Name = "The Seagrass Islet", Members = 25, Type = RaidType.Explore, Difficulty = RaidDifficulty.Normal, Image = "pack://application:,,,/Assets/NoesisGUI/Samples/NorthGame/Images/Location6.jpg" });

            Player = new PlayerInfo
            {
                Name = "Highlander",
                Race = Races[0],
                Class = Races[0].Classes[0],
                Initiative = Randomizer.r.Next(50, 150),
                Wins = Randomizer.r.Next(20, 30),
                Losses = Randomizer.r.Next(1, 10),
                Odds = Randomizer.r.Next(80, 120)
            };

            Race opponentRace = Races[Randomizer.r.Next(0, 2)];
            string[] opponentNames = { "Khorlsendukr", "Nettala", "Belarlug", "Kumar", "Jiduaz", "Nazzous", "Ookhin", "Gunaq" };
            Opponent = new PlayerInfo
            {
                Name = opponentNames[Randomizer.r.Next(0, 7)],
                Race = opponentRace,
                Class = opponentRace.Classes[Randomizer.r.Next(0, 2)],
                Initiative = Randomizer.r.Next(50, 150),
                Wins = Randomizer.r.Next(50, 100),
                Losses = Randomizer.r.Next(20,50),
                Odds = Randomizer.r.Next(80, 120)
            };

            Player.WeaponCategories.Add(closeRange);
            Player.WeaponCategories.Add(longRange);
            Player.WeaponCategories.Add(armor);
            Player.WeaponCategories.Add(magic);
            Player.SelectedCategory = Player.WeaponCategories[0];
            Player.SelectedLocation = Locations[0];

            PlayScreens = new List<string> { "Select", "Equip", "Raid", "Fight" };
            PlayScreenDirection = PlayScreenDirection.Current;

            NewMessages = Randomizer.r.Next(3, 8);
            Credits = Randomizer.r.Next(30000, 80000);
            NextGame = string.Format("{0} mins", Randomizer.r.Next(20, 50));

            _container1 = (Border)root.FindName("Container1");
            _container2 = (Border)root.FindName("Container2");

            OnMenu(null);
        }

        private void OnMenu(object param)
        {
            _container2.Child = new Menu();
            State = State.Menu;
            OnPropertyChanged("State");

            _playContainer1 = null;
            _playContainer2 = null;

            SelectedPlayScreen = -1;
        }

        private void OnPlay(object param)
        {
            Player.SelectedCategory = Player.WeaponCategories[0];
            Player.SelectedLocation = Locations[0];

            Play play = new Play();
            _container2.Child = play;
            State = State.Play;
            OnPropertyChanged("State");

            play.UpdateLayout();

            _playContainer1 = (Border)play.FindName("PlayContainer1");
            _playContainer2 = (Border)play.FindName("PlayContainer2");
        }

        private void OnOptions(object param)
        {
            //+State = State.Options;
            //+OnPropertyChanged("State");

#if NOESIS
            UnityEngine.Debug.Log("Options screen");
#else
            Console.WriteLine("Options screen");
#endif
        }

        private void OnQuit(object param)
        {
#if NOESIS
            UnityEngine.Debug.Log("Quit game");
            UnityEngine.Application.Quit();
#else
            Application.Current.Shutdown();
#endif
        }

        private void OnFight(object param)
        {
#if NOESIS
            UnityEngine.Debug.Log("Fight!");
#else
            Console.WriteLine("Fight!");
#endif
        }

        private void OnPrev(object param)
        {
            if (SelectedPlayScreen == 0)
            {
                OnMenu(param);
            }
            else
            {
                SelectedPlayScreen--;
            }
        }

        private void OnNext(object param)
        {
            if (SelectedPlayScreen < PlayScreens.Count - 1)
            {
                SelectedPlayScreen++;
            }
            else
            {
                OnFight(param);
            }
        }

        private void OnFadeCompleted(object param)
        {
            SwapContent(_container2, _container1);
        }

        private void OnSlideCompleted(object param)
        {
            SwapContent(_playContainer2, _playContainer1);
        }

        private void SwapContent(Border src, Border dst)
        {
            FrameworkElement content = (FrameworkElement)src.Child;
            content.DataContext = this;
            src.Child = null;
            dst.Child = content;
            content.ClearValue(FrameworkElement.DataContextProperty);
        }

        private void ShowPlayScreen(int oldScreenIndex, int newScreenIndex)
        {
            if (newScreenIndex >= 0 && newScreenIndex < PlayScreens.Count)
            {
                FrameworkElement screen = CreatePlayScreen(newScreenIndex);
                _playContainer2.Child = screen;
                screen.UpdateLayout();

                if (oldScreenIndex < newScreenIndex)
                {
                    PlayScreenDirection = PlayScreenDirection.Next;
                }
                else
                {
                    PlayScreenDirection = PlayScreenDirection.Prev;
                }
                OnPropertyChanged("PlayScreenDirection");

                PlayScreenDirection = PlayScreenDirection.Current;
                OnPropertyChanged("PlayScreenDirection");

                Player.SelectedLocation = Locations[0];
            }
        }

        private FrameworkElement CreatePlayScreen(int screenIndex)
        {
            switch (screenIndex)
            {
                case 0: return new SelectScreen();
                case 1: return new EquipScreen();
                case 2: return new RaidScreen();
                case 3: return new FightScreen();
            }

            return null;
        }

        private Border _container1;
        private Border _container2;

        private Border _playContainer1;
        private Border _playContainer2;
    }
}
