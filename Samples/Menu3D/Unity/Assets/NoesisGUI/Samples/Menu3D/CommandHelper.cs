using System;
using System.Windows.Input;

namespace Menu3D
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
}
