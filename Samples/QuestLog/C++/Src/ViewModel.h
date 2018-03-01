////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __QUESTLOG_VIEWMODEL_H__
#define __QUESTLOG_VIEWMODEL_H__


#include <NsCore/Noesis.h>
#include <NsCore/Ptr.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsGui/ObservableCollection.h>

#include "NotifyPropertyChangedBase.h"


namespace QuestLog
{

enum class QuestDifficulty
{
    Easy,
    Normal,
    Hard
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class ViewModel final: public NotifyPropertyChangedBase
{
public:
    ViewModel();

private:
    struct Quest;
    void SetSelectedQuest(Quest* value);
    Quest* GetSelectedQuest() const;

private:
    Noesis::Ptr<Noesis::ObservableCollection<Quest>> _quests;
    Noesis::Ptr<Quest> _selectedQuest;

private:

    NS_DECLARE_REFLECTION(ViewModel, NotifyPropertyChangedBase)
};

}

NS_DECLARE_REFLECTION_ENUM(QuestLog::QuestDifficulty)


#endif
