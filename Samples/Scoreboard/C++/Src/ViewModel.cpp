////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "ViewModel.h"
#include <NsCore/ReflectionImplement.h>
#include <NsCore/ReflectionImplementEnum.h>
#include <NsCore/TypeId.h>


using namespace Noesis;
using namespace Scoreboard;


////////////////////////////////////////////////////////////////////////////////////////////////////
Player::Player(Class klass_, int deaths_, int damage_, int heal_, int kills_, const char* name_,
    int score_, Team team_): klass(klass_), deaths(deaths_), damage(damage_), heal(heal_),
    kills(kills_), name(name_), score(score_), team(team_)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Game::Game()
{
    _players = *new Collection<Player>();
    _visibleTeams = *new Collection<BaseComponent>();
    _visibleTeams->Add(Boxing::Box("Overall"));
    _visibleTeams->Add(Boxing::Box("Alliance"));
    _visibleTeams->Add(Boxing::Box("Horde"));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::SetName(const char* name)
{
    _name = name;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* Game::GetName() const
{
    return _name.c_str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::SetElapsedTime(int elapsedTime)
{
    _elapsedTime = elapsedTime;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int Game::GetElapsedTime() const
{
    return _elapsedTime;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::SetSelectedTeam(int selectedTeam)
{
    if (_selectedTeam != selectedTeam)
    {
        _selectedTeam = selectedTeam;
        OnPropertyChanged("SelectedTeam");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int Game::GetSelectedTeam() const
{
    return _selectedTeam;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Collection<Player>* Game::GetPlayers() const
{
    return _players;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int Game::GetAllianceScore() const
{
    int score = 0;

    for (int i = 0; i < _players->Count(); i++)
    {
        Player* player = _players->Get(i);

        if (player->team == Team::Alliance)
        {
            score += player->score;
        }
    }

    return score;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int Game::GetHordeScore() const
{
    int score = 0;

    for (int i = 0; i < _players->Count(); i++)
    {
        Player* player = _players->Get(i);

        if (player->team == Team::Horde)
        {
            score += player->score;
        }
    }

    return score;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Collection<BaseComponent>* Game::GetVisibleTeams() const
{
    return _visibleTeams;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(Scoreboard::Game)
{
    NsProp("Name", &Game::GetName, &Game::SetName);
    NsProp("ElapsedTime", &Game::GetElapsedTime, &Game::SetElapsedTime);
    NsProp("Players", &Game::GetPlayers);
    NsProp("AllianceScore", &Game::GetAllianceScore);
    NsProp("HordeScore", &Game::GetHordeScore);
    NsProp("SelectedTeam", &Game::GetSelectedTeam, &Game::SetSelectedTeam);
    NsProp("VisibleTeams", &Game::GetVisibleTeams);
}

NS_IMPLEMENT_REFLECTION_ENUM(Scoreboard::Team)
{
    NsMeta<TypeId>("Scoreboard.Team");

    NsVal("Alliance", Team::Alliance);
    NsVal("Horde", Team::Horde);
}

NS_IMPLEMENT_REFLECTION_ENUM(Scoreboard::Class)
{
    NsMeta<TypeId>("Scoreboard.Class");

    NsVal("Fighter", Scoreboard::Class::Fighter);
    NsVal("Rogue", Scoreboard::Class::Rogue);
    NsVal("Hunter", Scoreboard::Class::Hunter);
    NsVal("Mage", Scoreboard::Class::Mage);
    NsVal("Cleric", Scoreboard::Class::Cleric);
}

NS_IMPLEMENT_REFLECTION(Scoreboard::Player)
{
    NsProp("Class", &Player::klass);
    NsProp("Deaths", &Player::deaths);
    NsProp("Damage", &Player::damage);
    NsProp("Heal", &Player::heal);
    NsProp("Kills", &Player::kills);
    NsProp("Name", &Player::name);
    NsProp("Score", &Player::score);
    NsProp("Team", &Player::team);
}
