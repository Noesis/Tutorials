////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "ViewModel.h"

#include <NsCore/ReflectionImplement.h>
#include <NsCore/ReflectionImplementEnum.h>
#include <NsCore/Boxing.h>


using namespace TicTacToe;
using namespace Noesis;
using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
ViewModel::ViewModel()
{
    _start.SetExecuteFunc(MakeDelegate(this, &ViewModel::OnStart));
    _check.SetExecuteFunc(MakeDelegate(this, &ViewModel::OnCheck));
    _scorePlayer1 = 0;
    _scorePlayer2 = 0;
    _scoreTies = 0;

    // start game
    OnStart(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const DelegateCommand* ViewModel::GetStart() const
{
    return &_start;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const DelegateCommand* ViewModel::GetCheck() const
{
    return &_check;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
State ViewModel::GetState() const
{
    return _state;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int ViewModel::GetScorePlayer1() const
{
    return _scorePlayer1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int ViewModel::GetScorePlayer2() const
{
    return _scorePlayer2;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int ViewModel::GetScoreTies() const
{
    return _scoreTies;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::OnStart(BaseComponent*)
{
    // reset board
    for (int i = 0; i < 9; ++i)
    {
        _board[i] = 0;
    }

    // start next game
    int numGames = _scorePlayer1 + _scorePlayer2 + _scoreTies;
    _state = (numGames % 2) == 0 ? State::Player1 : State::Player2;
    OnPropertyChanged("State");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::OnCheck(BaseComponent* parameter)
{
    // update board
    NS_ASSERT(Boxing::CanUnbox<int>(parameter));
    int index = Boxing::Unbox<int>(parameter);
    _board[index] = (int)_state;

    // check if player win
    _state = CheckWin();
    OnPropertyChanged("State");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
State ViewModel::CheckWin()
{
    for (int i = 0; i < 3; ++i)
    {
        if (CheckRow(i))
        {
            return Win((State)((int)State::WinRow0 + i));
        }
        if (CheckCol(i))
        {
            return Win((State)((int)State::WinCol0 + i));
        }
    }

    if (CheckDiag(0, 2))
    {
        return Win(State::WinDiag1);
    }
    if (CheckDiag(2, 0))
    {
        return Win(State::WinDiag2);
    }

    if (CheckTie())
    {
        _scoreTies++;
        OnPropertyChanged("ScoreTies");

        return State::Tie;
    }

    // continue playing...
    return _state == State::Player1 ? State::Player2 : State::Player1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool ViewModel::CheckRow(int row)
{
    return CheckCell(row, 0) && CheckCell(row, 1) && CheckCell(row, 2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool ViewModel::CheckCol(int col)
{
    return CheckCell(0, col) && CheckCell(1, col) && CheckCell(2, col);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool ViewModel::CheckDiag(int start, int end)
{
    return CheckCell(start, 0) && CheckCell(1, 1) && CheckCell(end, 2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool ViewModel::CheckCell(int row, int col)
{
    return _board[row * 3 + col] == (int)_state;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool ViewModel::CheckTie()
{
    for (int i = 0; i < 9; ++i)
    {
        if (_board[i] == 0)
        {
            return false;
        }
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
State ViewModel::Win(State state)
{
    if (_state == State::Player1)
    {
        _scorePlayer1++;
        OnPropertyChanged("ScorePlayer1");
    }
    else // _state == State::Player2
    {
        _scorePlayer2++;
        OnPropertyChanged("ScorePlayer2");
    }

    return state;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(TicTacToe::ViewModel)
{
    NsProp("Start", &ViewModel::GetStart);
    NsProp("Check", &ViewModel::GetCheck);
    NsProp("State", &ViewModel::GetState);
    NsProp("ScorePlayer1", &ViewModel::GetScorePlayer1);
    NsProp("ScorePlayer2", &ViewModel::GetScorePlayer2);
    NsProp("ScoreTies", &ViewModel::GetScoreTies);
}

NS_IMPLEMENT_REFLECTION_ENUM(TicTacToe::State, "TicTacToe.State")
{
    NsVal("Player1", State::Player1);
    NsVal("Player2", State::Player2);
    NsVal("Tie", State::Tie);
    NsVal("WinRow0", State::WinRow0);
    NsVal("WinRow1", State::WinRow1);
    NsVal("WinRow2", State::WinRow2);
    NsVal("WinCol0", State::WinCol0);
    NsVal("WinCol1", State::WinCol1);
    NsVal("WinCol2", State::WinCol2);
    NsVal("WinDiag1", State::WinDiag1);
    NsVal("WinDiag2", State::WinDiag2);
}

NS_END_COLD_REGION
