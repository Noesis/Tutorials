using System;
using System.Windows.Input;

namespace MenuDemo
{
	public static class CommandHelper
	{
		public static void TryExecute(ICommand command)
        {
            if (command != null)
            {
                command.Execute(null);
            }
        }
	}
	
	public class DelegateCommand : ICommand
	{
		private readonly Action<object> action;

		public DelegateCommand(Action<object> action)
		{
			this.action = action;
		}

		public bool CanExecute(object parameter)
		{
			return true;
		}

		public void Execute(object parameter)
		{
			action(parameter);
		}
		
		public event EventHandler CanExecuteChanged;
	}
}
