using System;
using System.Collections.ObjectModel;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;

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

            ImageSource image0 = new BitmapImage(new Uri("pack://application:,,,/QuestLog;component/Images/Image0.png"));
            ImageSource image1 = new BitmapImage(new Uri("pack://application:,,,/QuestLog;component/Images/Image1.png"));
            ImageSource image2 = new BitmapImage(new Uri("pack://application:,,,/QuestLog;component/Images/Image2.png"));

            // Should be filled by application
            Quests.Add(new Quest
            {
                Title = "Nature's Uprising",
                Image = image0,
                Difficulty = QuestDifficulty.Easy,
                Description = "\u201cThe timeless, tireless jaws of nature, which shaped our world since its inception, shall one day devour us all.\u201d",
                Completed = false
            });
            Quests.Add(new Quest
            {
                Title = "Calming the Wake",
                Image = image1,
                Difficulty = QuestDifficulty.Normal,
                Description = "\u201cThe rangers warned us of reports of malevolent evil energy swelling and pouring out of the dark Marshes.\u201d",
                Completed = true
            });
            Quests.Add(new Quest
            {
                Title = "Tomen's Curiosity",
                Image = image2,
                Difficulty = QuestDifficulty.Easy,
                Description = "\u201cBack to camp from the battle, lieutenant Tomen awaits your return with the loot of last night's skirmish.\u201d",
                Completed = false
            });
            Quests.Add(new Quest
            {
                Title = "Forest of Dispair",
                Image = image0,
                Difficulty = QuestDifficulty.Normal,
                Description = "\u201cWild animals are growing more and more aggressive near Eastburg, and our men suffers constant attacks from wolves!\u201d",
                Completed = true
            });
            Quests.Add(new Quest
            {
                Title = "Retaliation",
                Image = image1,
                Difficulty = QuestDifficulty.Hard,
                Description = "\u201cThe goblins are among the most ancient and bitter rivals of the Dwarven brethen, and yet again we should clash.\u201d",
                Completed = true
            });
            Quests.Add(new Quest
            {
                Title = "Living Hearts",
                Image = image2,
                Difficulty = QuestDifficulty.Easy,
                Description = "\u201cVenture into the depths of this land, and old lover's curse may be a blessing in disguise near the BrokenHeart's Well.\u201d",
                Completed = false
            });
            Quests.Add(new Quest
            {
                Title = "Scout their Defenses",
                Image = image0,
                Difficulty = QuestDifficulty.Easy,
                Description = "\u201cElwin believes that you can score a telling blow against the Black Ogres and their masters in the northern Amberwood.\u201d",
                Completed = false
            });
            Quests.Add(new Quest
            {
                Title = "Rescue the Leader",
                Image = image1,
                Difficulty = QuestDifficulty.Hard,
                Description = "\u201cEnter into their dwelling and release as many of the captives as possible. Find them quickly!\u201d",
                Completed = true
            });
            Quests.Add(new Quest
            {
                Title = "Golden Oportunity",
                Image = image2,
                Difficulty = QuestDifficulty.Hard,
                Description = "\u201cYou restored the good name of the Purple Guard, and master Proudbeard is delighted at what you have done.\u201d",
                Completed = false
            });
            Quests.Add(new Quest
            {
                Title = "Loyal Subordinates",
                Image = image2,
                Difficulty = QuestDifficulty.Easy,
                Description = "\u201cYou have helped us before, and if you continue to do so we will not forget it. Neither will the Orcs, to be sure.\u201d",
                Completed = true
            });
            Quests.Add(new Quest
            {
                Title = "Legacy of the Past",
                Image = image1,
                Difficulty = QuestDifficulty.Normal,
                Description = "\u201cWord of your deeds travelled far, and you became much sought-after by those who have need of such a champion!\u201d",
                Completed = true
            });
            Quests.Add(new Quest
            {
                Title = "Purging the Dead",
                Image = image2,
                Difficulty = QuestDifficulty.Hard,
                Description = "\u201cI think he said he hid it in a tall tree east of the River Falls in the Autumn Valley. Beware of the Necromancer!\u201d",
                Completed = false
            });

            SelectedQuest = Quests[1];
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