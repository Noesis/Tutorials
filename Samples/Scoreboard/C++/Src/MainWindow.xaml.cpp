////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "MainWindow.xaml.h"
#include "NotifyPropertyChangedBase.h"
#include "Player.h"

#include <NsGui/IntegrationAPI.h>
#include <NsGui/Collection.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/ReflectionImplementEnum.h>


using namespace Scoreboard;
using namespace Noesis;


////////////////////////////////////////////////////////////////////////////////////////////////////
class Game: public NotifyPropertyChangedBase
{
public:
    Game()
    {
        _players = *new Collection();
        _visibleTeams = *new Collection();
        _visibleTeams->Add("Overall");
        _visibleTeams->Add("Alliance");
        _visibleTeams->Add("Horde");
    }

    void SetName(const char* name)
    {
        _name = name;
    }

    const char* GetName() const
    {
        return _name.c_str();
    }

    void SetElapsedTime(int elapsedTime)
    {
        _elapsedTime = elapsedTime;
    }

    int GetElapsedTime() const
    {
        return _elapsedTime;
    }

    void SetSelectedTeam(int selectedTeam)
    {
        if (_selectedTeam != selectedTeam)
        {
            _selectedTeam = selectedTeam;
            OnPropertyChanged("SelectedTeam");
        }
    }

    int GetSelectedTeam() const
    {
        return _selectedTeam;
    }

    Collection* GetPlayers() const
    {
        return _players;
    }

    int GetAllianceScore() const
    {
        int score = 0;

        for (uint32_t i = 0; i < _players->Count(); i++)
        {
            Player* player = (Player*)_players->Get(i);

            if (player->team == Team::Alliance)
            {
                score += player->score;
            }
        }

        return score;
    }

    int GetHordeScore() const
    {
        int score = 0;

        for (uint32_t i = 0; i < _players->Count(); i++)
        {
            Player* player = (Player*)_players->Get(i);

            if (player->team == Team::Horde)
            {
                score += player->score;
            }
        }

        return score;
    }

    Collection* GetVisibleTeams() const
    {
        return _visibleTeams;
    }

private:
    NsString _name;
    int _elapsedTime;
    int _selectedTeam;
    Ptr<Collection> _players;
    Ptr<Collection> _visibleTeams;

    NS_IMPLEMENT_INLINE_REFLECTION(Game, NotifyPropertyChangedBase)
    {
        NsProp("Name", &Game::GetName, &Game::SetName);
        NsProp("ElapsedTime", &Game::GetElapsedTime, &Game::SetElapsedTime);
        NsProp("Players", &Game::GetPlayers);
        NsProp("AllianceScore", &Game::GetAllianceScore);
        NsProp("HordeScore", &Game::GetHordeScore);
        NsProp("SelectedTeam", &Game::GetSelectedTeam, &Game::SetSelectedTeam);
        NsProp("VisibleTeams", &Game::GetVisibleTeams);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
MainWindow::MainWindow()
{
    Initialized() += MakeDelegate(this, &MainWindow::OnInitialized);
    InitializeComponent();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::InitializeComponent()
{
    GUI::LoadComponent(this, "MainWindow.xaml");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::OnInitialized(BaseComponent*, const EventArgs&)
{
    Ptr<Game> game = *new Game();
    game->SetName("Silvershard Mines");
    game->SetElapsedTime(16);
    game->SetSelectedTeam(0);

    {
        Ptr<Player> player = *new Player(Class::Mage, 96, 8134124, 1831, 43, "Nam cras aenean", 476, Team::Alliance);
        game->GetPlayers()->Add(player);
    }
    {
        Ptr<Player> player = *new Player(Class::Rogue, 98, 8324715, 2954, 79, "Sed class vestibulum", 414, Team::Horde);
        game->GetPlayers()->Add(player);
    }
    {
        Ptr<Player> player = *new Player(Class::Hunter, 45, 797117, 2615, 99, "Curae praesent", 383, Team::Horde);
        game->GetPlayers()->Add(player);
    }
    {
        Ptr<Player> player = *new Player(Class::Hunter, 93, 481757, 6353, 34, "Adipiscing dis quisque", 327, Team::Alliance);
        game->GetPlayers()->Add(player);
    }
    {
        Ptr<Player> player = *new Player(Class::Fighter, 82, 743715, 37415, 80, "Est donec vivamus", 289, Team::Horde);
        game->GetPlayers()->Add(player);
    }
    {
        Ptr<Player> player = *new Player(Class::Rogue, 21, 383571, 82114, 90, "Duis leo curabitur", 265, Team::Alliance);
        game->GetPlayers()->Add(player);
    }
    {
        Ptr<Player> player = *new Player(Class::Cleric, 86, 441751, 255131, 37, "Mus etiam aliquam", 259, Team::Alliance);
        game->GetPlayers()->Add(player);
    }
    {
        Ptr<Player> player = *new Player(Class::Mage, 60, 201175, 4915, 63, "Nunc mauris accumsan", 225, Team::Horde);
        game->GetPlayers()->Add(player);
    }
    {
        Ptr<Player> player = *new Player(Class::Fighter, 30, 271735, 6715, 20, "Phasellus nullam", 195, Team::Alliance);
        game->GetPlayers()->Add(player);
    }
    {
        Ptr<Player> player = *new Player(Class::Cleric, 18, 87537, 95717, 54, "Consequat bibendum", 180, Team::Horde);
        game->GetPlayers()->Add(player);
    }

    SetDataContext(game);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_IMPLEMENT_REFLECTION(Scoreboard::MainWindow)
{
    NsMeta<TypeId>("Scoreboard.MainWindow");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_IMPLEMENT_REFLECTION_ENUM(Scoreboard::Team)
{
    NsMeta<TypeId>("Team");

    NsVal("Alliance", Team::Alliance);
    NsVal("Horde", Team::Horde);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_IMPLEMENT_REFLECTION_ENUM(Scoreboard::Class)
{
    NsMeta<TypeId>("Class");

    NsVal("Fighter", Scoreboard::Class::Fighter);
    NsVal("Rogue", Scoreboard::Class::Rogue);
    NsVal("Hunter", Scoreboard::Class::Hunter);
    NsVal("Mage", Scoreboard::Class::Mage);
    NsVal("Cleric", Scoreboard::Class::Cleric);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
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
