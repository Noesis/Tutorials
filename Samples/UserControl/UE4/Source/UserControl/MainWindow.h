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
        Noesis::GUI::LoadComponent(this, "MainWindow.xaml");
    }

    // This code-behind is needed because MultiBindings are not yet supported
    // http://stackoverflow.com/questions/1978316/binding-r-g-b-properties-of-color-in-wpf
    bool ConnectEvent(BaseComponent* source, const char* event, const char* handler) override
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
        _bg->SetColor(Noesis::Color(args.newValue / 255.0f, color.g, color.b, color.a));
    }
    
    void BgG_ValueChanged(BaseComponent*, const Noesis::RoutedPropertyChangedEventArgs<int>& args)
    {
        Noesis::Color color = _bg->GetColor();
        _bg->SetColor(Noesis::Color(color.r, args.newValue / 255.0f, color.b, color.a));
    }
    
    void BgB_ValueChanged(BaseComponent*, const Noesis::RoutedPropertyChangedEventArgs<int>& args)
    {
        Noesis::Color color = _bg->GetColor();
        _bg->SetColor(Noesis::Color(color.r, color.g, args.newValue / 255.0f, color.a));
    }
    
    void FgR_ValueChanged(BaseComponent*, const Noesis::RoutedPropertyChangedEventArgs<int>& args)
    {
        Noesis::Color color = _fg->GetColor();
        _fg->SetColor(Noesis::Color(args.newValue / 255.0f, color.g, color.b, color.a));
    }
    
    void FgG_ValueChanged(BaseComponent*, const Noesis::RoutedPropertyChangedEventArgs<int>& args)
    {
        Noesis::Color color = _fg->GetColor();
        _fg->SetColor(Noesis::Color(color.r, args.newValue / 255.0f, color.b, color.a));
    }
    
    void FgB_ValueChanged(BaseComponent*, const Noesis::RoutedPropertyChangedEventArgs<int>& args)
    {
        Noesis::Color color = _fg->GetColor();
        _fg->SetColor(Noesis::Color(color.r, color.g, args.newValue / 255.0f, color.a));
    }

private:
    Noesis::SolidColorBrush* _fg;
    Noesis::SolidColorBrush* _bg;

    NS_IMPLEMENT_INLINE_REFLECTION_(MainWindow, UserControl, "UserControl.MainWindow")
};

}
