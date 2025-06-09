////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __LOCALIZATION_VIEWMODEL_H__
#define __LOCALIZATION_VIEWMODEL_H__


#include <NsCore/Noesis.h>
#include <NsCore/Ptr.h>
#include <NsCore/String.h>
#include <NsApp/NotifyPropertyChangedBase.h>
#include <NsGui/TextProperties.h>

#include "NsGui/Uri.h"


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
    Language(const char* name, const char* sourcePath, Noesis::FlowDirection flow);

    const char* GetName() const;
    const Noesis::Uri& GetSource() const;
    Noesis::FlowDirection GetFlowDirection() const;

private:
    Noesis::String _name;
    Noesis::Uri _source;
    Noesis::FlowDirection _flow;

    NS_DECLARE_REFLECTION(Language, Noesis::BaseComponent)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class ViewModel final: public NoesisApp::NotifyPropertyChangedBase
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
    Language* _selectedLanguage;
    float _soundLevel;
    float _musicLevel;

    NS_DECLARE_REFLECTION(ViewModel, NotifyPropertyChangedBase)
};

}


#endif
