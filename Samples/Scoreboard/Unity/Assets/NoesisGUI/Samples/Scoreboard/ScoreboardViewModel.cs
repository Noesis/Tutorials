using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using UnityEngine;

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

    [Serializable]
    public class Player
    {
        public string _name;
        public string Name { get => _name; }

        public Class _class;
        public Class Class { get => _class; }

        public Team _team;
        public Team Team { get => _team; }

        public int _score;
        public int Score { get => _score; }

        public int _kills;
        public int Kills { get => _kills; }

        public int _deaths;
        public int Deaths { get => _deaths; }

        public int _damage;
        public int Damage { get => _damage; }

        public int _heal;
        public int Heal { get => _heal; }
    }
}

public class ScoreboardViewModel : MonoBehaviour, INotifyPropertyChanged
{
    public string _name;
    public string Name { get => _name; }

    public int _elapsedTime;
    public int ElapsedTime { get => _elapsedTime; }

    public int AllianceScore { get => Players.Where(p => p.Team == Scoreboard.Team.Alliance).Sum(p => p.Score); }
    public int HordeScore { get => Players.Where(p => p.Team == Scoreboard.Team.Horde).Sum(p => p.Score); }

    private int _selectedTeam;
    public int SelectedTeam
    {
        get => _selectedTeam;
        set { if (_selectedTeam != value) { _selectedTeam = value; OnPropertyChanged("SelectedTeam"); } }
    }

    public List<Scoreboard.Player> _players = new List<Scoreboard.Player>();
    public List<Scoreboard.Player> Players { get => _players; }

    private readonly string[] _visibleTeams = { "Overall", "Alliance", "Horde" };
    public string[] VisibleTeams { get => _visibleTeams; }

    void Reset()
    {
        _name = "Silvershard Mines";
        _elapsedTime = 16;
    }

    void Start()
    {
        NoesisView view = GetComponent<NoesisView>();
        view.Content.DataContext = this;
    }

    private void OnValidate()
    {
        _players = new List<Scoreboard.Player>(_players);
        OnPropertyChanged("Players");
    }

    #region INotifyPropertyChanged
    public event PropertyChangedEventHandler PropertyChanged;

    void OnPropertyChanged(string name)
    {
        PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
    }
    #endregion
}
