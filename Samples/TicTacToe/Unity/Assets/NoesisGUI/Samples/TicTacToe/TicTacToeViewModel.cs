using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using UnityEngine;

namespace TicTacToe
{
    public enum State
    {
        Player1 = 1,
        Player2 = 2,
        Tie,
        WinRow0,
        WinRow1,
        WinRow2,
        WinCol0,
        WinCol1,
        WinCol2,
        WinDiag1,
        WinDiag2
    }
}

public class TicTacToeViewModel : MonoBehaviour, INotifyPropertyChanged
{
    public NoesisEventCommand _startCommand;
    public NoesisEventCommand _checkCommand;

    public NoesisEventCommand StartCommand { get => _startCommand; }
    public NoesisEventCommand CheckCommand { get => _checkCommand; }

    public TicTacToe.State State { get; private set; }

    public int ScorePlayer1 { get; private set; }
    public int ScorePlayer2 { get; private set; }
    public int ScoreTies { get; private set; }

    private int[] _board = new int[9];

    void Start()
    {
        ScorePlayer1 = 0;
        ScorePlayer2 = 0;
        ScoreTies = 0;

        NoesisView view = GetComponent<NoesisView>();
        view.Content.DataContext = this;

        // start game
        OnStart(null);
    }

    public void OnStart(object parameter)
    {
        // reset board
        for (int i = 0; i < 9; ++i)
        {
            _board[i] = 0;
        }

        // start game again
        int numGames = ScorePlayer1 + ScorePlayer2 + ScoreTies;
        State = (numGames % 2) == 0 ? TicTacToe.State.Player1 : TicTacToe.State.Player2;
        OnPropertyChanged("State");
    }

    public void OnCheck(object parameter)
    {
        // update board
        _board[(int)parameter] = (int)State;

        // check if player won
        State = CheckWin();
        OnPropertyChanged("State");
    }

    private TicTacToe.State CheckWin()
    {
        for (int i = 0; i < 3; ++i)
        {
            if (CheckRow(i))
            {
                return Win(TicTacToe.State.WinRow0 + i);
            }
            if (CheckCol(i))
            {
                return Win(TicTacToe.State.WinCol0 + i);
            }
        }

        if (CheckDiag(0, 2))
        {
            return Win(TicTacToe.State.WinDiag1);
        }
        if (CheckDiag(2, 0))
        {
            return Win(TicTacToe.State.WinDiag2);
        }

        if (CheckTie())
        {
            ScoreTies++;
            OnPropertyChanged("ScoreTies");

            return TicTacToe.State.Tie;
        }

        // continue playing...
        return State == TicTacToe.State.Player1 ? TicTacToe.State.Player2 : TicTacToe.State.Player1;
    }

    private bool CheckRow(int row)
    {
        return CheckCell(row, 0) && CheckCell(row, 1) && CheckCell(row, 2);
    }

    private bool CheckCol(int col)
    {
        return CheckCell(0, col) && CheckCell(1, col) && CheckCell(2, col);
    }

    private bool CheckDiag(int start, int end)
    {
        return CheckCell(start, 0) && CheckCell(1, 1) && CheckCell(end, 2);
    }

    private bool CheckCell(int row, int col)
    {
        return _board[row * 3 + col] == (int)State;
    }

    private bool CheckTie()
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

    private TicTacToe.State Win(TicTacToe.State state)
    {
        if (State == TicTacToe.State.Player1)
        {
            ScorePlayer1++;
            OnPropertyChanged("ScorePlayer1");
        }
        else // State == TicTacToe.State.Player2
        {
            ScorePlayer2++;
            OnPropertyChanged("ScorePlayer2");
        }

        return state;
    }

    #region INotifyPropertyChanged
    public event PropertyChangedEventHandler PropertyChanged;

    void OnPropertyChanged(string name)
    {
        PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
    }
    #endregion
}
