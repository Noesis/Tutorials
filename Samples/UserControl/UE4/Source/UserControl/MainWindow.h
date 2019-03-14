////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "NumericUpDown.h"

namespace UserControl
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class MainWindow : public Noesis::UserControl
{
public:
    MainWindow()
    {
        InitializeComponent();

        _bg = FindName<Noesis::SolidColorBrush>("BgColor");
        _fg = FindName<Noesis::SolidColorBrush>("FgColor");
    }

private:
    void InitializeComponent()
    {
        Noesis::GUI::LoadComponent(this, "/Game/MainWindow.xaml");
    }

    // This code-behind is needed because MultiBindings are not yet supported
    // http://stackoverflow.com/questions/1978316/binding-r-g-b-properties-of-color-in-wpf
    bool ConnectEvent(Noesis::BaseComponent* source, const char* event, const char* handler) override
    {
        NS_CONNECT_EVENT(NumericUpDown, ValueChanged, BgR_ValueChanged);
        NS_CONNECT_EVENT(NumericUpDown, ValueChanged, BgG_ValueChanged);
        NS_CONNECT_EVENT(NumericUpDown, ValueChanged, BgB_ValueChanged);
        NS_CONNECT_EVENT(NumericUpDown, ValueChanged, FgR_ValueChanged);
        NS_CONNECT_EVENT(NumericUpDown, ValueChanged, FgG_ValueChanged);
        NS_CONNECT_EVENT(NumericUpDown, ValueChanged, FgB_ValueChanged);
        return false;
    }

    void BgR_ValueChanged(BaseComponent*, const Noesis::RoutedPropertyChangedEventArgs<int>& args)
    {
        Noesis::Color color = _bg->GetColor();
        _bg->SetColor(Noesis::Color(args.newValue, color.GetGreenI(), color.GetBlueI(), color.GetAlphaI()));
    }

    void BgG_ValueChanged(BaseComponent*, const Noesis::RoutedPropertyChangedEventArgs<int>& args)
    {
        Noesis::Color color = _bg->GetColor();
        _bg->SetColor(Noesis::Color(color.GetRedI(), args.newValue, color.GetBlueI(), color.GetAlphaI()));
    }

    void BgB_ValueChanged(BaseComponent*, const Noesis::RoutedPropertyChangedEventArgs<int>& args)
    {
        Noesis::Color color = _bg->GetColor();
        _bg->SetColor(Noesis::Color(color.GetRedI(), color.GetGreenI(), args.newValue, color.GetAlphaI()));
    }

    void FgR_ValueChanged(BaseComponent*, const Noesis::RoutedPropertyChangedEventArgs<int>& args)
    {
        Noesis::Color color = _fg->GetColor();
        _fg->SetColor(Noesis::Color(args.newValue, color.GetGreenI(), color.GetBlueI(), color.GetAlphaI()));
    }

    void FgG_ValueChanged(BaseComponent*, const Noesis::RoutedPropertyChangedEventArgs<int>& args)
    {
        Noesis::Color color = _fg->GetColor();
        _fg->SetColor(Noesis::Color(color.GetRedI(), args.newValue, color.GetBlueI(), color.GetAlphaI()));
    }

    void FgB_ValueChanged(BaseComponent*, const Noesis::RoutedPropertyChangedEventArgs<int>& args)
    {
        Noesis::Color color = _fg->GetColor();
        _fg->SetColor(Noesis::Color(color.GetRedI(), color.GetGreenI(), args.newValue, color.GetAlphaI()));
    }

private:
    Noesis::SolidColorBrush* _fg;
    Noesis::SolidColorBrush* _bg;

    NS_IMPLEMENT_INLINE_REFLECTION(MainWindow, Noesis::UserControl)
    {
        NsMeta<Noesis::TypeId>("UserControl.MainWindow");
    }
};

}
