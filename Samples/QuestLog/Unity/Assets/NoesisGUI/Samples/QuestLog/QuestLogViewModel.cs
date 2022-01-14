using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using UnityEngine;

namespace QuestLog
{
    public enum QuestDifficulty
    {
        Easy,
        Normal,
        Hard
    }

    [Serializable]
    public class Quest
    {
        public string _title;
        public string Title { get => _title; }

        public Texture2D _image;
        public Texture2D Image { get => _image; }

        public QuestDifficulty _difficulty;
        public QuestDifficulty Difficulty { get => _difficulty; }

        [TextArea(3, 10)]
        public string _description;
        public string Description { get => _description; }

        public bool _completed;
        public bool Completed { get => _completed; }
    }
}

public class QuestLogViewModel : MonoBehaviour, INotifyPropertyChanged
{
    public List<QuestLog.Quest> _quests = new List<QuestLog.Quest>();
    public List<QuestLog.Quest> Quests { get => _quests; }

    private QuestLog.Quest _selectedQuest;
    public QuestLog.Quest SelectedQuest
    {
        get => _selectedQuest;
        set { if (_selectedQuest != value) { _selectedQuest = value; OnPropertyChanged("SelectedQuest"); } }
    }

    void Start()
    {
        SelectedQuest = Quests.FirstOrDefault();

        NoesisView view = GetComponent<NoesisView>();
        view.Content.DataContext = this;
    }

    private void OnValidate()
    {
        _quests = new List<QuestLog.Quest>(_quests);
        OnPropertyChanged("Quests");
        SelectedQuest = Quests.FirstOrDefault();
    }

    #region INotifyPropertyChanged
    public event PropertyChangedEventHandler PropertyChanged;

    void OnPropertyChanged(string name)
    {
        PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
    }
    #endregion
}
