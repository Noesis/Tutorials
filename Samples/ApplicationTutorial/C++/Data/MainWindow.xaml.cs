using System.Windows;


namespace RssReader
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private string[] _urls =
        {
            "https://goo.gl/fDQNZa",
            "https://goo.gl/t256CG",
            "https://goo.gl/mJcay9"
        };

        private string[] _titles =
        {
            "Monkey Island 1",
            "Monkey Island 2",
            "Monkey Island 3"
        };

        private string[] _bodies =
        {
            "The Secret of Monkey Island is a 1990 point-and-click graphic adventure game developed and " +
            "published by Lucasfilm Games.It takes place in a fantastical version of the Caribbean during " +
            "the age of piracy.The player assumes the role of Guybrush Threepwood, a young man who dreams " +
            "of becoming a pirate and explores fictional islands while solving puzzles.",

            "Monkey Island 2: LeChuck's Revenge is an adventure game developed and published by LucasArts " +
            "in 1991. It was the second game of the Monkey Island series, following The Secret of Monkey " +
            "Island, and the sixth LucasArts game to use the SCUMM engine. It was the first game to use " +
            "the iMUSE sound system.",

            "The Curse of Monkey Island is an adventure game developed and published by LucasArts, and " +
            "the third game in the Monkey Island series. It was released in 1997 and followed the " +
            "successful games The Secret of Monkey Island and Monkey Island 2: LeChuck's Revenge. The " +
            "game is the twelfth and last LucasArts game to use the SCUMM engine, which was extensively " +
            "upgraded for its last outing before being replaced by the GrimE engine for the next game in " +
            "the series, Escape from Monkey Island. The Curse of Monkey Island is the first Monkey " +
            "Island game to include voice acting, and has a more cartoon-ish graphic style than the " +
            "earlier games."
        };

        public MainWindow()
        {
            InitializeComponent();

            this.Address.Text = _urls[0];
            this.EntryTitle.Text = _titles[0];
            this.EntryDesc.Text = _bodies[0];
        }

        void OnPrevClicked(object sender, RoutedEventArgs e)
        {
            _index = _index == 0 ? 2 : _index - 1;
            this.Address.Text = _urls[_index];
            this.EntryTitle.Text = _titles[_index];
            this.EntryDesc.Text = _bodies[_index];
        }

        void OnNextClicked(object sender, RoutedEventArgs e)
        {
            _index = _index == 2 ? 0 : _index + 1;
            this.Address.Text = _urls[_index];
            this.EntryTitle.Text = _titles[_index];
            this.EntryDesc.Text = _bodies[_index];
        }

        private int _index = 0;
    }
}
