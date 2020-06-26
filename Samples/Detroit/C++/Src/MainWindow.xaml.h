////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __DETROIT_MAINWINDOW_H__
#define __DETROIT_MAINWINDOW_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsApp/Window.h>


namespace Detroit
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class MainWindow final: public NoesisApp::Window
{
public:
    MainWindow();

private:
    void InitializeComponent();

private:
    NS_DECLARE_REFLECTION(MainWindow, Window)
};


}


#endif
