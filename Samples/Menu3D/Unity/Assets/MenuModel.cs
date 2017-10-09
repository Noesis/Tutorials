#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
#else
using System;
using System.Windows;
using System.Windows.Controls;
#endif
using System.Windows.Input;

namespace Menu3D
{
    public class MenuModel
    {
        public ICommand Start { get; private set; }
        public ICommand StartCasual { get; private set; }
        public ICommand StartNormal { get; private set; }
        public ICommand StartVeteran { get; private set; }
        public ICommand Settings { get; private set; }
        public ICommand Exit { get; private set; }
        public ICommand Back { get; private set; }

        public MenuModel(MainMenu main, StartMenu start, SettingsMenu settings)
        {
            Start = new DelegateCommand(OnStart);
            StartCasual = new DelegateCommand(OnStartCasual);
            StartNormal = new DelegateCommand(OnStartNormal);
            StartVeteran = new DelegateCommand(OnStartVeteran);
            Settings = new DelegateCommand(OnSettings);
            Exit = new DelegateCommand(OnExit);
            Back = new DelegateCommand(OnBack);

            _mainMenu = main;
            _startMenu = start;
            _settingsMenu = settings;
            
            _state = State.Main;
        }

        enum State
        {
            Main,
            Start,
            Settings,
            Exit
        }

        private State _state;

        private void OnStart(object parameter)
        {
            _state = State.Start;

            _mainMenu.FadeOut();
            _startMenu.FadeIn();
        }

        private void OnStartCasual(object parameter)
        {
            #if NOESIS
            UnityEngine.Debug.Log("Start Casual");
            #else
            Console.WriteLine("Start Casual");
            #endif
        }

        private void OnStartNormal(object parameter)
        {
            #if NOESIS
            UnityEngine.Debug.Log("Start Normal");
            #else
            Console.WriteLine("Start Normal");
            #endif
        }

        private void OnStartVeteran(object parameter)
        {
            #if NOESIS
            UnityEngine.Debug.Log("Start Veteran");
            #else
            Console.WriteLine("Start Veteran");
            #endif
        }

        private void OnSettings(object parameter)
        {
            _state = State.Settings;

            _mainMenu.FadeOut();
            _settingsMenu.FadeIn();
        }

        private void OnExit(object parameter)
        {
            #if NOESIS
            UnityEngine.Debug.Log("Exiting game");
            #endif

            _state = State.Exit;
            #if NOESIS
            UnityEngine.Application.Quit();
            #else
            Application.Current.Shutdown(0);
            #endif
        }

        private void OnBack(object parameter)
        {
            switch (_state)
            {
                case State.Main:
                {
                    OnExit(null);
                    break;
                }
                case State.Start:
                {
                    _state = State.Main;

                    _startMenu.FadeOut();
                    _mainMenu.FadeIn();
                    break;
                }
                case State.Settings:
                {
                    _state = State.Main;

                    _settingsMenu.FadeOut();
                    _mainMenu.FadeIn();
                    break;
                }
            }
        }

        #region Private members
        private MainMenu _mainMenu;
        private StartMenu _startMenu;
        private SettingsMenu _settingsMenu;
        #endregion
    }
}
