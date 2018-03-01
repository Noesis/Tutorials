////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __SCOREBOARD_PLAYER_H__
#define __SCOREBOARD_PLAYER_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/ReflectionDeclareEnum.h>


namespace Scoreboard
{

enum class Team
{
    Alliance,
    Horde,
};

enum class Class
{
    Fighter,
    Rogue,
    Hunter,
    Mage,
    Cleric,
};

struct Player: public Noesis::BaseComponent
{
public:
    Player(Class klass_, int deaths_, int damage_, int heal_, int kills_, const char* name_,
        int score_, Team team_): klass(klass_), deaths(deaths_), damage(damage_), heal(heal_),
        kills(kills_), name(name_), score(score_), team(team_) {}

    Class klass;
    int deaths;
    int damage;
    int heal;
    int kills;
    NsString name;
    int score;
    Team team;

    NS_DECLARE_REFLECTION(Player, BaseComponent)
};

}

NS_DECLARE_REFLECTION_ENUM(Scoreboard::Team)
NS_DECLARE_REFLECTION_ENUM(Scoreboard::Class)


#endif
