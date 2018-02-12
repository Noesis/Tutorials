////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "ViewModel.h"

#include <NsCore/ReflectionImplement.h>
#include <NsCore/ReflectionImplementEnum.h>
#include <NsGui/BitmapImage.h>


using namespace QuestLog;
using namespace Noesis;


////////////////////////////////////////////////////////////////////////////////////////////////////
struct ViewModel::Quest: public BaseComponent
{
public:
    NsString title;
    Ptr<ImageSource> image;
    QuestDifficulty difficulty;
    NsString description;
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
        q->description = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\nPellentesque molestie dolor ac leo convallis, non fermentum felis lobortis. Vivamus id turpis nibh.\n\nSed feugiat massa dolor, commodo hendrerit lectus dapibus sit amet.";
        q->completed = false;

        _quests->Add(q);
    }
    {
        Ptr<Quest> q = *new Quest();
        q->title = "Calming the Wake";
        q->image = image1;
        q->difficulty = QuestDifficulty::Normal;
        q->description = "Nullam volutpat felis eget lorem dictum sodales.\nNulla egestas porttitor ipsum ut tincidunt. Nullam varius justo quis mi pulvinar rutrum at a ligula.\n\nAenean efficitur dolor vel elit varius, sit amet convallis nulla rutrum.";
        q->completed = true;

        _quests->Add(q);
    }
    {
        Ptr<Quest> q = *new Quest();
        q->title = "Tomen's Curiosity";
        q->image = image2;
        q->difficulty = QuestDifficulty::Easy;
        q->description = "Quisque nec tortor in tortor.\nVestibulum tincidunt porttitor sit amet justo. Vestibulum vehicula, dui et vehicula finibus, est nunc efficitur sem, in tempus dolor dolor accumsan enim.\n\nUt rhoncus et orci quis vehicula. Nam bibendum at augue sit amet iaculis.";
        q->completed = false;

        _quests->Add(q);
    }
    {
        Ptr<Quest> q = *new Quest();
        q->title = "Forest in Dispair";
        q->image = image0;
        q->difficulty = QuestDifficulty::Normal;
        q->description = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\nPellentesque molestie dolor ac leo convallis, non fermentum felis lobortis. Vivamus id turpis nibh.\n\nSed feugiat massa dolor, commodo hendrerit lectus dapibus sit amet.";
        q->completed = true;

        _quests->Add(q);
    }
    {
        Ptr<Quest> q = *new Quest();
        q->title = "Retaliation";
        q->image = image1;
        q->difficulty = QuestDifficulty::Easy;
        q->description = "Nullam volutpat felis eget lorem dictum sodales.\nNulla egestas porttitor ipsum ut tincidunt. Nullam varius justo quis mi pulvinar rutrum at a ligula.\n\nAenean efficitur dolor vel elit varius, sit amet convallis nulla rutrum.";
        q->completed = true;

        _quests->Add(q);
    }
    {
        Ptr<Quest> q = *new Quest();
        q->title = "Living Hearts";
        q->image = image2;
        q->difficulty = QuestDifficulty::Easy;
        q->description = "Quisque nec tortor in tortor.\nVestibulum tincidunt porttitor sit amet justo. Vestibulum vehicula, dui et vehicula finibus, est nunc efficitur sem, in tempus dolor dolor accumsan enim.\n\nUt rhoncus et orci quis vehicula. Nam bibendum at augue sit amet iaculis.";
        q->completed = false;

        _quests->Add(q);
    }
    {
        Ptr<Quest> q = *new Quest();
        q->title = "Scout their Defenses";
        q->image = image0;
        q->difficulty = QuestDifficulty::Easy;
        q->description = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\nPellentesque molestie dolor ac leo convallis, non fermentum felis lobortis. Vivamus id turpis nibh.\n\nSed feugiat massa dolor, commodo hendrerit lectus dapibus sit amet.";
        q->completed = false;

        _quests->Add(q);
    }
    {
        Ptr<Quest> q = *new Quest();
        q->title = "Rescue the Leader";
        q->image = image1;
        q->difficulty = QuestDifficulty::Hard;
        q->description = "Nullam volutpat felis eget lorem dictum sodales.\nNulla egestas porttitor ipsum ut tincidunt. Nullam varius justo quis mi pulvinar rutrum at a ligula.\n\nAenean efficitur dolor vel elit varius, sit amet convallis nulla rutrum.";
        q->completed = true;

        _quests->Add(q);
    }
    {
        Ptr<Quest> q = *new Quest();
        q->title = "Golden Oportunity";
        q->image = image2;
        q->difficulty = QuestDifficulty::Hard;
        q->description = "Quisque nec tortor in tortor.\nVestibulum tincidunt porttitor sit amet justo. Vestibulum vehicula, dui et vehicula finibus, est nunc efficitur sem, in tempus dolor dolor accumsan enim.\n\nUt rhoncus et orci quis vehicula. Nam bibendum at augue sit amet iaculis.";
        q->completed = false;

        _quests->Add(q);
    }
    {
        Ptr<Quest> q = *new Quest();
        q->title = "Loyal Subordinates";
        q->image = image2;
        q->difficulty = QuestDifficulty::Easy;
        q->description = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\nPellentesque molestie dolor ac leo convallis, non fermentum felis lobortis. Vivamus id turpis nibh.\n\nSed feugiat massa dolor, commodo hendrerit lectus dapibus sit amet.";
        q->completed = true;

        _quests->Add(q);
    }
    {
        Ptr<Quest> q = *new Quest();
        q->title = "Legacy of the Past";
        q->image = image1;
        q->difficulty = QuestDifficulty::Normal;
        q->description = "Nullam volutpat felis eget lorem dictum sodales.\nNulla egestas porttitor ipsum ut tincidunt. Nullam varius justo quis mi pulvinar rutrum at a ligula.\n\nAenean efficitur dolor vel elit varius, sit amet convallis nulla rutrum.";
        q->completed = true;

        _quests->Add(q);
    }
    {
        Ptr<Quest> q = *new Quest();
        q->title = "Purging the Dead";
        q->image = image2;
        q->difficulty = QuestDifficulty::Hard;
        q->description = "Quisque nec tortor in tortor.\nVestibulum tincidunt porttitor sit amet justo. Vestibulum vehicula, dui et vehicula finibus, est nunc efficitur sem, in tempus dolor dolor accumsan enim.\n\nUt rhoncus et orci quis vehicula. Nam bibendum at augue sit amet iaculis.";
        q->completed = false;

        _quests->Add(q);
    }

    _selectedQuest.Reset(_quests->Get(0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::SetSelectedQuest(Quest* value)
{
    if (_selectedQuest != value)
    {
        _selectedQuest.Reset(value);
        OnPropertyChanged("SelectedQuest");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ViewModel::Quest* ViewModel::GetSelectedQuest() const
{
    return _selectedQuest;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_IMPLEMENT_REFLECTION(ViewModel)
{
    NsProp("Quests", &ViewModel::_quests);
    NsProp("SelectedQuest", &ViewModel::GetSelectedQuest, &ViewModel::SetSelectedQuest);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_IMPLEMENT_REFLECTION_ENUM(QuestDifficulty)
{
    NsVal("Easy", QuestDifficulty::Easy);
    NsVal("Normal", QuestDifficulty::Normal);
    NsVal("Hard", QuestDifficulty::Hard);
}
