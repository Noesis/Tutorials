using System;
using System.ComponentModel;

namespace TicTacToe
{
    /// <summary>
    /// Base class implementing INotifyPropertyChanged
    /// </summary>
    public class NotifyPropertyChangedBase: INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged(string name)
        {
            var handler = PropertyChanged;
            if (handler != null)
            {
                handler(this, new PropertyChangedEventArgs(name));
            }
        }
    }
}