using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;

namespace TicTacToe
{
    public enum Player
    {
        Player1,
        Player2
    }

    class Cell : NotifyPropertyChangedBase
    {
        public event EventHandler Checked;

        private bool _isChecked;
        public bool IsChecked
        {
            get { return _isChecked; }
            set
            {
                if (_isChecked != value)
                {
                    _isChecked = value;
                    OnPropertyChanged("IsChecked");

                    if (_isChecked)
                    {
                        OnChecked(EventArgs.Empty);
                    }
                }
            }
        }

        private Player _player;
        public Player Player
        {
            get { return _player; }
            set
            {
                if (_player != value)
                {
                    _player = value;
                    OnPropertyChanged("Player");
                }
            }
        }

        private void OnChecked(EventArgs e)
        {
            EventHandler handler = Checked;
            if (handler != null)
            {
                handler(this, e);
            }
        }
    }

    public enum Status
    {
        Waiting,
        Playing,
        WinRow1,
        WinRow2,
        WinRow3,
        WinColumn1,
        WinColumn2,
        WinColumn3,
        WinDiagonal1,
        WinDiagonal2,
        Tie
    }

    class ViewModel : NotifyPropertyChangedBase
    {
        /// <summary>
        /// Cells[0..2] : 1st Row
        /// Cells[3..5] : 2nd Row
        /// Cells[6..8] : 3rd Row
        /// </summary>
        public List<Cell> Board { get; private set; }

        private uint _scorePlayer1;
        public uint ScorePlayer1
        {
            get { return _scorePlayer1; }
            set
            {
                if (_scorePlayer1 != value)
                {
                    _scorePlayer1 = value;
                    OnPropertyChanged("ScorePlayer1");

                    ScorePlayer1Changed = !ScorePlayer1Changed;
                    OnPropertyChanged("ScorePlayer1Changed");
                }
            }
        }

        public bool ScorePlayer1Changed { get; private set; }

        private uint _scorePlayer2;
        public uint ScorePlayer2
        {
            get { return _scorePlayer2; }
            set
            {
                if (_scorePlayer2 != value)
                {
                    _scorePlayer2 = value;
                    OnPropertyChanged("ScorePlayer2");

                    ScorePlayer2Changed = !ScorePlayer2Changed;
                    OnPropertyChanged("ScorePlayer2Changed");
                }
            }
        }

        public bool ScorePlayer2Changed { get; private set; }

        private uint _scoreTies;
        public uint ScoreTies
        {
            get { return _scoreTies; }
            set
            {
                if (_scoreTies != value)
                {
                    _scoreTies = value;
                    OnPropertyChanged("ScoreTies");

                    ScoreTiesChanged = !ScoreTiesChanged;
                    OnPropertyChanged("ScoreTiesChanged");
                }
            }
        }

        public bool ScoreTiesChanged { get; private set; }

        private Player _lastPlayerStarting;
        private Player _playerPlaying;
        public Player PlayerPlaying
        {
            get { return _playerPlaying; }
            set
            {
                if (_playerPlaying != value)
                {
                    _playerPlaying = value;
                    OnPropertyChanged("PlayerPlaying");

                    PlayerPlayingChanged = !PlayerPlayingChanged;
                    OnPropertyChanged("PlayerPlayingChanged");
                }
            }
        }

        public bool PlayerPlayingChanged { get; private set; }

        private Status _status;
        public Status Status
        {
            get { return _status; }
            set
            {
                if (_status != value)
                {
                    _status = value;
                    OnPropertyChanged("Status");

                    StartGame.RaiseCanExecuteChanged();
                }
            }
        }

        public DelegateCommand StartGame { get; private set; }

        public ViewModel()
        {
            Board = new List<Cell>(9);
            for (int i = 0; i < 9; ++i)
            {
                Cell cell = new Cell();
                cell.Checked += OnCellChecked;
                Board.Add(cell);
            }

            StartGame = new DelegateCommand(OnCanStartGame, OnStartGame);

            _lastPlayerStarting = Player.Player2;
            ScorePlayer1 = 0;
            ScorePlayer2 = 0;
            ScoreTies = 0;
            Status = Status.Waiting;
        }

        bool OnCanStartGame(object param)
        {
            return Status != Status.Playing;
        }

        void OnStartGame(object param)
        {
            _lastPlayerStarting = SwitchPlayer(_lastPlayerStarting);
            PlayerPlaying = _lastPlayerStarting;

            for (int i = 0; i < 9; ++i)
            {
                Cell cell = Board[i];
                cell.IsChecked = false;
                cell.Player = PlayerPlaying;
            }

            Status = Status.Playing;
        }

        void OnCellChecked(object sender, EventArgs e)
        {
            if (!CheckGameEnd())
            {
                SwitchPlayer();
            }
        }

        private bool CheckGameEnd()
        {
            for (int i = 0; i < 3; ++i)
            {
                if (CheckRow(i))
                {
                    WinGame((Status)(Status.WinRow1 + i));
                    return true;
                }
                if (CheckColumn(i))
                {
                    WinGame((Status)(Status.WinColumn1 + i));
                    return true;
                }
            }

            if (CheckDiagonal(0, 2))
            {
                WinGame(Status.WinDiagonal1);
                return true;
            }
            if (CheckDiagonal(2, 0))
            {
                WinGame(Status.WinDiagonal2);
                return true;
            }

            if (CheckTie())
            {
                TieGame();
                return true;
            }

            return false;
        }

        private bool CheckRow(int row)
        {
            return CheckCell(row, 0) && CheckCell(row, 1) && CheckCell(row, 2);
        }

        private bool CheckColumn(int col)
        {
            return CheckCell(0, col) && CheckCell(1, col) && CheckCell(2, col);
        }

        private bool CheckDiagonal(int start, int end)
        {
            return CheckCell(start, 0) && CheckCell(1, 1) && CheckCell(end, 2);
        }

        private bool CheckCell(int row, int col)
        {
            Cell cell = Board[row * 3 + col];
            return cell.IsChecked == true && cell.Player == PlayerPlaying;
        }

        private bool CheckTie()
        {
            return Board.Where((c) => !c.IsChecked).Count() == 0;
        }

        private void WinGame(Status status)
        {
            if (PlayerPlaying == Player.Player1)
            {
                ScorePlayer1++;
            }
            else
            {
                ScorePlayer2++;
            }

            Status = status;
        }

        private void TieGame()
        {
            ScoreTies++;
            Status = Status.Tie;
        }

        private void SwitchPlayer()
        {
            PlayerPlaying = SwitchPlayer(PlayerPlaying);

            for (int i = 0; i < 9; ++i)
            {
                Cell cell = Board[i];
                if (!cell.IsChecked)
                {
                    cell.Player = PlayerPlaying;
                }
            }
        }

        private Player SwitchPlayer(Player currentPlayer)
        {
            return currentPlayer == Player.Player1 ? Player.Player2 : Player.Player1;
        }
    }
}
