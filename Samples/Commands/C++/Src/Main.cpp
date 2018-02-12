////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/RegisterComponent.h>
#include <NsCore/TypeId.h>
#include <NsCore/Delegate.h>
#include <NsApp/EmbeddedXamlProvider.h>
#include <NsApp/EmbeddedFontProvider.h>
#include <NsApp/ApplicationLauncher.h>
#include <NsApp/EntryPoint.h>
#include <NsApp/Application.h>
#include <NsApp/Window.h>

#include "DelegateCommand.h"
#include "NotifyPropertyChangedBase.h"
#include "App.xaml.bin.h"
#include "MainWindow.xaml.bin.h"
#include "Aero Matics Regular.ttf.bin.h"


using namespace Noesis;
using namespace NoesisApp;


namespace Commands
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class ViewModel: public NotifyPropertyChangedBase
{
public:
    ViewModel()
    {
        _command = *new DelegateCommand(MakeDelegate(this, &ViewModel::SayHello));
    }

    const char* GetInput() const
    {
        return _input.c_str();
    }

    void SetInput(const char* input)
    {
        _input = input;
    }

    const char* GetOutput() const
    {
        return _output.c_str();
    }

    void SetOutput(const char* output)
    {
        if (_output != output)
        {
            _output = output;
            OnPropertyChanged("Output");
        }
    }

    DelegateCommand* GetSayHelloCommand() const
    {
        return _command.GetPtr();
    }

private:
    void SayHello(BaseComponent* param_)
    {
        if (Boxing::CanUnbox<NsString>(param_))
        {
            const char* param = Boxing::Unbox<NsString>(param_).c_str();

            char text[256];
            String::FormatBuffer(text, sizeof(text), "Hello, %s (%s)", _input.c_str(), param);
            SetOutput(text);
        }
    }

private:
    Ptr<DelegateCommand> _command;

    NsString _input;
    NsString _output;

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
        NsRegisterComponent<Commands::ViewModel>();
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
