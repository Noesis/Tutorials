using System;
using System.Collections.Generic;
using System.Linq;

namespace Scoreboard
{
    public class Game : NotifyPropertyChangedBase
    {
        public Game()
        {
            Players = new List<Player>();
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