////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/RegisterComponent.h>
#include <NsCore/Delegate.h>
#include <NsGui/IntegrationAPI.h>
#include <NsApp/EmbeddedXamlProvider.h>
#include <NsApp/EmbeddedFontProvider.h>
#include <NsApp/ApplicationLauncher.h>
#include <NsApp/EntryPoint.h>
#include <NsApp/Application.h>
#include <NsApp/Window.h>
#include <NsApp/DelegateCommand.h>
#include <NsApp/NotifyPropertyChangedBase.h>

#include "App.xaml.bin.h"
#include "MainWindow.xaml.bin.h"
#include "Aero Matics Regular.ttf.bin.h"


using namespace Noesis;
using namespace NoesisApp;


namespace Commands
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class ViewModel: public NoesisApp::NotifyPropertyChangedBase
{
public:
    ViewModel()
    {
        _command.SetExecuteFunc(MakeDelegate(this, &ViewModel::SayHello));
    }

    const char* GetInput() const
    {
        return _input;
    }

    void SetInput(const char* value)
    {
        if (!StrEquals(_input, value))
        {
            StrCopy(_input, sizeof(_input), value);
            OnPropertyChanged("Input");
        }
    }

    const char* GetOutput() const
    {
        return _output;
    }

    void SetOutput(const char* value)
    {
        if (!StrEquals(_output, value))
        {
            StrCopy(_output, sizeof(_output), value);
            OnPropertyChanged("Output");
        }
    }

    const DelegateCommand* GetSayHelloCommand() const
    {
        return &_command;
    }

private:
    void SayHello(BaseComponent* param_)
    {
        if (Boxing::CanUnbox<String>(param_))
        {
            const char* param = Boxing::Unbox<String>(param_).Str();

            char text[512];
            snprintf(text, sizeof(text), "Hello, %s (%s)", _input, param);
            SetOutput(text);
        }
    }

private:
    DelegateCommand _command;
    char _input[256] = "";
    char _output[256] = "";

    NS_IMPLEMENT_INLINE_REFLECTION(ViewModel, NotifyPropertyChangedBase, "Commands.ViewModel")
    {
        NsProp("Input", &ViewModel::GetInput, &ViewModel::SetInput);
        NsProp("Output", &ViewModel::GetOutput, &ViewModel::SetOutput);
        NsProp("SayHelloCommand", &ViewModel::GetSayHelloCommand);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class App final: public Application
{
    NS_IMPLEMENT_INLINE_REFLECTION_(App, Application,"Commands.App")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class MainWindow final: public Window
{
public:
    MainWindow()
    {
        Initialized() += MakeDelegate(this, &MainWindow::OnInitialized);
        InitializeComponent();
    }

    void InitializeComponent()
    {
        Noesis::GUI::LoadComponent(this, "MainWindow.xaml");
    }

    void OnInitialized(BaseComponent*, const EventArgs&)
    {
        SetDataContext(MakePtr<ViewModel>());
    }

    NS_IMPLEMENT_INLINE_REFLECTION_(MainWindow, Window, "Commands.MainWindow")
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        RegisterComponent<Commands::App>();
        RegisterComponent<Commands::MainWindow>();
    }

    Noesis::Ptr<XamlProvider> GetXamlProvider() const override
    {
        EmbeddedXaml xamls[] = 
        {
            { "App.xaml", App_xaml },
            { "MainWindow.xaml", MainWindow_xaml }
        };

        return *new EmbeddedXamlProvider(xamls);
    }

    Noesis::Ptr<FontProvider> GetFontProvider() const override
    {
        EmbeddedFont fonts[] =
        {
            { "", Aero_Matics_Regular_ttf }
        };

        return *new EmbeddedFontProvider(fonts);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
int NsMain(int argc, char **argv)
{
    AppLauncher launcher;
    launcher.SetArguments(argc, argv);
    launcher.SetApplicationFile("App.xaml");
    return launcher.Run();
}
