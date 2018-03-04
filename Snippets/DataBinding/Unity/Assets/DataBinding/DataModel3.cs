using Noesis;
using System.Collections.ObjectModel;
public class Player
{
    public Player(string name, Color color, float scale, string pos)
    {
        Name = name;
        Color = new SolidColorBrush(color);
        Scale = scale;
        Pos = pos;
    }

    public string Name { get; private set; }
    public Brush Color { get; private set; }
    public float Scale { get; private set; }
    public string Pos { get; private set; }
    
}

public class DataModel3
{
    public DataModel3()
    {
        Players = new ObservableCollection<Player>();
        Players.Add(new Player("Player0", Colors.Red, 1.0f, "(0,0,0)"));
        Players.Add(new Player("Player1", Colors.Gray, 0.75f, "(0,30,0)"));
        Players.Add(new Player("Player2", Colors.Orange, 0.50f, "(0,-10,0)"));
        Players.Add(new Player("Player3", Colors.Green, 0.85f, "(0,-10,0)"));
    }

    public ObservableCollection<Player> Players { get; private set; }
}