using System;
using System.Collections.Generic;
using System.Linq;

namespace Scoreboard
{
    public enum Team
    {
        Alliance,
        Horde
    }

    public enum Class
    {
        Fighter,
        Rogue,
        Hunter,
        Mage,
        Cleric
    }

    public class Player
    {
        public Team Team { get; set; }
        public Class Class { get; set; }
        public string Name { get; set; }
        public int Score { get; set; }
        public int Kills { get; set; }
        public int Deaths { get; set; }
        public int Damage { get; set; }
        public int Heal { get; set; }
    }

    public class Game : NotifyPropertyChangedBase
    {
        public Game()
        {
            Players = new List<Player>();

            Name = "Silvershard Mines";
            ElapsedTime = 16;

            Players.Add(new Player { Class = Class.Mage, Deaths = 96, Damage = 8134124, Heal = 1831, Kills = 43, Name = "Namcras Aenean", Score = 476, Team = Team.Alliance });
            Players.Add(new Player { Class = Class.Rogue, Deaths = 98, Damage = 8324715, Heal = 2954, Kills = 79, Name = "Sedlass Vestibulum", Score = 414, Team = Team.Horde });
            Players.Add(new Player { Class = Class.Hunter, Deaths = 45, Damage = 797117, Heal = 2615, Kills = 99, Name = "Curae Praesent", Score = 383, Team = Team.Horde });
            Players.Add(new Player { Class = Class.Hunter, Deaths = 93, Damage = 481757, Heal = 6353, Kills = 34, Name = "Adipiscing Quisque", Score = 327, Team = Team.Alliance });
            Players.Add(new Player { Class = Class.Fighter, Deaths = 82, Damage = 743715, Heal = 37415, Kills = 80, Name = "Estdonec Vivamus", Score = 289, Team = Team.Horde });
            Players.Add(new Player { Class = Class.Rogue, Deaths = 21, Damage = 383571, Heal = 82114, Kills = 90, Name = "Duisleo Curabitur", Score = 265, Team = Team.Alliance });
            Players.Add(new Player { Class = Class.Cleric, Deaths = 86, Damage = 441751, Heal = 255131, Kills = 37, Name = "Musetiam Aliquam", Score = 259, Team = Team.Alliance });
            Players.Add(new Player { Class = Class.Mage, Deaths = 60, Damage = 201175, Heal = 4915, Kills = 63, Name = "Nuncmauris Accumsan", Score = 225, Team = Team.Horde });
            Players.Add(new Player { Class = Class.Fighter, Deaths = 30, Damage = 271735, Heal = 6715, Kills = 20, Name = "Phasellus Nullam", Score = 195, Team = Team.Alliance });
            Players.Add(new Player { Class = Class.Cleric, Deaths = 18, Damage = 87537, Heal = 95717, Kills = 54, Name = "Consequat Bibendum", Score = 180, Team = Team.Horde });
        }

        public string Name { get; set; }
        public int ElapsedTime { get; set; }
        public List<Player> Players { get; internal set; }

        public int AllianceScore { get { return Players.Where(p => p.Team == Team.Alliance).Sum(p => p.Score); } }
        public int HordeScore { get { return Players.Where(p => p.Team == Team.Horde).Sum(p => p.Score); } }

        private int _selectedTeam;
        public int SelectedTeam
        {
            get { return _selectedTeam; }
            set
            {
                if (_selectedTeam != value)
                {
                    _selectedTeam = value;
                    OnPropertyChanged("SelectedTeam");
                }
            }
        }

        private string[] _visibleTeams = new string[] { "Overall", "Alliance", "Horde" };
        public string[] VisibleTeams { get { return _visibleTeams; } }
    }
}
