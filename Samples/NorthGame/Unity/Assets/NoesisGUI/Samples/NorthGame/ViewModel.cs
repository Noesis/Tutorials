#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
using System.Collections.Generic;
using System.ComponentModel;
using System.Windows.Input;
#else
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
#endif

namespace NorthGame
{
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
                if (value == null || !Weapons.Contains(value))
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
        Discover,
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
        private string _name;
        public string Name
        {
            get { return _name; }
            set
            {
                if (_name != value)
                {
                    _name = value;
                    OnPropertyChanged("Name");
                }
            }
        }

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
                }
            }
        }

        private int _strength;
        public int Strength
        {
            get { return _strength; }
            set
            {
                if (_strength != value)
                {
                    _strength = value;
                    OnPropertyChanged("Strength");
                }
            }
        }

        private int _dexterity;
        public int Dexterity
        {
            get { return _dexterity; }
            set
            {
                if (_dexterity != value)
                {
                    _dexterity = value;
                    OnPropertyChanged("Dexterity");
                }
            }
        }

        private int _constitution;
        public int Constitution
        {
            get { return _constitution; }
            set
            {
                if (_constitution != value)
                {
                    _constitution = value;
                    OnPropertyChanged("Constitution");
                }
            }
        }

        private int _intelligence;
        public int Intelligence
        {
            get { return _intelligence; }
            set
            {
                if (_intelligence != value)
                {
                    _intelligence = value;
                    OnPropertyChanged("Intelligence");
                }
            }
        }

        private int _wisdom;
        public int Wisdom
        {
            get { return _wisdom; }
            set
            {
                if (_wisdom != value)
                {
                    _wisdom = value;
                    OnPropertyChanged("Wisdom");
                }
            }
        }

        private int _charisma;
        public int Charisma
        {
            get { return _charisma; }
            set
            {
                if (_charisma != value)
                {
                    _charisma = value;
                    OnPropertyChanged("Charisma");
                }
            }
        }

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

        private Location _selectedLocation;
        public Location SelectedLocation
        {
            get { return _selectedLocation; }
            set
            {
                if (_selectedLocation != value)
                {
                    _selectedLocation = value;
                    OnPropertyChanged("SelectedLocation");
                }
            }
        }

        public PlayerInfo() { WeaponCategories = new List<WeaponCategory>(); }
    }

    public class ViewModel : NotifyPropertyChangedBase
    {
        public ICommand MenuCommand { get; private set; }
        public ICommand PlayCommand { get; private set; }
        public ICommand OptionsCommand { get; private set; }
        public ICommand QuitCommand { get; private set; }

        public ICommand FadeCompletedCommand { get; private set; }
        public ICommand SlideCompletedCommand { get; private set; }

        public List<Race> Races { get; private set; }

        public List<Location> Locations { get; private set; }

        public PlayerInfo Player { get; private set; }

        private State _state;
        public State State
        {
            get { return _state; }
            private set
            {
                if (_state != value)
                {
                    _state = value;
                    OnPropertyChanged("State");
                }
            }
        }

        private int _newMessages;
        public int NewMessages
        {
            get { return _newMessages; }
            private set
            {
                if (_newMessages != value)
                {
                    _newMessages = value;
                    OnPropertyChanged("NewMessages");
                }
            }
        }

        private int _credits;
        public int Credits
        {
            get { return _credits; }
            private set
            {
                if (_credits != value)
                {
                    _credits = value;
                    OnPropertyChanged("Credits");
                }
            }
        }

        private string _nextGame;
        public string NextGame
        {
            get { return _nextGame; }
            private set
            {
                if (_nextGame != value)
                {
                    _nextGame = value;
                    OnPropertyChanged("NextGame");
                }
            }
        }

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

        private PlayScreenDirection _playScreenDirection;
        public PlayScreenDirection PlayScreenDirection
        {
            get { return _playScreenDirection; }
            set
            {
                if (_playScreenDirection != value)
                {
                    _playScreenDirection = value;
                    OnPropertyChanged("PlayScreenDirection");
                }
            }
        }

        public ViewModel(FrameworkElement root)
        {
            MenuCommand = new DelegateCommand(OnMenu);
            PlayCommand = new DelegateCommand(OnPlay);
            OptionsCommand = new DelegateCommand(OnOptions);
            QuitCommand = new DelegateCommand(OnQuit);

            FadeCompletedCommand = new DelegateCommand(OnFadeCompleted);
            SlideCompletedCommand = new DelegateCommand(OnSlideCompleted);

            Race human = new Race { Name = "Human" };
            human.Classes.Add(new RaceClass { Name = "Knight", Image = ImagePath("ClassHumanKnight.png") });
            human.Classes.Add(new RaceClass { Name = "Cleric", Image = ImagePath("ClassHumanCleric.png") });
            human.Classes.Add(new RaceClass { Name = "Thief", Image = ImagePath("ClassHumanThief.png") });

            Race orc = new Race { Name = "Orc" };
            orc.Classes.Add(new RaceClass { Name = "Warrior", Image = ImagePath("ClassOrcWarrior.png") });
            orc.Classes.Add(new RaceClass { Name = "Hunter", Image = ImagePath("ClassOrcHunter.png") });
            orc.Classes.Add(new RaceClass { Name = "Shaman", Image = ImagePath("ClassOrcShaman.png") });

            Race elf = new Race { Name = "Elf" };
            elf.Classes.Add(new RaceClass { Name = "Ranger", Image = ImagePath("ClassElfRanger.png") });
            elf.Classes.Add(new RaceClass { Name = "Priest", Image = ImagePath("ClassElfPriest.png") });
            elf.Classes.Add(new RaceClass { Name = "Wizard", Image = ImagePath("ClassElfWizard.png") });

            Races = new List<Race> { human, orc, elf };

            WeaponCategory closeRange = new WeaponCategory { Name = "Close Range" };
            closeRange.Weapons.Add(new Weapon { Name = "Double Axe", Image = ImagePath("WeaponDoubleAxe.png") });
            closeRange.Weapons.Add(new Weapon { Name = "Long Sword", Image = ImagePath("WeaponLongSword.png") });
            closeRange.Weapons.Add(new Weapon { Name = "Hand Axe", Image = ImagePath("WeaponHandAxe.png") });
            closeRange.Weapons.Add(new Weapon { Name = "Hammer", Image = ImagePath("WeaponHammer.png") });
            closeRange.Weapons.Add(new Weapon { Name = "Mace", Image = ImagePath("WeaponMace.png") });
            closeRange.SelectedWeapon = closeRange.Weapons[0];

            WeaponCategory longRange = new WeaponCategory { Name = "Long Range" };
            longRange.Weapons.Add(new Weapon { Name = "Long Bow", Image = ImagePath("WeaponLongSword.png") });
            longRange.Weapons.Add(new Weapon { Name = "Crossbow", Image = ImagePath("WeaponDoubleAxe.png") });
            longRange.Weapons.Add(new Weapon { Name = "Sling", Image = ImagePath("WeaponLongSword.png") });
            longRange.Weapons.Add(new Weapon { Name = "Spear", Image = ImagePath("WeaponDoubleAxe.png") });
            longRange.SelectedWeapon = longRange.Weapons[0];

            WeaponCategory armor = new WeaponCategory { Name = "Armor" };
            armor.Weapons.Add(new Weapon { Name = "Shield", Image = ImagePath("WeaponDoubleAxe.png") });
            armor.Weapons.Add(new Weapon { Name = "Leather Armor", Image = ImagePath("WeaponLongSword.png") });
            armor.Weapons.Add(new Weapon { Name = "Scale Mail", Image = ImagePath("WeaponDoubleAxe.png") });
            armor.Weapons.Add(new Weapon { Name = "Breastplate", Image = ImagePath("WeaponLongSword.png") });
            armor.SelectedWeapon = armor.Weapons[0];

            WeaponCategory magic = new WeaponCategory { Name = "Magic" };
            magic.Weapons.Add(new Weapon { Name = "Staff", Image = ImagePath("WeaponLongSword.png") });
            magic.Weapons.Add(new Weapon { Name = "Ring", Image = ImagePath("WeaponDoubleAxe.png") });
            magic.Weapons.Add(new Weapon { Name = "Amulet", Image = ImagePath("WeaponLongSword.png") });
            magic.Weapons.Add(new Weapon { Name = "Spell Book", Image = ImagePath("WeaponDoubleAxe.png") });
            magic.SelectedWeapon = magic.Weapons[0];

            Locations = new List<Location>();
            Locations.Add(new Location { Name = "The Spark Range", Members = 45, Type = RaidType.Arena, Difficulty = RaidDifficulty.Easy, Image = ImagePath("Location1.jpg") });
            Locations.Add(new Location { Name = "Frirf Woods", Members = 20, Type = RaidType.Defend, Difficulty = RaidDifficulty.Normal, Image = ImagePath("Location2.jpg") });
            Locations.Add(new Location { Name = "The Ymart Plains", Members = 30, Type = RaidType.Discover, Difficulty = RaidDifficulty.Normal, Image = ImagePath("Location3.jpg") });
            Locations.Add(new Location { Name = "Rusty Wallaby Grove", Members = 5, Type = RaidType.Defend, Difficulty = RaidDifficulty.Hard, Image = ImagePath("Location4.jpg") });
            Locations.Add(new Location { Name = "Sapphire Shallows", Members = 40, Type = RaidType.Arena, Difficulty = RaidDifficulty.Easy, Image = ImagePath("Location5.jpg") });
            Locations.Add(new Location { Name = "The Seagrass Islet", Members = 25, Type = RaidType.Discover, Difficulty = RaidDifficulty.Normal, Image = ImagePath("Location6.jpg") });
            Locations.Add(new Location { Name = "The Spark Range", Members = 45, Type = RaidType.Arena, Difficulty = RaidDifficulty.Easy, Image = ImagePath("Location1.jpg") });
            Locations.Add(new Location { Name = "Frirf Woods", Members = 20, Type = RaidType.Defend, Difficulty = RaidDifficulty.Normal, Image = ImagePath("Location2.jpg") });
            Locations.Add(new Location { Name = "The Ymart Plains", Members = 30, Type = RaidType.Discover, Difficulty = RaidDifficulty.Normal, Image = ImagePath("Location3.jpg") });
            Locations.Add(new Location { Name = "Rusty Wallaby Grove", Members = 5, Type = RaidType.Defend, Difficulty = RaidDifficulty.Hard, Image = ImagePath("Location4.jpg") });
            Locations.Add(new Location { Name = "Sapphire Shallows", Members = 40, Type = RaidType.Arena, Difficulty = RaidDifficulty.Easy, Image = ImagePath("Location5.jpg") });
            Locations.Add(new Location { Name = "The Seagrass Islet", Members = 25, Type = RaidType.Discover, Difficulty = RaidDifficulty.Normal, Image = ImagePath("Location6.jpg") });

            Player = new PlayerInfo
            {
                Name = "Highlander",
                Race = Races[0],
                Class = Races[0].Classes[0],
                Strength = 87,
                Dexterity = 60,
                Constitution = 91,
                Intelligence = 45,
                Wisdom = 32,
                Charisma = 56
            };

            Player.WeaponCategories.Add(closeRange);
            Player.WeaponCategories.Add(longRange);
            Player.WeaponCategories.Add(armor);
            Player.WeaponCategories.Add(magic);
            Player.SelectedCategory = Player.WeaponCategories[0];
            Player.SelectedLocation = Locations[0];

            PlayScreens = new List<string> { "Select", "Equip", "Raid", "Fight" };

            NewMessages = 7;
            Credits = 386500;
            NextGame = "23-03-2018 8:25PM";

            _container1 = (Border)root.FindName("Container1");
            _container2 = (Border)root.FindName("Container2");

            OnMenu(null);
        }

        private void OnMenu(object param)
        {
            _container2.Child = new Menu();
            State = State.Menu;

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

            play.UpdateLayout();

            _playContainer1 = (Border)play.Template.FindName("PlayContainer1", play);
            _playContainer2 = (Border)play.Template.FindName("PlayContainer2", play);
        }

        private void OnOptions(object param)
        {
            //+State = State.Options;
        }

        private void OnQuit(object param)
        {
#if NOESIS
            UnityEngine.Application.Quit();
#else
            Application.Current.Shutdown();
#endif
        }

        private void OnFadeCompleted(object param)
        {
            UIElement target = (UIElement)param;
            if (target == null)
            {
                return;
            }

#if NOESIS
            if (target.IsEnabled)
            {
                // swap new content to the front container
                SwapContent(_container2, _container1);

                // focus target
                target.Focus();
            }
#else
            if (!target.IsEnabled)
            {
                // swap new content to the front container
                SwapContent(_container2, _container1);

                // focus target
                target.Dispatcher.BeginInvoke(new Action(() =>
                {
                    target.Focus();
                }));

                // load play screen
                if (State == State.Play)
                {
                    SelectedPlayScreen = 0;
                }
            }
#endif
        }

        private void OnSlideCompleted(object param)
        {
            UIElement target = (UIElement)param;
            if (target == null)
            {
                return;
            }

#if NOESIS
            if (target.IsEnabled)
            {
                SwapContent(_playContainer2, _playContainer1);
            }
#else
            if (!target.IsEnabled)
            {
                SwapContent(_playContainer2, _playContainer1);
            }
#endif
        }

        private void ShowPlayScreen(int oldScreenIndex, int newScreenIndex)
        {
            if (newScreenIndex >= 0 && newScreenIndex < PlayScreens.Count)
            {
                _playContainer2.Child = CreatePlayScreen(newScreenIndex);

                PlayScreenDirection = oldScreenIndex < newScreenIndex ? PlayScreenDirection.Next : PlayScreenDirection.Prev;
                PlayScreenDirection = PlayScreenDirection.Current;
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

        private void SwapContent(Border src, Border dst)
        {
            FrameworkElement content = (FrameworkElement)src.Child;
            content.DataContext = this;
            src.Child = null;
            dst.Child = content;
            content.ClearValue(FrameworkElement.DataContextProperty);
        }

        private Border _container1;
        private Border _container2;

        private Border _playContainer1;
        private Border _playContainer2;

#if NOESIS
        private string ImagePath(string name)
        {
            return "Assets/NoesisGUI/Samples/NorthGame/Images/" + name;
        }
#else
        private string ImagePath(string name)
        {
            return "Images/" + name;
        }
#endif
    }
}
