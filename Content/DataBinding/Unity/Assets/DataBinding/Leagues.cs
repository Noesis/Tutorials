using Noesis;
using System.Collections.ObjectModel;


public class Team
{
    public Team(string name)
    {
        Name = name;
    }

    public string Name { get; private set; }
}

public class Division
{
    public Division(string name)
    {
        Name = name;
        Teams = new ObservableCollection<Team>();
    }

    public string Name { get; private set; }
    public ObservableCollection<Team> Teams { get; private set; }
}

public class League
{
    public League(string name)
    {
        Name = name;
        Divisions = new ObservableCollection<Division>();
    }

    public string Name { get; private set; }
    public ObservableCollection<Division> Divisions { get; private set; }
}

public class LeagueList
{
    public LeagueList()
    {
        Leagues = new ObservableCollection<League>();
        
        var leagueA = new League("League A");
        Leagues.Add(leagueA);

        var leagueB = new League("League B");
        Leagues.Add(leagueB);
        
            var divisionA = new Division("Division A");
            leagueB.Divisions.Add(divisionA);

            var divisionB = new Division("Division B");
            leagueB.Divisions.Add(divisionB);

            var divisionC = new Division("Division C");
            leagueB.Divisions.Add(divisionC);
            
                var east = new Team("Team East");
                divisionC.Teams.Add(east);

                var west = new Team("Team West");
                divisionC.Teams.Add(west);

                var north = new Team("Team North");
                divisionC.Teams.Add(north);

                var south = new Team("Team South");
                divisionC.Teams.Add(south);

            var divisionD = new Division("Division D");
            leagueB.Divisions.Add(divisionD);

        var leagueC = new League("League C");
        Leagues.Add(leagueC);
    }
    
    public ObservableCollection<League> Leagues { get; private set; }
}
