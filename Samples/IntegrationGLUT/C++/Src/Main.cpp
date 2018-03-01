////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


// Minimal integration sample using GLUT and NoesisGUI. For simplification purposes, this example
// is not complete (for example, only mouse input events are handled). For a full multiplatform
// integration code with step by step comments have a look at 'Samples/Integration'


#ifdef _WIN32
#include "glut.h"
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#if defined(__linux__)
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#ifdef _WIN32
#pragma comment(linker,"/SUBSYSTEM:CONSOLE")
#endif

#ifdef _WIN32
#define UNUSED_ARGS(...) (void)(true ? (void)0 : ((void)(__VA_ARGS__)))
#else
#define UNUSED_ARGS(...)
#endif

// Comment this out to totally disable NoesisGUI
#define NOESIS_GUI

#ifdef NOESIS_GUI

#include <NsCore/Noesis.h>
#include <NsGui/IntegrationAPI.h>
#include <NsGui/IView.h>
#include <NsGui/IRenderer.h>
#include <NsGui/FrameworkElement.h>
#include <NsRender/GLFactory.h>
#include <NsApp/EmbeddedXamlProvider.h>

#include "Reflections.xaml.bin.h"


Noesis::Ptr<Noesis::IView> _view;


///////////////////////////////////////////////////////////////////////////////////////////////////
void Noesis_Init()
{
    // Noesis initialization. This must be the first step before using any NoesisGUI functionality
    auto logHandler = [](const char*, uint32_t, uint32_t level, const char* channel,
        const char* message)
    {
        if (strcmp(channel, "") == 0)
        {
            // [TRACE] [DEBUG] [INFO] [WARNING] [ERROR]
            const char* prefixes[] = { "T", "D", "I", "W", "E" };
            const char* prefix = level < NS_COUNTOF(prefixes) ? prefixes[level] : " ";
            fprintf(stderr, "[NOESIS/%s] %s\n", prefix, message);
        }
    };

    Noesis::GUI::Init(nullptr, logHandler, nullptr);

    // Setup C array embedded XAMLs provider
    NoesisApp::EmbeddedXaml content =
    {
        "Reflections.xaml", Reflections_xaml, sizeof(Reflections_xaml)
    };

    Noesis::GUI::SetXamlProvider(Noesis::MakePtr<NoesisApp::EmbeddedXamlProvider>(&content, 1));

    // View creation to render and interact with the user interface
    auto xaml = Noesis::GUI::LoadXaml<Noesis::FrameworkElement>("Reflections.xaml");
    _view = Noesis::GUI::CreateView(xaml);
    _view->SetIsPPAAEnabled(true);

    // Renderer initialization with an OpenGL device
    Noesis::Ptr<Noesis::RenderDevice> device = NoesisApp::GLFactory::CreateDevice();
    _view->GetRenderer()->Init(device);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Noesis_Shutdown()
{
    // It is mandatory to release all noesis objects before shutting down
    _view->GetRenderer()->Shutdown();
    _view.Reset();
    Noesis::GUI::Shutdown();
}

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
void DisplayFunc(void)
{
#ifdef NOESIS_GUI
    // Update view (layout, animations, ...)
    _view->Update(glutGet(GLUT_ELAPSED_TIME) / 1000.0);

    // Offscreen rendering phase populates textures needed by the on-screen rendering
    _view->GetRenderer()->UpdateRenderTree();
    _view->GetRenderer()->RenderOffscreen();
#endif

    // If you are going to render here with your own engine you need to restore the GPU state
    // because noesis changes it. The framebuffer and viewport are restored here
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

    glClearColor(0.0f, 0.0f, 0.25f, 0.0f);
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

#ifdef NOESIS_GUI
    // Rendering is done in the active framebuffer
    _view->GetRenderer()->Render();
#endif

    glutSwapBuffers();
    glutPostRedisplay();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ReshapeFunc(int width, int height)
{
    UNUSED_ARGS(width, height);

#ifdef NOESIS_GUI
    if (_view != 0)
    {
        _view->SetSize(width, height);
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MouseMoveFunc(int x, int y)
{
    UNUSED_ARGS(x, y);

#ifdef NOESIS_GUI
    if (_view != 0)
    {
        _view->MouseMove(x, y);
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MouseFunc(int button, int state, int x, int y)
{
    UNUSED_ARGS(button, state, x , y);

#ifdef NOESIS_GUI
    if (_view != 0 && button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            _view->MouseButtonDown(x, y, Noesis::MouseButton_Left);
        }
        else
        {
            _view->MouseButtonUp(x, y, Noesis::MouseButton_Left);
        }
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(1000, 600);
    glutCreateWindow("NoesisGUI - GLUT integration");

#ifdef NOESIS_GUI
    Noesis_Init();
    atexit(Noesis_Shutdown);
#endif

    glutDisplayFunc(&DisplayFunc);
    glutReshapeFunc(&ReshapeFunc);
    glutPassiveMotionFunc(&MouseMoveFunc);
    glutMouseFunc(&MouseFunc);

    glutMainLoop();
    return 0;
}
