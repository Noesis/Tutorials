////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "ViewModel.h"

#include <NsCore/ReflectionImplement.h>
#include <NsGui/ResourceDictionary.h>
#include <NsGui/ObservableCollection.h>
#include <NsGui/IntegrationAPI.h>


using namespace Localization;
using namespace Noesis;


////////////////////////////////////////////////////////////////////////////////////////////////////
Language::Language(const char* name, ResourceDictionary* resources): _name(name),
    _resources(resources)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* Language::GetName() const
{
    return _name.c_str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ResourceDictionary* Language::GetResources() const
{
    return _resources;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_IMPLEMENT_REFLECTION(Language)
{
    NsProp("Name", &Language::GetName);
    NsProp("Resources", &Language::GetResources);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ViewModel::ViewModel()
{
    _languages = *new ObservableCollection<Language>();
    _languages->Add(MakePtr<Language>("English",
        GUI::LoadXaml<ResourceDictionary>("Language-en.xaml")));
    _languages->Add(MakePtr<Language>("Fran""\xC3\xA7""ais",
        GUI::LoadXaml<ResourceDictionary>("Language-fr.xaml")));
    _languages->Add(MakePtr<Language>("\xE6\x97\xA5\xE6\x9C\xAC\xE8\xAA\x9E",
        GUI::LoadXaml<ResourceDictionary>("Language-jp.xaml")));

    SetSelectedLanguage(_languages->Get(0));

    SetSoundLevel(100.0f);
    SetMusicLevel(70.0f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ObservableCollection<Language>* ViewModel::GetLanguages() const
{
    return _languages;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::SetSelectedLanguage(Language* language)
{
    if (_selectedLanguage != language)
    {
        _selectedLanguage.Reset(language);
        OnPropertyChanged("SelectedLanguage");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Language* ViewModel::GetSelectedLanguage() const
{
    return _selectedLanguage;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::SetSoundLevel(float level)
{
    if (_soundLevel != level)
    {
        _soundLevel = level;
        OnPropertyChanged("SoundLevel");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float ViewModel::GetSoundLevel() const
{
    return _soundLevel;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::SetMusicLevel(float level)
{
    if (_musicLevel != level)
    {
        _musicLevel = level;
        OnPropertyChanged("MusicLevel");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float ViewModel::GetMusicLevel() const
{
    return _musicLevel;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_IMPLEMENT_REFLECTION(ViewModel)
{
    NsProp("Languages", &ViewModel::GetLanguages);
    NsProp("SelectedLanguage", &ViewModel::GetSelectedLanguage, &ViewModel::SetSelectedLanguage);
    NsProp("SoundLevel", &ViewModel::GetSoundLevel, &ViewModel::SetSoundLevel);
    NsProp("MusicLevel", &ViewModel::GetMusicLevel, &ViewModel::SetMusicLevel);
}
