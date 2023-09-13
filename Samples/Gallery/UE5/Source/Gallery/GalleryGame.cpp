////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "GalleryGame.h"
#include "MainWindow.h"

DEFINE_LOG_CATEGORY(LogNoesisGallery)

Noesis::BaseComponent* ButtonCreator(Noesis::Symbol)
{
    return nullptr;
}

class GalleryModule : public FDefaultGameModuleImpl
{
    virtual void StartupModule() override
    {
        Noesis::RegisterComponent<Gallery::MainWindow>();
    }

    virtual void ShutdownModule() override
    {
        Noesis::UnregisterComponent<Gallery::MainWindow>();
    }
};

IMPLEMENT_MODULE(GalleryModule, GalleryModule);
