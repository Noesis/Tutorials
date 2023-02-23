using System.ComponentModel;

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

    public class ViewModel : NotifyPropertyChangedBase
    {
        public DelegateCommand StartCommand { get; private set; }
        public DelegateCommand CheckCommand { get; private set; }

        public State State { get; private set; }

        public int ScorePlayer1 { get; private set; }
        public int ScorePlayer2 { get; private set; }
        public int ScoreTies { get; private set; }

        public ViewModel()
        {
            StartCommand = new DelegateCommand(OnStart);
            CheckCommand = new DelegateCommand(OnCheck);
            ScorePlayer1 = 0;
            ScorePlayer2 = 0;
            ScoreTies = 0;

            // start game
            OnStart(null);
        }

        private void OnStart(object parameter)
        {
            // reset board
            for (int i = 0; i < 9; ++i)
            {
                _board[i] = 0;
            }

            // start game again
            int numGames = ScorePlayer1 + ScorePlayer2 + ScoreTies;
            State = (numGames % 2) == 0 ? State.Player1 : State.Player2;
            OnPropertyChanged("State");
        }

        private void OnCheck(object parameter)
        {
            // update board
            _board[(int)parameter] = (int)State;

            // check if player won
            State = CheckWin();
            OnPropertyChanged("State");
        }

        private State CheckWin()
        {
            for (int i = 0; i < 3; ++i)
            {
                if (CheckRow(i))
                {
                    return Win(State.WinRow0 + i);
                }
                if (CheckCol(i))
                {
                    return Win(State.WinCol0 + i);
                }
            }

            if (CheckDiag(0, 2))
            {
                return Win(State.WinDiag1);
            }
            if (CheckDiag(2, 0))
            {
                return Win(State.WinDiag2);
            }

            if (CheckTie())
            {
                ScoreTies++;
                OnPropertyChanged("ScoreTies");

                return State.Tie;
            }

            // continue playing...
            return State == State.Player1 ? State.Player2 : State.Player1;
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

        private State Win(State state)
        {
            if (State == State.Player1)
            {
                ScorePlayer1++;
                OnPropertyChanged("ScorePlayer1");
            }
            else // State == State.Player2
            {
                ScorePlayer2++;
                OnPropertyChanged("ScorePlayer2");
            }

            return state;
        }

        private int[] _board = new int[9];
    }
}
