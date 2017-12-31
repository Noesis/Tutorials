#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
#else
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
#endif

namespace TicTacToe
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : UserControl
    {
        public MainWindow()
        {
            Initialized += OnInitialized;
            InitializeComponent();
        }

#if NOESIS
        private void InitializeComponent()
        {
            Noesis.GUI.LoadComponent(this, "Assets/NoesisGUI/Samples/TicTacToe/MainWindow.xaml");
        }
#endif

        private void OnInitialized(object sender, EventArgs e)
        {
            _board = new Cell[3, 3];

            _boardPanel = (FrameworkElement)FindName("Board");
            _boardPanel.MouseLeftButtonDown += OnBoardClicked;

            for (int row = 0; row < 3; ++row)
            {
                for (int col = 0; col < 3; ++col)
                {
                    string cellName = string.Format("Cell{0}{1}", row, col);

                    ToggleButton btn = (ToggleButton)FindName(cellName);

                    Cell cell = new Cell { Button = btn };
                    _board[row, col] = cell;

                    btn.Tag = cell;
                    btn.IsEnabled = false;
                    btn.Checked += OnCellChecked;
                }
            }

            _statusText = (TextBlock)FindName("StatusText");
            _scorePlayer1Text = (TextBlock)FindName("ScorePlayer1");
            _scorePlayer2Text = (TextBlock)FindName("ScorePlayer2");
            _scoreTiesText = (TextBlock)FindName("ScoreTies");

            _scoreText = null;


            _winAnimation = (Storyboard)Resources["WinAnim"];
            _winAnimation.Completed += OnWinAnimationCompleted;

            _tieAnimation = (Storyboard)Resources["TieAnim"];
            _tieAnimation.Completed += OnTieAnimationCompleted;

            _resetAnimation = (Storyboard)Resources["ResetAnim"];
            _resetAnimation.Completed += OnResetAnimationCompleted;

            _progressAnimation = (Storyboard)Resources["ProgressAnim"];
            _progressFadeAnimation = (Storyboard)Resources["ProgressFadeAnim"];
            _progressFadeAnimation.Completed += OnProgressFadeAnimationCompleted;

            _scoreEndAnimation = (Storyboard)Resources["ScoreEndAnim"];
            _scoreHalfAnimation = (Storyboard)Resources["ScoreHalfAnim"];
            _scoreHalfAnimation.Completed += OnScoreHaldAnimationCompleted;

            _statusEndAnimation = (Storyboard)Resources["StatusEndAnim"];
            _statusHalfAnimation = (Storyboard)Resources["StatusHalfAnim"];
            _statusHalfAnimation.Completed += OnStatusHalfAnimationCompleted;

            _statusText.Text = "Player 1 Turn";
            _player = Player.First;
            _lastStarterPlayer = Player.First;
            _scorePlayer1 = 0;
            _scorePlayer2 = 0;
            _scoreTies = 0;
            _score = 0;

            StartGame();
        }

        private void StartGame()
        {
#if NOESIS
            PlaneProjection projection = (PlaneProjection)_boardPanel.Projection;
            projection.ClearAnimation(PlaneProjection.RotationYProperty);
#endif

            ScaleTransform t = (ScaleTransform)_boardPanel.RenderTransform;
            t.ClearAnimation(ScaleTransform.ScaleXProperty);
            t.ClearAnimation(ScaleTransform.ScaleYProperty);

            for (int row = 0; row < 3; ++row)
            {
                for (int col = 0; col < 3; ++col)
                {
                    Cell cell = _board[row, col];

                    cell.Player = Player.None;
                    cell.Button.ClearAnimation(UIElement.OpacityProperty);
                    cell.Button.IsEnabled = true;
                    cell.Button.IsChecked = false;

                    VisualStateManager.GoToState(cell.Button, PlayerState, false);
                }
            }

            _progressAnimation.Begin(this, true);
        }

        private void MarkCell(Cell cell)
        {
            cell.Player = _player;
            cell.Button.IsEnabled = false;

            VisualStateManager.GoToState(cell.Button, PlayerState, false);
        }

        bool HasWon(out string winPlay)
        {
            winPlay = "";

            for (int i = 0; i < 3; ++i)
            {
                if (PlayerCheckedRow(i))
                {
                    winPlay = string.Format("WinRow{0}", i + 1);
                    return true;
                }

                if (PlayerCheckedCol(i))
                {
                    winPlay = string.Format("WinCol{0}", i + 1);
                    return true;
                }
            }

            if (PlayerCheckedDiag(0, 2))
            {
                winPlay = "WinDiagLR";
                return true;
            }

            if (PlayerCheckedDiag(2, 0))
            {
                winPlay = "WinDiagRL";
                return true;
            }

            return false;
        }

        bool HasTied()
        {
            for (int row = 0; row < 3; ++row)
            {
                for (int col = 0; col < 3; ++col)
                {
                    if (_board[row, col].Player == Player.None)
                    {
                        return false;
                    }
                }
            }

            return true;
        }

        void WinGame(string winPlay)
        {
            for (int row = 0; row < 3; ++row)
            {
                for (int col = 0; col < 3; ++col)
                {
                    _board[row, col].Button.IsEnabled = false;
                }
            }

            _statusMessage = string.Format("Player {0} Wins", _player == Player.First ? 1 : 2);

            TimelineCollection timelines = _winAnimation.Children;
            Storyboard.SetTargetName((DependencyObject)timelines[0], winPlay);
            Storyboard.SetTargetName((DependencyObject)timelines[1], winPlay);
            Storyboard.SetTargetName((DependencyObject)timelines[2], winPlay);

            _progressFadeAnimation.Begin(this);
            _winAnimation.Begin(this);
            _statusHalfAnimation.Begin(this);
        }

        void TieGame()
        {
            _statusMessage = "Game Tied";

            _progressFadeAnimation.Begin(this);
            _tieAnimation.Begin(this);
            _statusHalfAnimation.Begin(this);
        }

        void SwitchPlayer()
        {
            if (_player == Player.First)
            {
                _player = Player.Second;
                _statusMessage = "Player 2 Turn";
            }
            else
            {
                _player = Player.First;
                _statusMessage = "Player 1 Turn";
            }

            for (int row = 0; row < 3; ++row)
            {
                for (int col = 0; col < 3; ++col)
                {
                    Cell cell = _board[row, col];
                    if (cell.Player == Player.None)
                    {
                        VisualStateManager.GoToState(cell.Button, PlayerState, false);
                    }
                }
            }

            _statusHalfAnimation.Begin(this);
        }

        void UpdateScoreAnimation(string targetName)
        {
            // Score Half
            Storyboard.SetTargetName((DependencyObject)_scoreHalfAnimation.Children[0], targetName);

            // Score End
            TimelineCollection timelines = _scoreEndAnimation.Children;
            Storyboard.SetTargetName((DependencyObject)timelines[0], targetName);
            Storyboard.SetTargetName((DependencyObject)timelines[1], targetName);
            Storyboard.SetTargetName((DependencyObject)timelines[2], targetName);
        }

        bool PlayerCheckedRow(int row)
        {
            return PlayerCheckedCell(row, 0) && PlayerCheckedCell(row, 1) && PlayerCheckedCell(row, 2);
        }

        bool PlayerCheckedCol(int col)
        {
            return PlayerCheckedCell(0, col) && PlayerCheckedCell(1, col) && PlayerCheckedCell(2, col);
        }

        bool PlayerCheckedDiag(int start, int end)
        {
            return PlayerCheckedCell(start, 0) && PlayerCheckedCell(1, 1) && PlayerCheckedCell(end, 2);
        }

        bool PlayerCheckedCell(int row, int col)
        {
            return _board[row, col].Player == _player;
        }


        private void OnBoardClicked(object sender, MouseButtonEventArgs e)
        {
            if (_player == Player.None)
            {
                if (_lastStarterPlayer == Player.First)
                {
                    _player = Player.Second;
                    _lastStarterPlayer = Player.Second;
                    _statusMessage = "Player 2 Turn";
                }
                else
                {
                    _player = Player.First;
                    _lastStarterPlayer = Player.First;
                    _statusMessage = "Player 1 Turn";
                }

                _resetAnimation.Begin(this);
                _statusHalfAnimation.Begin(this);
            }
        }

        private void OnCellChecked(object sender, RoutedEventArgs e)
        {
            ToggleButton btn = (ToggleButton)sender;
            Cell cell = (Cell)btn.Tag;

            MarkCell(cell);

            string winPlay;
            if (HasWon(out winPlay))
            {
                WinGame(winPlay);
            }
            else if (HasTied())
            {
                TieGame();
            }
            else
            {
                SwitchPlayer();
            }
        }

        private void OnWinAnimationCompleted(object sender, EventArgs e)
        {
            if (_player == Player.First)
            {
                _scoreText = _scorePlayer1Text;
                _score = ++_scorePlayer1;
                UpdateScoreAnimation("ScorePlayer1");
            }
            else
            {
                _scoreText = _scorePlayer2Text;
                _score = ++_scorePlayer2;
                UpdateScoreAnimation("ScorePlayer2");
            }

            _player = Player.None;

            _scoreHalfAnimation.Begin(this);
        }

        private void OnTieAnimationCompleted(object sender, EventArgs e)
        {
            _scoreText = _scoreTiesText;
            _score = ++_scoreTies;
            UpdateScoreAnimation("ScoreTies");

            _player = Player.None;

            _scoreHalfAnimation.Begin(this);
        }

        private void OnResetAnimationCompleted(object sender, EventArgs e)
        {
            StartGame();
        }

        private void OnProgressFadeAnimationCompleted(object sender, EventArgs e)
        {
            _progressAnimation.Stop(this);
        }

        private void OnScoreHaldAnimationCompleted(object sender, EventArgs e)
        {
            _scoreText.Text = _score.ToString();
            _scoreEndAnimation.Begin(this);
        }

        private void OnStatusHalfAnimationCompleted(object sender, EventArgs e)
        {
            _statusText.Text = _statusMessage;
            _statusEndAnimation.Begin(this);
        }

        private string PlayerState
        {
            get { return _player == Player.First ? "Player1" : "Player2"; }
        }

        class Cell
        {
            public Player Player { get; set; }
            public ToggleButton Button { get; set; }

            public override string ToString()
            {
                return Button != null ? Button.Name : base.ToString();
            }
        }

        Cell[,] _board;

        enum Player
        {
            None,
            First,
            Second
        };

        Player _player;
        Player _lastStarterPlayer;

        int _scorePlayer1;
        int _scorePlayer2;
        int _scoreTies;
        int _score;

        string _statusMessage;

        FrameworkElement _boardPanel;
        TextBlock _statusText;
        TextBlock _scorePlayer1Text;
        TextBlock _scorePlayer2Text;
        TextBlock _scoreTiesText;
        TextBlock _scoreText;

        Storyboard _winAnimation;
        Storyboard _tieAnimation;
        Storyboard _resetAnimation;
        Storyboard _progressAnimation;
        Storyboard _progressFadeAnimation;
        Storyboard _scoreEndAnimation;
        Storyboard _scoreHalfAnimation;
        Storyboard _statusEndAnimation;
        Storyboard _statusHalfAnimation;
    }

#if !NOESIS
    public static class DependencyObjectExtensions
    {
        public static void ClearAnimation(this DependencyObject d, DependencyProperty dp)
        {
            if (d is UIElement)
            {
                ((UIElement)d).BeginAnimation(dp, null);
            }
            else if (d is Animatable)
            {
                ((Animatable)d).BeginAnimation(dp, null);
            }
        }
    }
#endif
}
