#if UNITY_STANDALONE || UNITY_ANDROID || UNITY_IOS || UNITY_WINRT_8_1
#define UNITY
#endif

#if UNITY
using Noesis;
#else
using System;
using System.Windows;
using System.Windows.Controls;
#endif
using System.Windows.Input;

namespace MenuDemo
{
    public class MenuDemoModel
    {
        public ICommand Start { get; private set; }
        public ICommand StartCasual { get; private set; }
        public ICommand StartNormal { get; private set; }
        public ICommand StartVeteran { get; private set; }
        public ICommand Settings { get; private set; }
        public ICommand Exit { get; private set; }
        public ICommand Back { get; private set; }

        private MainMenu _mainMenu;
        private StartMenu _startMenu;
        private SettingsMenu _settingsMenu;

        public MenuDemoModel(MainMenu main, StartMenu start, SettingsMenu settings)
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
			#if UNITY
            UnityEngine.Debug.Log("Start Casual");
			#endif
        }

        private void OnStartNormal(object parameter)
        {
			#if UNITY
            UnityEngine.Debug.Log("Start Normal");
			#endif
        }

        private void OnStartVeteran(object parameter)
        {
			#if UNITY
            UnityEngine.Debug.Log("Start Veteran");
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
			#if UNITY
            UnityEngine.Debug.Log("Exiting game");
			#endif

            _state = State.Exit;
			#if UNITY
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
    }
}
