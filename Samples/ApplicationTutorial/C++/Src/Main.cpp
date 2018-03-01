////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/RegisterComponent.h>
#include <NsCore/TypeId.h>
#include <NsGui/Button.h>
#include <NsGui/IntegrationAPI.h>
#include <NsGui/TextBlock.h>
#include <NsApp/EmbeddedXamlProvider.h>
#include <NsApp/EmbeddedFontProvider.h>
#include <NsApp/ApplicationLauncher.h>
#include <NsApp/EntryPoint.h>
#include <NsApp/Application.h>
#include <NsApp/Window.h>

#include "App.xaml.bin.h"
#include "MainWindow.xaml.bin.h"
#include "Roboto-Regular.ttf.bin.h"
#include "Roboto-Bold.ttf.bin.h"


using namespace Noesis;
using namespace NoesisApp;


static const char* const gTitles[] =
{
    "Monkey Island 1",
    "Monkey Island 2",
    "Monkey Island 3"
};

static const char* const gBodies[] =
{
    "The Secret of Monkey Island is a 1990 point-and-click graphic adventure game developed and "
    "published by Lucasfilm Games.It takes place in a fantastical version of the Caribbean during "
    "the age of piracy.The player assumes the role of Guybrush Threepwood, a young man who dreams "
    "of becoming a pirate and explores fictional islands while solving puzzles.",

    "Monkey Island 2: LeChuck's Revenge is an adventure game developed and published by LucasArts "
    "in 1991. It was the second game of the Monkey Island series, following The Secret of Monkey "
    "Island, and the sixth LucasArts game to use the SCUMM engine. It was the first game to use "
    "the iMUSE sound system.",

    "The Curse of Monkey Island is an adventure game developed and published by LucasArts, and "
    "the third game in the Monkey Island series. It was released in 1997 and followed the "
    "successful games The Secret of Monkey Island and Monkey Island 2: LeChuck's Revenge. The "
    "game is the twelfth and last LucasArts game to use the SCUMM engine, which was extensively "
    "upgraded for its last outing before being replaced by the GrimE engine for the next game in "
    "the series, Escape from Monkey Island. The Curse of Monkey Island is the first Monkey "
    "Island game to include voice acting, and has a more cartoon-ish graphic style than the "
    "earlier games."
};


namespace RssReader
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class App final: public Application
{
    NS_IMPLEMENT_INLINE_REFLECTION(App, Application)
    {
        NsMeta<TypeId>("RssReader.App");
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class MainWindow final: public Window
{
public:
    MainWindow(): _index(0)
    {
        InitializeComponent();

        _title = FindName<TextBlock>("EntryTitle");
        _desc = FindName<TextBlock>("EntryDesc");
        _title->SetText(gTitles[0]);
        _desc->SetText(gBodies[0]);
    }

private:
    void InitializeComponent()
    {
        Noesis::GUI::LoadComponent(this, "MainWindow.xaml");
    }

    bool ConnectEvent(BaseComponent* source, const char* event, const char* handler) override
    {
        NS_CONNECT_EVENT(Button, Click, OnGoToClicked);
        NS_CONNECT_EVENT(Button, Click, OnPrevClicked);
        NS_CONNECT_EVENT(Button, Click, OnNextClicked);
        return false;
    }

    void OnGoToClicked(BaseComponent* /*sender*/, const RoutedEventArgs& /*e*/)
    {
    }

    void OnPrevClicked(BaseComponent* /*sender*/, const RoutedEventArgs& /*e*/)
    {
        _index = _index == 0 ? 2 : _index - 1;
        _title->SetText(gTitles[_index]);
        _desc->SetText(gBodies[_index]);
    }

    void OnNextClicked(BaseComponent* /*sender*/, const RoutedEventArgs& /*e*/)
    {
        _index = _index == 2 ? 0 : _index + 1;
        _title->SetText(gTitles[_index]);
        _desc->SetText(gBodies[_index]);
    }

private:
    int _index;
    TextBlock* _title;
    TextBlock* _desc;

    NS_IMPLEMENT_INLINE_REFLECTION(MainWindow, Window)
    {
        NsMeta<TypeId>("RssReader.MainWindow");
    }
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        NsRegisterComponent<RssReader::App>();
        NsRegisterComponent<RssReader::MainWindow>();
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
            { "", Roboto_Regular_ttf, sizeof(Roboto_Regular_ttf) },
            { "", Roboto_Bold_ttf, sizeof(Roboto_Bold_ttf) }
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
