////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/RegisterComponent.h>
#include <NsCore/TypeId.h>
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
        if (!String::Equals(_input, value))
        {
            String::Copy(_input, sizeof(_input), value);
            OnPropertyChanged("Input");
        }
    }

    const char* GetOutput() const
    {
        return _output;
    }

    void SetOutput(const char* value)
    {
        if (!String::Equals(_output, value))
        {
            String::Copy(_output, sizeof(_output), value);
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
        if (Boxing::CanUnbox<NsString>(param_))
        {
            const char* param = Boxing::Unbox<NsString>(param_).c_str();

            char text[512];
            snprintf(text, sizeof(text), "Hello, %s (%s)", _input, param);
            SetOutput(text);
        }
    }

private:
    DelegateCommand _command;
    char _input[256] = "";
    char _output[256] = "";

    NS_IMPLEMENT_INLINE_REFLECTION(ViewModel, NotifyPropertyChangedBase)
    {
        NsMeta<TypeId>("Commands.ViewModel");
        NsProp("Input", &ViewModel::GetInput, &ViewModel::SetInput);
        NsProp("Output", &ViewModel::GetOutput, &ViewModel::SetOutput);
        NsProp("SayHelloCommand", &ViewModel::GetSayHelloCommand);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class App final: public Application
{
    NS_IMPLEMENT_INLINE_REFLECTION(App, Application)
    {
        NsMeta<TypeId>("Commands.App");
    }
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

    NS_IMPLEMENT_INLINE_REFLECTION(MainWindow, Window)
    {
        NsMeta<TypeId>("Commands.MainWindow");
    }
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        NsRegisterComponent<Commands::App>();
        NsRegisterComponent<Commands::MainWindow>();
    }

    Ptr<XamlProvider> GetXamlProvider() const override
    {
        EmbeddedXaml xamls[] = 
        {
            { "App.xaml", App_xaml, sizeof(App_xaml) },
            { "MainWindow.xaml", MainWindow_xaml, sizeof(MainWindow_xaml) }
        };

        return *new EmbeddedXamlProvider(xamls, NS_COUNTOF(xamls));
    }

    Ptr<FontProvider> GetFontProvider() const override
    {
        EmbeddedFont fonts[] =
        {
            { "", Aero_Matics_Regular_ttf, sizeof(Aero_Matics_Regular_ttf) }
        };

        return *new EmbeddedFontProvider(fonts, NS_COUNTOF(fonts));
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
