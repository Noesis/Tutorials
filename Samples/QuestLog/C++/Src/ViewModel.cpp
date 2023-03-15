////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "ViewModel.h"

#include <NsCore/ReflectionImplement.h>
#include <NsCore/ReflectionImplementEnum.h>
#include <NsGui/BitmapImage.h>
#include <NsGui/Uri.h>


using namespace QuestLog;
using namespace Noesis;


////////////////////////////////////////////////////////////////////////////////////////////////////
struct ViewModel::Quest: public BaseComponent
{
public:
    String title;
    Ptr<ImageSource> image;
    QuestDifficulty difficulty;
    String description;
    bool completed;

private:
    NS_IMPLEMENT_INLINE_REFLECTION(Quest, BaseComponent)
    {
        NsProp("Title", &Quest::title);
        NsProp("Image", &Quest::image);
        NsProp("Difficulty", &Quest::difficulty);
        NsProp("Description", &Quest::description);
        NsProp("Completed", &Quest::completed);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
ViewModel::ViewModel()
{
    _quests = *new ObservableCollection<Quest>();

    Ptr<ImageSource> image0 = *new BitmapImage("Images/Image0.png");
    Ptr<ImageSource> image1 = *new BitmapImage("Images/Image1.png");
    Ptr<ImageSource> image2 = *new BitmapImage("Images/Image2.png");

    {
        Ptr<Quest> q = *new Quest();
        q->title = "Nature's Uprising";
        q->image = image0;
        q->difficulty = QuestDifficulty::Easy;
        q->description = "\u201cThe timeless, tireless jaws of nature, which shaped our world since its inception, shall one day devour us all.\u201d";
        q->completed = false;

        _quests->Add(q);
    }
    {
        Ptr<Quest> q = *new Quest();
        q->title = "Calming the Wake";
        q->image = image1;
        q->difficulty = QuestDifficulty::Normal;
        q->description = "\u201cThe rangers warned us of reports of malevolent evil energy swelling and pouring out of the dark Marshes.\u201d";
        q->completed = true;

        _quests->Add(q);
    }
    {
        Ptr<Quest> q = *new Quest();
        q->title = "Tomen's Curiosity";
        q->image = image2;
        q->difficulty = QuestDifficulty::Easy;
        q->description = "\u201cBack to camp from the battle, lieutenant Tomen awaits your return with the loot of last night's skirmish.\u201d";
        q->completed = false;

        _quests->Add(q);
    }
    {
        Ptr<Quest> q = *new Quest();
        q->title = "Forest in Dispair";
        q->image = image0;
        q->difficulty = QuestDifficulty::Normal;
        q->description = "\u201cWild animals are growing more and more aggressive near Eastburg, and our men suffers constant attacks from wolves!\u201d";
        q->completed = true;

        _quests->Add(q);
    }
    {
        Ptr<Quest> q = *new Quest();
        q->title = "Retaliation";
        q->image = image1;
        q->difficulty = QuestDifficulty::Easy;
        q->description = "\u201cThe goblins are among the most ancient and bitter rivals of the Dwarven brethen, and yet again we should clash.\u201d";
        q->completed = true;

        _quests->Add(q);
    }
    {
        Ptr<Quest> q = *new Quest();
        q->title = "Living Hearts";
        q->image = image2;
        q->difficulty = QuestDifficulty::Easy;
        q->description = "\u201cVenture into the depths of this land, and old lover's curse may be a blessing in disguise near the BrokenHeart's Well.\u201d";
        q->completed = false;

        _quests->Add(q);
    }
    {
        Ptr<Quest> q = *new Quest();
        q->title = "Scout their Defenses";
        q->image = image0;
        q->difficulty = QuestDifficulty::Easy;
        q->description = "\u201cElwin believes that you can score a telling blow against the Black Ogres and their masters in the northern Amberwood.\u201d";
        q->completed = false;

        _quests->Add(q);
    }
    {
        Ptr<Quest> q = *new Quest();
        q->title = "Rescue the Leader";
        q->image = image1;
        q->difficulty = QuestDifficulty::Hard;
        q->description = "\u201cEnter into their dwelling and release as many of the captives as possible. Find them quickly!\u201d";
        q->completed = true;

        _quests->Add(q);
    }
    {
        Ptr<Quest> q = *new Quest();
        q->title = "Golden Oportunity";
        q->image = image2;
        q->difficulty = QuestDifficulty::Hard;
        q->description = "\u201cYou restored the good name of the Purple Guard, and master Proudbeard is delighted at what you have done.\u201d";
        q->completed = false;

        _quests->Add(q);
    }
    {
        Ptr<Quest> q = *new Quest();
        q->title = "Loyal Subordinates";
        q->image = image2;
        q->difficulty = QuestDifficulty::Easy;
        q->description = "\u201cYou have helped us before, and if you continue to do so we will not forget it. Neither will the Orcs, to be sure.\u201d";
        q->completed = true;

        _quests->Add(q);
    }
    {
        Ptr<Quest> q = *new Quest();
        q->title = "Legacy of the Past";
        q->image = image1;
        q->difficulty = QuestDifficulty::Normal;
        q->description = "\u201cWord of your deeds travelled far, and you became much sought-after by those who have need of such a champion!\u201d";
        q->completed = true;

        _quests->Add(q);
    }
    {
        Ptr<Quest> q = *new Quest();
        q->title = "Purging the Dead";
        q->image = image2;
        q->difficulty = QuestDifficulty::Hard;
        q->description = "\u201cI think he said he hid it in a tall tree east of the River Falls in the Autumn Valley. Beware of the Necromancer!\u201d";
        q->completed = false;

        _quests->Add(q);
    }

    _selectedQuest = _quests->Get(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::SetSelectedQuest(Quest* value)
{
    if (_selectedQuest != value)
    {
        _selectedQuest = value;
        OnPropertyChanged("SelectedQuest");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ViewModel::Quest* ViewModel::GetSelectedQuest() const
{
    return _selectedQuest;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(ViewModel)
{
    NsProp("Quests", &ViewModel::_quests);
    NsProp("SelectedQuest", &ViewModel::GetSelectedQuest, &ViewModel::SetSelectedQuest);
}

NS_IMPLEMENT_REFLECTION_ENUM(QuestDifficulty)
{
    NsVal("Easy", QuestDifficulty::Easy);
    NsVal("Normal", QuestDifficulty::Normal);
    NsVal("Hard", QuestDifficulty::Hard);
}

NS_END_COLD_REGION
