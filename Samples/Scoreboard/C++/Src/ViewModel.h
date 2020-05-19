////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __SCOREBOARD_VIEWMODEL_H__
#define __SCOREBOARD_VIEWMODEL_H__


#include <NsCore/Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsCore/String.h>
#include <NsGui/Collection.h>
#include <NsApp/NotifyPropertyChangedBase.h>


namespace Scoreboard
{

////////////////////////////////////////////////////////////////////////////////////////////////////
enum class Team
{
    Alliance,
    Horde,
};

////////////////////////////////////////////////////////////////////////////////////////////////////
enum class Class
{
    Fighter,
    Rogue,
    Hunter,
    Mage,
    Cleric,
};

////////////////////////////////////////////////////////////////////////////////////////////////////
struct Player: public Noesis::BaseComponent
{
public:
    Player(Class klass_, int deaths_, int damage_, int heal_, int kills_, const char* name_,
        int score_, Team team_);

    Class klass;
    int deaths;
    int damage;
    int heal;
    int kills;
    Noesis::String name;
    int score;
    Team team;

    NS_DECLARE_REFLECTION(Player, BaseComponent)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class Game: public NoesisApp::NotifyPropertyChangedBase
{
public:
    Game();

    void SetName(const char* name);
    const char* GetName() const;

    void SetElapsedTime(int elapsedTime);
    int GetElapsedTime() const;

    void SetSelectedTeam(int selectedTeam);
    int GetSelectedTeam() const;

    Noesis::Collection<Player>* GetPlayers() const;
    int GetAllianceScore() const;

    int GetHordeScore() const;

    Noesis::Collection<BaseComponent>* GetVisibleTeams() const;

private:
    Noesis::String _name;
    int _elapsedTime;
    int _selectedTeam;
    Noesis::Ptr<Noesis::Collection<Player>> _players;
    Noesis::Ptr<Noesis::Collection<BaseComponent>> _visibleTeams;

    NS_DECLARE_REFLECTION(Game, NotifyPropertyChangedBase)
};

}

NS_DECLARE_REFLECTION_ENUM(Scoreboard::Team)
NS_DECLARE_REFLECTION_ENUM(Scoreboard::Class)


#endif
