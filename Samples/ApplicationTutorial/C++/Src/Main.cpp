////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionImplementEmpty.h>
#include <NsCore/RegisterComponent.h>
#include <NsGui/Button.h>
#include <NsGui/IntegrationAPI.h>
#include <NsGui/TextBlock.h>
#include <NsGui/TextBox.h>
#include <NsApp/EmbeddedXamlProvider.h>
#include <NsApp/EmbeddedFontProvider.h>
#include <NsApp/ApplicationLauncher.h>
#include <NsApp/EntryPoint.h>
#include <NsApp/Application.h>
#include <NsApp/Window.h>
#include <NsApp/RichText.h>

#include "App.xaml.bin.h"
#include "MainWindow.xaml.bin.h"
#include "Resources.xaml.bin.h"
#include "Montserrat-Bold.ttf.bin.h"
#include "Montserrat-Medium.ttf.bin.h"
#include "Montserrat-SemiBold.ttf.bin.h"


using namespace Noesis;
using namespace NoesisApp;


static const char* const gURLs[] =
{
    "https://goo.gl/fDQNZa",
    "https://goo.gl/t256CG",
    "https://goo.gl/mJcay9"
};

static const char* const gTitles[] =
{
    "Monkey Island 1",
    "Monkey Island 2",
    "Monkey Island 3"
};

static const char* const gBodies[] =
{
    "The Secret of Monkey Island is a 1990 [b]point and click[/b] graphic adventure game developed and "
    "published by [url='https://en.wikipedia.org/wiki/Lucasfilm_Games']Lucasfilm Games[/url]. It "
    "takes place in a fantastical version of the Caribbean during the age of piracy. The player "
    "assumes the funny role of [b]Guybrush Threepwood[/b], a man who dreams of becoming a pirate "
    "while exploring fictional islands and solving puzzles.",

    "Monkey Island 2: LeChuck's Revenge is an [b]adventure game[/b] developed and published by "
    "[url='https://en.wikipedia.org/wiki/LucasArts']LucasArts[/url] in 1991. It was the second "
    "game of the Monkey Island series, following The Secret of Monkey Island, and the sixth "
    "LucasArts game to use the [b]SCUMM[/b] game engine. It was the first game to use the "
    "[b]iMUSE[/b] sound system.",

    "The Curse of Monkey Island was the adventure video game developed and published by "
    "[url='https://en.wikipedia.org/wiki/LucasArts']LucasArts[/url], and the third game in the "
    "'[b]Monkey Island[/b]' series. It was released in 1997 and followed the successful games The "
    "Secret of Monkey Island and Monkey Island 2: LeChuck's Revenge. The game is the twelfth and "
    "last game of LucasArts to use the [b]SCUMM[/b] engine, which was extensively upgraded for its "
    "last outing before being replaced by the new [b]GrimE[/b] engine for the next game in the "
    "series, Escape from Monkey Island. The Curse of Monkey Island is the first 'Monkey Island' "
    "game to include voice acting, and has a more cartoon-ish graphic style than the earlier games."
};

namespace RssReader
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class App final: public Application
{
    NS_IMPLEMENT_INLINE_REFLECTION_(App, Application, "RssReader.App")
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

private:
    void InitializeComponent()
    {
        Noesis::GUI::LoadComponent(this, "MainWindow.xaml");
    }

    bool ConnectField(BaseComponent* object, const char* name) override
    {
        NS_CONNECT_FIELD(_title, "EntryTitle");
        NS_CONNECT_FIELD(_desc, "EntryDesc");
        NS_CONNECT_FIELD(_url, "Address");

        return false;
    }

    bool ConnectEvent(BaseComponent* source, const char* event, const char* handler) override
    {
        NS_CONNECT_EVENT(Button, Click, OnPrevClicked);
        NS_CONNECT_EVENT(Button, Click, OnNextClicked);

        return false;
    }

    void OnInitialized(BaseComponent*, const EventArgs&)
    {
        SetData();
    }

    void SetData()
    {
        _title->SetText(gTitles[_index]);
        RichText::SetText(_desc, gBodies[_index]);
        _url->SetText(gURLs[_index]);
    }

    void OnPrevClicked(BaseComponent*, const RoutedEventArgs&)
    {
        _index = _index == 0 ? 2 : _index - 1;
        SetData();
    }

    void OnNextClicked(BaseComponent*, const RoutedEventArgs&)
    {
        _index = _index == 2 ? 0 : _index + 1;
        SetData();
    }

private:
    int _index = 0;

    TextBlock* _title = nullptr;
    TextBlock* _desc = nullptr;
    TextBox* _url = nullptr;

    NS_IMPLEMENT_INLINE_REFLECTION_(MainWindow, Window, "RssReader.MainWindow")
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        RegisterComponent<RssReader::App>();
        RegisterComponent<RssReader::MainWindow>();
    }

    Noesis::Ptr<XamlProvider> GetXamlProvider() const override
    {
        EmbeddedXaml xamls[] = 
        {
            { "App.xaml", App_xaml },
            { "MainWindow.xaml", MainWindow_xaml },
            { "Resources.xaml", Resources_xaml }
        };

        return *new EmbeddedXamlProvider(xamls);
    }

    Noesis::Ptr<FontProvider> GetFontProvider() const override
    {
        EmbeddedFont fonts[] =
        {
            { "", Montserrat_Bold_ttf },
            { "", Montserrat_Medium_ttf },
            { "", Montserrat_SemiBold_ttf }
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
