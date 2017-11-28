#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
#else
using System;
using System.Windows;
using System.Windows.Controls;
#endif


namespace Scoreboard
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : UserControl
    {
        public MainWindow()
        {
            this.Initialized += OnInitialized;
            this.InitializeComponent();
        }

#if NOESIS
        private void InitializeComponent()
        {
            Noesis.GUI.LoadComponent(this, "Assets/NoesisGUI/Samples/Scoreboard/MainWindow.xaml");
        }
#endif

        private void OnInitialized(object sender, EventArgs args)
        {
            var game = new Game { ElapsedTime = 16, Name = "Silvershard Mines" };
            game.Players.Add(new Player { Class = Class.Mage, Deaths = 96, Damage = 8134124, Heal = 1831, Kills = 43, Name = "Nam cras aenean", Score = 476, Team = Team.Alliance });
            game.Players.Add(new Player { Class = Class.Rogue, Deaths = 98, Damage = 8324715, Heal = 2954, Kills = 79, Name = "Sed class vestibulum", Score = 414, Team = Team.Horde });
            game.Players.Add(new Player { Class = Class.Hunter, Deaths = 45, Damage = 797117, Heal = 2615, Kills = 99, Name = "Curae praesent", Score = 383, Team = Team.Horde });
            game.Players.Add(new Player { Class = Class.Hunter, Deaths = 93, Damage = 481757, Heal = 6353, Kills = 34, Name = "Adipiscing dis quisque", Score = 327, Team = Team.Alliance });
            game.Players.Add(new Player { Class = Class.Fighter, Deaths = 82, Damage = 743715, Heal = 37415, Kills = 80, Name = "Est donec vivamus", Score = 289, Team = Team.Horde });
            game.Players.Add(new Player { Class = Class.Rogue, Deaths = 21, Damage = 383571, Heal = 82114, Kills = 90, Name = "Duis leo curabitur", Score = 265, Team = Team.Alliance });
            game.Players.Add(new Player { Class = Class.Cleric, Deaths = 86, Damage = 441751, Heal = 255131, Kills = 37, Name = "Mus etiam aliquam", Score = 259, Team = Team.Alliance });
            game.Players.Add(new Player { Class = Class.Mage, Deaths = 60, Damage = 201175, Heal = 4915, Kills = 63, Name = "Nunc mauris accumsan", Score = 225, Team = Team.Horde });
            game.Players.Add(new Player { Class = Class.Fighter, Deaths = 30, Damage = 271735, Heal = 6715, Kills = 20, Name = "Phasellus nullam", Score = 195, Team = Team.Alliance });
            game.Players.Add(new Player { Class = Class.Cleric, Deaths = 18, Damage = 87537, Heal = 95717, Kills = 54, Name = "Consequat bibendum", Score = 180, Team = Team.Horde });

            this.DataContext = game;
        }
    }
}