#ifdef _MSC_VER
    #include <windows.h>
    #include <GL/gl.h>
#endif

#include <glut.h>


#define GLUT_DLL_EXPORT __declspec(dllexport)
#define GLUT_STDCALL __stdcall


namespace
{
#ifdef _MSC_VER
    #define GL_FRAMEBUFFER 0x8D40

    typedef void (WINAPI *PFNGLBINDFRAMEBUFFERPROC)(GLenum target, GLuint framebuffer);
    PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;

    typedef void (WINAPI * PFNGLUSEPROGRAMPROC)(GLuint program);
    PFNGLUSEPROGRAMPROC glUseProgram;
#endif

typedef void(GLUT_STDCALL *CloseCallbackFn)();
CloseCallbackFn gCloseCallback = 0;

typedef void(GLUT_STDCALL *TickCallbackFn)();
TickCallbackFn gTickCallback = 0;

typedef void(GLUT_STDCALL *LogCallbackFn)(int);
LogCallbackFn gLogCallback = 0;

typedef void(GLUT_STDCALL *PreRenderCallbackFn)();
PreRenderCallbackFn gPreRenderCallback = 0;

typedef void(GLUT_STDCALL *PostRenderCallbackFn)();
PostRenderCallbackFn gPostRenderCallback = 0;

typedef void(GLUT_STDCALL *ResizeCallbackFn)(int width, int height);
ResizeCallbackFn gResizeCallback = 0;

typedef void(GLUT_STDCALL *MouseMoveCallbackFn)(int x, int y);
MouseMoveCallbackFn gMouseMoveCallback = 0;

typedef void(GLUT_STDCALL *MouseButtonCallbackFn)(int x, int y, int button);
MouseButtonCallbackFn gMouseDownCallback = 0;
MouseButtonCallbackFn gMouseUpCallback = 0;

typedef void(GLUT_STDCALL *KeyCallbackFn)(unsigned char key, int specialKey, int modifiers);
KeyCallbackFn gKeyDownCallback = 0;
KeyCallbackFn gKeyUpCallback = 0;

int gWidth = 0;
int gHeight = 0;

enum MouseButton
{
    MouseButton_Left,
    MouseButton_Right,
    MouseButton_Middle,
    MouseButton_XButton1,
    MouseButton_XButton2
};

enum SpecialKey
{
    SpecialKey_None,
    SpecialKey_F1, SpecialKey_F2, SpecialKey_F3, SpecialKey_F4, SpecialKey_F5, SpecialKey_F6,
    SpecialKey_F7, SpecialKey_F8, SpecialKey_F9, SpecialKey_F10, SpecialKey_F11, SpecialKey_F12,
    SpecialKey_PageUp, SpecialKey_PageDown,
    SpecialKey_Home, SpecialKey_End, SpecialKey_Insert,
    SpecialKey_Left, SpecialKey_Right, SpecialKey_Up, SpecialKey_Down
};

enum ModifierKey
{
    ModifierKey_Shift = 1,
    ModifierKey_Ctrl = 2,
    ModifierKey_Alt = 4
};

///////////////////////////////////////////////////////////////////////////////////////////////////
MouseButton GetMouseButton(int button)
{
    switch (button)
    {
        default:
        case GLUT_LEFT_BUTTON: return MouseButton_Left;
        case GLUT_RIGHT_BUTTON: return MouseButton_Right;
        case GLUT_MIDDLE_BUTTON: return MouseButton_Middle;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
SpecialKey GetSpecialKey(int key)
{
    switch (key)
    {
        case GLUT_KEY_F1: return SpecialKey_F1;
        case GLUT_KEY_F2: return SpecialKey_F2;
        case GLUT_KEY_F3: return SpecialKey_F3;
        case GLUT_KEY_F4: return SpecialKey_F4;
        case GLUT_KEY_F5: return SpecialKey_F5;
        case GLUT_KEY_F6: return SpecialKey_F6;
        case GLUT_KEY_F7: return SpecialKey_F7;
        case GLUT_KEY_F8: return SpecialKey_F8;
        case GLUT_KEY_F9: return SpecialKey_F9;
        case GLUT_KEY_F10: return SpecialKey_F10;
        case GLUT_KEY_F11: return SpecialKey_F11;
        case GLUT_KEY_F12: return SpecialKey_F12;
        case GLUT_KEY_PAGE_UP: return SpecialKey_PageUp;
        case GLUT_KEY_PAGE_DOWN: return SpecialKey_PageDown;
        case GLUT_KEY_HOME: return SpecialKey_Home;
        case GLUT_KEY_END: return SpecialKey_End;
        case GLUT_KEY_INSERT: return SpecialKey_Insert;
        case GLUT_KEY_LEFT: return SpecialKey_Left;
        case GLUT_KEY_RIGHT: return SpecialKey_Right;
        case GLUT_KEY_UP: return SpecialKey_Up;
        case GLUT_KEY_DOWN: return SpecialKey_Down;
        default: return SpecialKey_None;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void GLUT_Close()
{
    if (gCloseCallback != 0)
    {
        gCloseCallback();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void GLUT_Display()
{
    // Frame tick
    if (gTickCallback != 0)
    {
        gTickCallback();
    }

    // PreRender
    if (gPreRenderCallback != 0)
    {
        gPreRenderCallback();
    }

    // Render Scene (now only a clear)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearDepth(1.0f);
    glDepthMask(GL_TRUE);

    glDisable(GL_CULL_FACE);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_BLEND);
    glDisable(GL_SCISSOR_TEST);

    glUseProgram(0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, gWidth, gHeight);
    glColorMask(true, true, true, true);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

    // PostRender
    if (gPostRenderCallback != 0)
    {
        gPostRenderCallback();
    }

    // End
    glFlush();
    glutSwapBuffers();

    // Update again and again...
    glutPostRedisplay();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void GLUT_Resize(int width, int height)
{
    gWidth = width;
    gHeight = height;

    if (gResizeCallback != 0)
    {
        gResizeCallback(gWidth, gHeight);
    }

    // Update
    glutPostRedisplay();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void GLUT_MouseMove(int x, int y)
{
    if (gMouseMoveCallback != 0)
    {
        gMouseMoveCallback(x, y);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void GLUT_MouseButton(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        if (gMouseDownCallback != 0)
        {
            gMouseDownCallback(x, y, GetMouseButton(button));
        }
    }
    else // state == GLUT_UP
    {
        if (gMouseUpCallback != 0)
        {
            gMouseUpCallback(x, y, GetMouseButton(button));
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void GLUT_KeyboardDown(unsigned char key, int x, int y)
{
    if (gKeyDownCallback != 0)
    {
        int modifiers = glutGetModifiers();
        gKeyDownCallback(key, SpecialKey_None, modifiers);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void GLUT_KeyboardUp(unsigned char key, int x, int y)
{
    if (gKeyUpCallback != 0)
    {
        int modifiers = glutGetModifiers();
        gKeyUpCallback(key, SpecialKey_None, modifiers);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void GLUT_KeyboardSpecialDown(int key, int x, int y)
{
    if (gKeyDownCallback != 0)
    {
        int modifiers = glutGetModifiers();
        gKeyDownCallback(0, GetSpecialKey(key), modifiers);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void GLUT_KeyboardSpecialUp(int key, int x, int y)
{
    if (gKeyUpCallback != 0)
    {
        int modifiers = glutGetModifiers();
        gKeyUpCallback(0, GetSpecialKey(key), modifiers);
    }
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" GLUT_DLL_EXPORT void GLUT_STDCALL GLUT_Init(int windowWidth, int windowHeight,
    const char* title)
{
    char *myargv[] = { "GLUTWrapper" };
    int myargc = 1;

    glutInit(&myargc, myargv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(0, 0);

    glutCreateWindow(title);

#ifdef _MSC_VER
    glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)wglGetProcAddress("glBindFramebuffer");
    glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" GLUT_DLL_EXPORT void GLUT_STDCALL GLUT_RegisterClose(CloseCallbackFn closeCallback)
{
    gCloseCallback = closeCallback;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" GLUT_DLL_EXPORT void GLUT_STDCALL GLUT_RegisterTick(TickCallbackFn tickCallback)
{
    gTickCallback = tickCallback;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" GLUT_DLL_EXPORT void GLUT_STDCALL GLUT_RegisterLog(LogCallbackFn logCallback)
{
    gLogCallback = logCallback;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" GLUT_DLL_EXPORT void GLUT_STDCALL GLUT_RegisterPreRender(PreRenderCallbackFn preRenderCallback)
{
    gPreRenderCallback = preRenderCallback;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" GLUT_DLL_EXPORT void GLUT_STDCALL GLUT_RegisterPostRender(PostRenderCallbackFn postRenderCallback)
{
    gPostRenderCallback = postRenderCallback;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" GLUT_DLL_EXPORT void GLUT_STDCALL GLUT_RegisterResize(ResizeCallbackFn resizeCallback)
{
    gResizeCallback = resizeCallback;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" GLUT_DLL_EXPORT void GLUT_STDCALL GLUT_RegisterMouse(
    MouseMoveCallbackFn mouseMoveCallback,
    MouseButtonCallbackFn mouseDownCallback,
    MouseButtonCallbackFn mouseUpCallback)
{
    gMouseMoveCallback = mouseMoveCallback;
    gMouseDownCallback = mouseDownCallback;
    gMouseUpCallback = mouseUpCallback;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" GLUT_DLL_EXPORT void GLUT_STDCALL GLUT_RegisterKeyboard(
    KeyCallbackFn keyDownCallback,
    KeyCallbackFn keyUpCallback)
{
    gKeyDownCallback = keyDownCallback;
    gKeyUpCallback = keyUpCallback;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" GLUT_DLL_EXPORT void GLUT_STDCALL GLUT_Run()
{
    glutDisplayFunc(&GLUT_Display);
    glutReshapeFunc(&GLUT_Resize);
    glutMouseFunc(&GLUT_MouseButton);
    glutMotionFunc(&GLUT_MouseMove);
    glutPassiveMotionFunc(&GLUT_MouseMove);
    glutKeyboardFunc(&GLUT_KeyboardDown);
    glutKeyboardUpFunc(&GLUT_KeyboardUp);
    glutSpecialFunc(&GLUT_KeyboardSpecialDown);
    glutSpecialUpFunc(&GLUT_KeyboardSpecialUp);

    atexit(&GLUT_Close);

    glutMainLoop();
}
