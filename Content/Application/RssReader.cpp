#include "pch.h"


using namespace Noesis;


const NsChar* const gTitles[] =
{
    "Monkey Island 1",
    "Monkey Island 2",
    "Monkey Island 3"
};

const NsChar* const gBodies[] =
{
    "The Secret of Monkey Island is a 1990 point-and-click graphic adventure game developed and "
    "published by Lucasfilm Games.It takes place in a fantastical version of the Caribbean during "
    "the age of piracy.The player assumes the role of Guybrush Threepwood, a young man who dreams "
    "of becoming a pirate and explores fictional islands while solving puzzles",
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
    "earlier games"
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class RssReader: public Window
{
public:
    RssReader(): _index(0) {}

    void OnInit()
    {
        ParentClass::OnInit();
        Update();
    }

    void OnGoToClicked(BaseComponent* sender, const RoutedEventArgs& e) {}

    void OnPrevClicked(BaseComponent* sender, const RoutedEventArgs& e)
    {
        _index = _index == 0 ? 2 : _index -  1;
        Update();
    }

    void OnNextClicked(BaseComponent* sender, const RoutedEventArgs& e)
    {
        _index = _index == 2 ? 0 : _index +  1;
        Update();
    }

private:
    void Update()
    {
        TextBlock* title = NsStaticCast<TextBlock*>(FindName("Title"));
        title->SetText(gTitles[_index]);
        
        TextBlock* desc = NsStaticCast<TextBlock*>(FindName("Desc"));
        desc->SetText(gBodies[_index]);
    }

private:
    NsUInt _index;

    NS_IMPLEMENT_INLINE_REFLECTION(RssReader, Window)
    {
        NsMeta<TypeId>("RssReader");
        NsFunc("OnGoToClicked", &RssReader::OnGoToClicked);
        NsFunc("OnPrevClicked", &RssReader::OnPrevClicked);
        NsFunc("OnNextClicked", &RssReader::OnNextClicked);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" NS_DLL_EXPORT void NsRegisterReflection(ComponentFactory*, NsBool registerComponents)
{
    NS_REGISTER_COMPONENT(RssReader)
}
