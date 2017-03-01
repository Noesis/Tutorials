#if UNITY_5_3_OR_NEWER
#define NOESIS
#endif

#if NOESIS
using Noesis;
using UnityEngine;
using System.Collections.ObjectModel;
#else
using System;
using System.Collections.ObjectModel;
using System.Windows;
using System.Windows.Media;
using System.Windows.Markup;
using System.IO;
#endif

namespace Noesis.Samples
{
	public enum QuestDifficulty
	{
		Easy,
		Normal,
		Hard
	}
	
	public class Quest
	{
		public string Title { get; set; }
		public ImageSource Image { get; set; }
		public QuestDifficulty Difficulty { get; set; }
		public string Description { get; set; }
		public bool Completed { get; set; }
	}
	
	public class QuestLogViewModel : NotifyPropertyChangedBase
	{
		public QuestLogViewModel(ResourceDictionary questImages)
		{
			Quests = new ObservableCollection<Quest>();
			
			// Should be filled by application
			Quests.Add(new Quest
				{
					Title = "Nature's Uprising",
					Image = questImages["Image0"] as ImageSource,
					Difficulty = QuestDifficulty.Easy,
					Description = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\nPellentesque molestie dolor ac leo convallis, non fermentum felis lobortis. Vivamus id turpis nibh.\n\nSed feugiat massa dolor, commodo hendrerit lectus dapibus sit amet.",
					Completed = false
				});
			Quests.Add(new Quest
				{
					Title = "Calming the Wake",
					Image = questImages["Image1"] as ImageSource,
					Difficulty = QuestDifficulty.Normal,
					Description = "Nullam volutpat felis eget lorem dictum sodales.\nNulla egestas porttitor ipsum ut tincidunt. Nullam varius justo quis mi pulvinar rutrum at a ligula.\n\nAenean efficitur dolor vel elit varius, sit amet convallis nulla rutrum.",
					Completed = true
				});
			Quests.Add(new Quest
				{
					Title = "Tomen's Curiosity",
					Image = questImages["Image2"] as ImageSource,
					Difficulty = QuestDifficulty.Easy,
					Description = "Quisque nec tortor in tortor.\nVestibulum tincidunt porttitor sit amet justo. Vestibulum vehicula, dui et vehicula finibus, est nunc efficitur sem, in tempus dolor dolor accumsan enim.\n\nUt rhoncus et orci quis vehicula. Nam bibendum at augue sit amet iaculis.",
					Completed = false
				});
			Quests.Add(new Quest
				{
					Title = "Forest in Dispair",
					Image = questImages["Image0"] as ImageSource,
					Difficulty = QuestDifficulty.Normal,
					Description = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\nPellentesque molestie dolor ac leo convallis, non fermentum felis lobortis. Vivamus id turpis nibh.\n\nSed feugiat massa dolor, commodo hendrerit lectus dapibus sit amet.",
					Completed = true
				});
			Quests.Add(new Quest
				{
					Title = "Retaliation",
					Image = questImages["Image1"] as ImageSource,
					Difficulty = QuestDifficulty.Hard,
					Description = "Nullam volutpat felis eget lorem dictum sodales.\nNulla egestas porttitor ipsum ut tincidunt. Nullam varius justo quis mi pulvinar rutrum at a ligula.\n\nAenean efficitur dolor vel elit varius, sit amet convallis nulla rutrum.",
					Completed = true
				});
			Quests.Add(new Quest
				{
					Title = "Living Hearts",
					Image = questImages["Image2"] as ImageSource,
					Difficulty = QuestDifficulty.Easy,
					Description = "Quisque nec tortor in tortor.\nVestibulum tincidunt porttitor sit amet justo. Vestibulum vehicula, dui et vehicula finibus, est nunc efficitur sem, in tempus dolor dolor accumsan enim.\n\nUt rhoncus et orci quis vehicula. Nam bibendum at augue sit amet iaculis.",
					Completed = false
				});
			Quests.Add(new Quest
				{
					Title = "Scout their Defenses",
					Image = questImages["Image0"] as ImageSource,
					Difficulty = QuestDifficulty.Easy,
					Description = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\nPellentesque molestie dolor ac leo convallis, non fermentum felis lobortis. Vivamus id turpis nibh.\n\nSed feugiat massa dolor, commodo hendrerit lectus dapibus sit amet.",
					Completed = false
				});
			Quests.Add(new Quest
				{
					Title = "Rescue the Leader",
					Image = questImages["Image1"] as ImageSource,
					Difficulty = QuestDifficulty.Hard,
					Description = "Nullam volutpat felis eget lorem dictum sodales.\nNulla egestas porttitor ipsum ut tincidunt. Nullam varius justo quis mi pulvinar rutrum at a ligula.\n\nAenean efficitur dolor vel elit varius, sit amet convallis nulla rutrum.",
					Completed = true
				});
			Quests.Add(new Quest
				{
					Title = "Golden Oportunity",
					Image = questImages["Image2"] as ImageSource,
					Difficulty = QuestDifficulty.Hard,
					Description = "Quisque nec tortor in tortor.\nVestibulum tincidunt porttitor sit amet justo. Vestibulum vehicula, dui et vehicula finibus, est nunc efficitur sem, in tempus dolor dolor accumsan enim.\n\nUt rhoncus et orci quis vehicula. Nam bibendum at augue sit amet iaculis.",
					Completed = false
				});
			Quests.Add(new Quest
				{
					Title = "Loyal Subordinates",
					Image = questImages["Image0"] as ImageSource,
					Difficulty = QuestDifficulty.Easy,
					Description = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\nPellentesque molestie dolor ac leo convallis, non fermentum felis lobortis. Vivamus id turpis nibh.\n\nSed feugiat massa dolor, commodo hendrerit lectus dapibus sit amet.",
					Completed = true
				});
			Quests.Add(new Quest
				{
					Title = "Legacy of the Past",
					Image = questImages["Image1"] as ImageSource,
					Difficulty = QuestDifficulty.Normal,
					Description = "Nullam volutpat felis eget lorem dictum sodales.\nNulla egestas porttitor ipsum ut tincidunt. Nullam varius justo quis mi pulvinar rutrum at a ligula.\n\nAenean efficitur dolor vel elit varius, sit amet convallis nulla rutrum.",
					Completed = true
				});
			Quests.Add(new Quest
				{
					Title = "Purging the Dead",
					Image = questImages["Image2"] as ImageSource,
					Difficulty = QuestDifficulty.Hard,
					Description = "Quisque nec tortor in tortor.\nVestibulum tincidunt porttitor sit amet justo. Vestibulum vehicula, dui et vehicula finibus, est nunc efficitur sem, in tempus dolor dolor accumsan enim.\n\nUt rhoncus et orci quis vehicula. Nam bibendum at augue sit amet iaculis.",
					Completed = false
				});
			
			SelectedQuest = Quests[0];
		}
		
		public ObservableCollection<Quest> Quests { get; private set; }
		
		private Quest _selectedQuest;
		public Quest SelectedQuest
		{
			get { return _selectedQuest; }
			set
			{
				if (_selectedQuest != value)
				{
					_selectedQuest = value;
					OnPropertyChanged("SelectedQuest");
				}
			}
		}
	}
}