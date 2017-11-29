using System;

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
}