////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __LOCALIZATION_VIEWMODEL_H__
#define __LOCALIZATION_VIEWMODEL_H__


#include <NsCore/Noesis.h>
#include <NsCore/Ptr.h>
#include <NsCore/String.h>

#include "NotifyPropertyChangedBase.h"


namespace Noesis
{
class ResourceDictionary;
template<class T> class ObservableCollection;
}

namespace Localization
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class Language final: public Noesis::BaseComponent
{
public:
    Language(const char* name, Noesis::ResourceDictionary* resources);

    const char* GetName() const;
    Noesis::ResourceDictionary* GetResources() const;

private:
    NsString _name;
    Noesis::Ptr<Noesis::ResourceDictionary> _resources;

    NS_DECLARE_REFLECTION(Language, Noesis::BaseComponent)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class ViewModel final: public NotifyPropertyChangedBase
{
public:
    ViewModel();

    Noesis::ObservableCollection<Language>* GetLanguages() const;

    void SetSelectedLanguage(Language* language);
    Language* GetSelectedLanguage() const;

    void SetSoundLevel(float level);
    float GetSoundLevel() const;

    void SetMusicLevel(float level);
    float GetMusicLevel() const;

private:
    Noesis::Ptr<Noesis::ObservableCollection<Language>> _languages;
    Noesis::Ptr<Language> _selectedLanguage;
    float _soundLevel;
    float _musicLevel;

    NS_DECLARE_REFLECTION(ViewModel, NotifyPropertyChangedBase)
};

}


#endif
