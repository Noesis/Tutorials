#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
using UnityEngine;
using System;
using System.Collections.ObjectModel;
#else
using System;
using System.Collections.ObjectModel;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;
#endif

namespace QuestLog
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

    public class ViewModel : NotifyPropertyChangedBase
    {
        public ViewModel()
        {
            Quests = new ObservableCollection<Quest>();

#if NET_2_0_SUBSET
            // Net2.0 does not support 'pack://application' syntax and we need it to display images at editor time in Blend
            ImageSource image0 = new BitmapImage(new Uri("Assets/NoesisGUI/Samples/QuestLog/Images/Image0.png", UriKind.Relative));
            ImageSource image1 = new BitmapImage(new Uri("Assets/NoesisGUI/Samples/QuestLog/Images/Image1.png", UriKind.Relative));
            ImageSource image2 = new BitmapImage(new Uri("Assets/NoesisGUI/Samples/QuestLog/Images/Image2.png", UriKind.Relative));
#else
            ImageSource image0 = new BitmapImage(new Uri("pack://application:,,,/QuestLog;component/Assets/NoesisGUI/Samples/QuestLog/Images/Image0.png"));
            ImageSource image1 = new BitmapImage(new Uri("pack://application:,,,/QuestLog;component/Assets/NoesisGUI/Samples/QuestLog/Images/Image1.png"));
            ImageSource image2 = new BitmapImage(new Uri("pack://application:,,,/QuestLog;component/Assets/NoesisGUI/Samples/QuestLog/Images/Image2.png"));
#endif

            // Should be filled by application
            Quests.Add(new Quest
                {
                    Title = "Nature's Uprising",
                    Image = image0,
                    Difficulty = QuestDifficulty.Easy,
                    Description = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\nPellentesque molestie dolor ac leo convallis, non fermentum felis lobortis. Vivamus id turpis nibh.\n\nSed feugiat massa dolor, commodo hendrerit lectus dapibus sit amet.",
                    Completed = false
                });
            Quests.Add(new Quest
                {
                    Title = "Calming the Wake",
                    Image = image1,
                    Difficulty = QuestDifficulty.Normal,
                    Description = "Nullam volutpat felis eget lorem dictum sodales.\nNulla egestas porttitor ipsum ut tincidunt. Nullam varius justo quis mi pulvinar rutrum at a ligula.\n\nAenean efficitur dolor vel elit varius, sit amet convallis nulla rutrum.",
                    Completed = true
                });
            Quests.Add(new Quest
                {
                    Title = "Tomen's Curiosity",
                    Image = image2,
                    Difficulty = QuestDifficulty.Easy,
                    Description = "Quisque nec tortor in tortor.\nVestibulum tincidunt porttitor sit amet justo. Vestibulum vehicula, dui et vehicula finibus, est nunc efficitur sem, in tempus dolor dolor accumsan enim.\n\nUt rhoncus et orci quis vehicula. Nam bibendum at augue sit amet iaculis.",
                    Completed = false
                });
            Quests.Add(new Quest
                {
                    Title = "Forest in Dispair",
                    Image = image0,
                    Difficulty = QuestDifficulty.Normal,
                    Description = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\nPellentesque molestie dolor ac leo convallis, non fermentum felis lobortis. Vivamus id turpis nibh.\n\nSed feugiat massa dolor, commodo hendrerit lectus dapibus sit amet.",
                    Completed = true
                });
            Quests.Add(new Quest
                {
                    Title = "Retaliation",
                    Image = image1,
                    Difficulty = QuestDifficulty.Hard,
                    Description = "Nullam volutpat felis eget lorem dictum sodales.\nNulla egestas porttitor ipsum ut tincidunt. Nullam varius justo quis mi pulvinar rutrum at a ligula.\n\nAenean efficitur dolor vel elit varius, sit amet convallis nulla rutrum.",
                    Completed = true
                });
            Quests.Add(new Quest
                {
                    Title = "Living Hearts",
                    Image = image2,
                    Difficulty = QuestDifficulty.Easy,
                    Description = "Quisque nec tortor in tortor.\nVestibulum tincidunt porttitor sit amet justo. Vestibulum vehicula, dui et vehicula finibus, est nunc efficitur sem, in tempus dolor dolor accumsan enim.\n\nUt rhoncus et orci quis vehicula. Nam bibendum at augue sit amet iaculis.",
                    Completed = false
                });
            Quests.Add(new Quest
                {
                    Title = "Scout their Defenses",
                    Image = image0,
                    Difficulty = QuestDifficulty.Easy,
                    Description = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\nPellentesque molestie dolor ac leo convallis, non fermentum felis lobortis. Vivamus id turpis nibh.\n\nSed feugiat massa dolor, commodo hendrerit lectus dapibus sit amet.",
                    Completed = false
                });
            Quests.Add(new Quest
                {
                    Title = "Rescue the Leader",
                    Image = image1,
                    Difficulty = QuestDifficulty.Hard,
                    Description = "Nullam volutpat felis eget lorem dictum sodales.\nNulla egestas porttitor ipsum ut tincidunt. Nullam varius justo quis mi pulvinar rutrum at a ligula.\n\nAenean efficitur dolor vel elit varius, sit amet convallis nulla rutrum.",
                    Completed = true
                });
            Quests.Add(new Quest
                {
                    Title = "Golden Oportunity",
                    Image = image2,
                    Difficulty = QuestDifficulty.Hard,
                    Description = "Quisque nec tortor in tortor.\nVestibulum tincidunt porttitor sit amet justo. Vestibulum vehicula, dui et vehicula finibus, est nunc efficitur sem, in tempus dolor dolor accumsan enim.\n\nUt rhoncus et orci quis vehicula. Nam bibendum at augue sit amet iaculis.",
                    Completed = false
                });
            Quests.Add(new Quest
                {
                    Title = "Loyal Subordinates",
                    Image = image2,
                    Difficulty = QuestDifficulty.Easy,
                    Description = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\nPellentesque molestie dolor ac leo convallis, non fermentum felis lobortis. Vivamus id turpis nibh.\n\nSed feugiat massa dolor, commodo hendrerit lectus dapibus sit amet.",
                    Completed = true
                });
            Quests.Add(new Quest
                {
                    Title = "Legacy of the Past",
                    Image = image1,
                    Difficulty = QuestDifficulty.Normal,
                    Description = "Nullam volutpat felis eget lorem dictum sodales.\nNulla egestas porttitor ipsum ut tincidunt. Nullam varius justo quis mi pulvinar rutrum at a ligula.\n\nAenean efficitur dolor vel elit varius, sit amet convallis nulla rutrum.",
                    Completed = true
                });
            Quests.Add(new Quest
                {
                    Title = "Purging the Dead",
                    Image = image2,
                    Difficulty = QuestDifficulty.Hard,
                    Description = "Quisque nec tortor in tortor.\nVestibulum tincidunt porttitor sit amet justo. Vestibulum vehicula, dui et vehicula finibus, est nunc efficitur sem, in tempus dolor dolor accumsan enim.\n\nUt rhoncus et orci quis vehicula. Nam bibendum at augue sit amet iaculis.",
                    Completed = false
                });
            
            SelectedQuest = Quests[0];
        }

        public ObservableCollection<Quest> Quests { get; internal set; }
        
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