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
using System.Windows.Media.Animation;
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
                }
            }
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
            FightCommand = new DelegateCommand(OnFight);

            PrevCommand = new DelegateCommand(OnPrev);
            NextCommand = new DelegateCommand(OnNext);

            FadeCompletedCommand = new DelegateCommand(OnFadeCompleted);
            SlideCompletedCommand = new DelegateCommand(OnSlideCompleted);

            Race human = new Race { Name = "Human" };
            human.Classes.Add(new RaceClass { Name = "Knight", Image = ImagePath("ClassHumanKnight.png") });
            human.Classes.Add(new RaceClass { Name = "Thief", Image = ImagePath("ClassHumanThief.png") });
            human.Classes.Add(new RaceClass { Name = "Cleric", Image = ImagePath("ClassHumanCleric.png") });

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
            closeRange.Weapons.Add(new Weapon { Name = "Double Sword", Image = ImagePath("WeaponDoubleSword.png") });
            closeRange.Weapons.Add(new Weapon { Name = "Mace", Image = ImagePath("WeaponMace.png") });
            closeRange.SelectedWeapon = closeRange.Weapons[0];

            WeaponCategory longRange = new WeaponCategory { Name = "Long Range" };
            longRange.Weapons.Add(new Weapon { Name = "Long Bow", Image = ImagePath("WeaponLongBow.png") });
            longRange.Weapons.Add(new Weapon { Name = "Crossbow", Image = ImagePath("WeaponCrossbow.png") });
            longRange.Weapons.Add(new Weapon { Name = "Sling", Image = ImagePath("WeaponSling.png") });
            longRange.Weapons.Add(new Weapon { Name = "Spear", Image = ImagePath("WeaponSpear.png") });
            longRange.SelectedWeapon = longRange.Weapons[0];

            WeaponCategory armor = new WeaponCategory { Name = "Armor" };
            armor.Weapons.Add(new Weapon { Name = "Round Shield", Image = ImagePath("WeaponRoundShield.png") });
            armor.Weapons.Add(new Weapon { Name = "Chain Mail", Image = ImagePath("WeaponChainMail.png") });
            armor.Weapons.Add(new Weapon { Name = "Big Shield", Image = ImagePath("WeaponBigShield.png") });
            armor.Weapons.Add(new Weapon { Name = "Breastplate", Image = ImagePath("WeaponBreastplate.png") });
            armor.Weapons.Add(new Weapon { Name = "Helmet", Image = ImagePath("WeaponHelmet.png") });
            armor.SelectedWeapon = armor.Weapons[0];

            WeaponCategory magic = new WeaponCategory { Name = "Magic" };
            magic.Weapons.Add(new Weapon { Name = "Wand", Image = ImagePath("WeaponWand.png") });
            magic.Weapons.Add(new Weapon { Name = "Staff", Image = ImagePath("WeaponStaff.png") });
            magic.Weapons.Add(new Weapon { Name = "Spell Book", Image = ImagePath("WeaponSpellBook.png") });
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
                Charisma = 56,
                Initiative = 120,
                Wins = 26,
                Losses = 3,
                Odds = 103
            };

            Opponent = new PlayerInfo
            {
                Name = "Khorlsendukr",
                Race = Races[1],
                Class = Races[1].Classes[1],
                Initiative = 81,
                Wins = 97,
                Losses = 35,
                Odds = 105
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
            UIElement target = (UIElement)param;
            if (ScreenShown(target))
            {
                SwapContent(_container2, _container1);

                FocusTarget(target);

                if (State == State.Play)
                {
                    SelectedPlayScreen = 0;
                }
            }
        }

        private void OnSlideCompleted(object param)
        {
            if (ScreenShown((UIElement)param))
            {
                SwapContent(_playContainer2, _playContainer1);

                FrameworkElement child = _playContainer1.Child as FrameworkElement;
                UIElement focus = (UIElement)child.FindName((string)child.Tag);
                FocusTarget(focus);
            }
        }

        private bool ScreenShown(UIElement target)
        {
#if NOESIS
            return target.IsEnabled;
#else
            return !target.IsEnabled;
#endif
        }

        private void FocusTarget(UIElement target)
        {
#if NOESIS
            target.Focus();
#else
            target.Dispatcher.BeginInvoke(new Action(() =>
            {
                target.Focus();
            }));
#endif
        }

        private void ShowPlayScreen(int oldScreenIndex, int newScreenIndex)
        {
            if (newScreenIndex >= 0 && newScreenIndex < PlayScreens.Count)
            {
                FrameworkElement screen = CreatePlayScreen(newScreenIndex);
                _playContainer2.Child = screen;

                if (oldScreenIndex < newScreenIndex)
                {
                    PlayScreenDirection = PlayScreenDirection.Next;
                    Storyboard slide = (Storyboard)screen.TryFindResource("SlideFromRight");
                    if (slide != null)
                    {
                        slide.Begin(screen);
                    }
                }
                else
                {
                    PlayScreenDirection = PlayScreenDirection.Prev;
                    Storyboard slide = (Storyboard)screen.TryFindResource("SlideFromLeft");
                    if (slide != null)
                    {
                        slide.Begin(screen);
                    }
                }

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
