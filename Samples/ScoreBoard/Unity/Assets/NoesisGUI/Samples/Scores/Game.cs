using System;
using System.Collections.Generic;
using System.Linq;

namespace Noesis.Samples
{
	public class Game : System.ComponentModel.INotifyPropertyChanged
    {		
		public Game()
		{
			Players = new List<Player>();
		}
		
		public string Name { get; set; }
		public int ElapsedTime { get; set; }
		public List<Player> Players { get; private set; }
	
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
					
					#if UNITY
					UnityEngine.Debug.Log("Selected team: " + _visibleTeams[_selectedTeam].ToString());
					#endif
				}
			}
		}
		
		private string[] _visibleTeams = new string[] { "Overall", "Alliance", "Horde" };
		public string[] VisibleTeams { get { return _visibleTeams; } }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string name)
        {
            System.ComponentModel.PropertyChangedEventHandler handler = PropertyChanged;
            if (handler != null)
            {
                handler(this, new System.ComponentModel.PropertyChangedEventArgs(name));
            }
        }
	}
}