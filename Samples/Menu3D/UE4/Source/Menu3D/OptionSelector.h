////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __MENU3D_OPTIONSELECTOR_H__
#define __MENU3D_OPTIONSELECTOR_H__


#include <NsCore/Noesis.h>
#include <NsCore/Ptr.h>
#include <NsGui/UserControl.h>


namespace Noesis
{
class RepeatButton;
struct NotifyCollectionChangedEventArgs;
template<class T> class ObservableCollection;
}

namespace Menu3D
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class OptionSelector final: public Noesis::UserControl
{
public:
    OptionSelector();

    Noesis::ObservableCollection<UIElement>* GetOptions() const;
    void SetOptions(Noesis::ObservableCollection<UIElement>* value);

    int GetSelectedIndex() const;
    void SetSelectedIndex(int value);

    Noesis::BaseComponent* GetSelectedOption() const;

private:
    void InitializeComponent();
    void OnInitialized(Noesis::BaseComponent*, const Noesis::EventArgs&);
    void OnPrev(Noesis::BaseComponent*, const Noesis::RoutedEventArgs&);
    void OnNext(Noesis::BaseComponent*, const Noesis::RoutedEventArgs&);
    void OnKeyDownHandler(Noesis::BaseComponent*, const Noesis::KeyEventArgs&);
    void OnOptionsChanged(Noesis::BaseComponent*, const Noesis::NotifyCollectionChangedEventArgs&);

    static void OnIndexChanged(Noesis::DependencyObject* d,
        const Noesis::DependencyPropertyChangedEventArgs&);

    void CycleNext();
    void UpdateSelectedOption();
    void UpdateButtons();

    int GetNumOptions() const;
    int GetLastIndex() const;
    int GetIndex() const;

    void SetSelectedOption(Noesis::BaseComponent* value);

private:
    Noesis::RepeatButton* _prevButton;
    Noesis::RepeatButton* _nextButton;
    Noesis::Ptr<Noesis::ObservableCollection<UIElement>> _options;

    static const Noesis::DependencyProperty* SelectedIndexProperty;
    static const Noesis::DependencyProperty* SelectedOptionProperty;

    NS_DECLARE_REFLECTION(OptionSelector, UserControl)
};

}


#endif
