////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "MainWindow.xaml.h"
#include "ViewModel.h"

#include <NsGui/IntegrationAPI.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/ReflectionImplementEnum.h>


using namespace Scoreboard;
using namespace Noesis;


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
    game->GetPlayers()->Add(MakePtr<Player>(Class::Mage, 96, 8134124, 1831, 43, "Nam cras aenean", 476, Team::Alliance));
    game->GetPlayers()->Add(MakePtr<Player>(Class::Rogue, 98, 8324715, 2954, 79, "Sed class vestibulum", 414, Team::Horde));
    game->GetPlayers()->Add(MakePtr<Player>(Class::Hunter, 45, 797117, 2615, 99, "Curae praesent", 383, Team::Horde));
    game->GetPlayers()->Add(MakePtr<Player>(Class::Hunter, 93, 481757, 6353, 34, "Adipiscing dis quisque", 327, Team::Alliance));
    game->GetPlayers()->Add(MakePtr<Player>(Class::Fighter, 82, 743715, 37415, 80, "Est donec vivamus", 289, Team::Horde));
    game->GetPlayers()->Add(MakePtr<Player>(Class::Rogue, 21, 383571, 82114, 90, "Duis leo curabitur", 265, Team::Alliance));
    game->GetPlayers()->Add(MakePtr<Player>(Class::Cleric, 86, 441751, 255131, 37, "Mus etiam aliquam", 259, Team::Alliance));
    game->GetPlayers()->Add(MakePtr<Player>(Class::Mage, 60, 201175, 4915, 63, "Nunc mauris accumsan", 225, Team::Horde));
    game->GetPlayers()->Add(MakePtr<Player>(Class::Fighter, 30, 271735, 6715, 20, "Phasellus nullam", 195, Team::Alliance));
    game->GetPlayers()->Add(MakePtr<Player>(Class::Cleric, 18, 87537, 95717, 54, "Consequat bibendum", 180, Team::Horde));

    SetDataContext(game);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(Scoreboard::MainWindow)
{
    NsMeta<TypeId>("Scoreboard.MainWindow");
}

