////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


// This is a minimal integration example. For simplification purposes only basic input events are
// handled, no resource providers are used and the shutdown procedure is omitted. A more complete
// multiplatform integration sample with step by step comments can be found at 'Samples/Integration'


#ifdef _WIN32
#include "glut.h"
#pragma comment(linker,"/SUBSYSTEM:CONSOLE")
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __EMSCRIPTEN__
#include <GL/glut.h>
#include <GLES3/gl32.h>
#include <emscripten/html5.h>
#endif

#ifdef __linux__
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#ifdef _MSC_VER
#define UNUSED_ARGS(...) (void)(true ? (void)0 : ((void)(__VA_ARGS__)))
#else
#define UNUSED_ARGS(...)
#endif


#include <NsApp/ThemeProviders.h>
#include <NsRender/GLFactory.h>
#include <NsGui/FontProperties.h>
#include <NsGui/IntegrationAPI.h>
#include <NsGui/IRenderer.h>
#include <NsGui/IView.h>
#include <NsGui/Grid.h>


static Noesis::IView* _view;


///////////////////////////////////////////////////////////////////////////////////////////////////
static void NoesisInit()
{
    Noesis::SetLogHandler([](const char*, uint32_t, uint32_t level, const char*, const char* msg)
    {
        // [TRACE] [DEBUG] [INFO] [WARNING] [ERROR]
        const char* prefixes[] = { "T", "D", "I", "W", "E" };
        printf("[NOESIS/%s] %s\n", prefixes[level], msg);
    });

    // Noesis initialization. This must be the first step before using any NoesisGUI functionality
    Noesis::GUI::Init(NS_LICENSE_NAME, NS_LICENSE_KEY);

    // Setup theme
    NoesisApp::SetThemeProviders();
    Noesis::GUI::LoadApplicationResources("Theme/NoesisTheme.DarkBlue.xaml");

    // For simplicity purposes we are not using resource providers in this sample. ParseXaml() is
    // enough if there is no extra XAML dependencies
    Noesis::Ptr<Noesis::Grid> xaml(Noesis::GUI::ParseXaml<Noesis::Grid>(R"(
        <Grid xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation">
            <Grid.Background>
                <LinearGradientBrush StartPoint="0,0" EndPoint="0,1">
                    <GradientStop Offset="0" Color="#FF123F61"/>
                    <GradientStop Offset="0.6" Color="#FF0E4B79"/>
                    <GradientStop Offset="0.7" Color="#FF106097"/>
                </LinearGradientBrush>
            </Grid.Background>
            <Viewbox>
                <StackPanel Margin="50">
                    <Button Content="Hello World!" Margin="0,30,0,0"/>
                    <Rectangle Height="5" Margin="-10,20,-10,0">
                        <Rectangle.Fill>
                            <RadialGradientBrush>
                                <GradientStop Offset="0" Color="#40000000"/>
                                <GradientStop Offset="1" Color="#00000000"/>
                            </RadialGradientBrush>
                        </Rectangle.Fill>
                    </Rectangle>
                </StackPanel>
            </Viewbox>
        </Grid>
    )"));

    // View creation to render and interact with the user interface
    // We transfer the ownership to a global pointer instead of a Ptr<> because there is no way
    // in GLUT to do shutdown and we don't want the Ptr<> to be released at global time
    _view = Noesis::GUI::CreateView(xaml).GiveOwnership();
    _view->SetFlags(Noesis::RenderFlags_PPAA | Noesis::RenderFlags_LCD);

    // Renderer initialization with an OpenGL device
    _view->GetRenderer()->Init(NoesisApp::GLFactory::CreateDevice());
}

///////////////////////////////////////////////////////////////////////////////////////////////////
static void DisplayFunc(void)
{
    // Update view (layout, animations, ...)
    _view->Update(glutGet(GLUT_ELAPSED_TIME) / 1000.0);

    // Offscreen rendering phase populates textures needed by the on-screen rendering
    _view->GetRenderer()->UpdateRenderTree();
    _view->GetRenderer()->RenderOffscreen();

    // If you are going to render here with your own engine you need to restore the GPU state
    // because noesis changes it. In this case only framebuffer and viewport need to be restored
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

    glClearColor(0.0f, 0.0f, 0.25f, 0.0f);
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // Rendering is done in the active framebuffer
    _view->GetRenderer()->Render();

    glutSwapBuffers();
    glutPostRedisplay();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void ReshapeFunc(int width, int height)
{
    _view->SetSize(width, height);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void MouseMoveFunc(int x, int y)
{
    _view->MouseMove(x, y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void MouseFunc(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
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
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_STENCIL);
    glutInitWindowSize(1000, 600);

#ifdef __EMSCRIPTEN__
    double width, height;
    emscripten_get_element_css_size("#canvas", &width, &height);
    emscripten_set_canvas_element_size("#canvas", (uint32_t)width, (uint32_t)height);
    glutInitWindowSize((uint32_t)width, (uint32_t)height);
#endif

    glutCreateWindow("NoesisGUI - GLUT integration");
    NoesisInit();

    glutDisplayFunc(&DisplayFunc);
    glutReshapeFunc(&ReshapeFunc);
    glutPassiveMotionFunc(&MouseMoveFunc);
    glutMouseFunc(&MouseFunc);

    glutMainLoop();
    return 0;
}
