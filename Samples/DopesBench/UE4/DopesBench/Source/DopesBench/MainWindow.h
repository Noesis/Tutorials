////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __DOPESBENCH_MAINWINDOW_H__
#define __DOPESBENCH_MAINWINDOW_H__


#include <NsCore/Noesis.h>
#include <NsCore/Delegate.h>
#include <NsCore/Ptr.h>
#include <NsGui/Page.h>
#include <NsGui/Collection.h>
#include <NsGui/INotifyPropertyChanged.h>
#include <NsDrawing/Color.h>

namespace Noesis
{
class Button;
class Canvas;
class ItemsControl;
class TextBlock;
}

namespace DopesBench
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class Item final: public Noesis::BaseComponent, public Noesis::INotifyPropertyChanged
{
public:
    float GetTop() const;
    void SetTop(float value);

    float GetLeft() const;
    void SetLeft(float value);

    float GetRotation() const;
    void SetRotation(float value);

    const Noesis::Color& GetColor() const;
    void SetColor(const Noesis::Color& value);

    Noesis::PropertyChangedEventHandler& PropertyChanged() override;

    NS_IMPLEMENT_INTERFACE_FIXUP

private:
    float _top;
    float _left;
    float _rotation;
    Noesis::Color _color;
    Noesis::PropertyChangedEventHandler _changed;

    NS_DECLARE_REFLECTION(Item, Noesis::BaseComponent)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class MainWindow final: public Noesis::Page
{
public:
    MainWindow();

private:
    void InitializeComponent();
    bool ConnectEvent(Noesis::BaseComponent* source, const char* event, const char* handler) override;
    void OnRendering(Noesis::IView*);

    void TestBuild();
    void TestReuse();
    void TestBinding();
    void TestChange();

    void StartTest(int test);

    void Stop_Clicked(Noesis::BaseComponent*, const Noesis::RoutedEventArgs&);
    void Build_Clicked(Noesis::BaseComponent*, const Noesis::RoutedEventArgs&);
    void Reuse_Clicked(Noesis::BaseComponent*, const Noesis::RoutedEventArgs&);
    void Binding_Clicked(Noesis::BaseComponent*, const Noesis::RoutedEventArgs&);
    void Change_Clicked(Noesis::BaseComponent*, const Noesis::RoutedEventArgs&);

private:
    const int max = 600;

    int processed = 0;

    uint64 prevTicks = 0;
    int prevProcessed = 0;
    double avgSum = 0;
    int avgN = 0;

    Noesis::Button* stop;
    Noesis::Button* build;
    Noesis::Button* reuse;
    Noesis::Button* binding;
    Noesis::Button* change;

    Noesis::Canvas* canvas;
    Noesis::ItemsControl* items;
    Noesis::TextBlock* dopes;

    Noesis::Ptr<Noesis::Collection<Item>> list;

    int runningTest;

    NS_DECLARE_REFLECTION(MainWindow, Noesis::Page)
};

}


#endif
