////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GLUT_H__
#define __GLUT_H__


// Quick & dirty minimal GLUT implementation for Windows to avoid extra dependencies because GLUT
// is not included in Windows by default. Can be replaced by standard GLUT implementation


#include <windows.h>
#include <ShellScalingApi.h>
#include <GL/gl.h>
#include <assert.h>
#include <stdint.h>


#pragma comment (lib, "opengl32.lib")


#define WINDOW_CLASS_NAME "GLUT_Window"

// Display mode bit masks
#define GLUT_RGB            1
#define GLUT_DOUBLE         2
#define GLUT_DEPTH          4
#define GLUT_STENCIL        8

// Mouse buttons
#define GLUT_LEFT_BUTTON    0
#define GLUT_MIDDLE_BUTTON  1
#define GLUT_RIGHT_BUTTON   2

// Mouse button state
#define GLUT_DOWN           0
#define GLUT_UP             1

// glutGet parameters
#define GLUT_ELAPSED_TIME   0
#define GLUT_WINDOW_WIDTH   1
#define GLUT_WINDOW_HEIGHT  2


#define GL_FRAMEBUFFER      0x8D40
typedef  void (WINAPI* PFNGLBINDFRAMEBUFFERPROC)(GLenum target, GLuint framebuffer);
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;


namespace GLUT
{
uint64_t start;
int width;
int height;
HWND hWnd;
HDC hDC;

void (*DisplayFunc)(void);
void (*ReshapeFunc)(int width, int height);
void (*PassiveMotionFunc)(int x, int y);
void (*MouseFunc)(int button, int state, int x, int y);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
LRESULT WINAPI WndProc_(HWND hWnd, unsigned int msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_SIZE:
        {
            if (GLUT::ReshapeFunc != nullptr)
            {
                GLUT::ReshapeFunc(LOWORD(lParam), HIWORD(lParam));
            }
            break;
        }
        case WM_LBUTTONUP:
        {
            if (GLUT::MouseFunc != nullptr)
            {
                GLUT::MouseFunc(GLUT_LEFT_BUTTON, GLUT_UP, LOWORD(lParam), HIWORD(lParam));
            }
            break;
        }
        case WM_LBUTTONDOWN:
        {
            if (GLUT::MouseFunc != nullptr)
            {
                GLUT::MouseFunc(GLUT_LEFT_BUTTON, GLUT_DOWN, LOWORD(lParam), HIWORD(lParam));
            }
            break;
        }
        case WM_MOUSEMOVE:
        {
            if (GLUT::PassiveMotionFunc != nullptr)
            {
                GLUT::PassiveMotionFunc(LOWORD(lParam), HIWORD(lParam));
            }
            break;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
    }

    return DefWindowProcA(hWnd, msg, wParam, lParam);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
uint64_t Milliseconds()
{
    static long long frequency;
    if (frequency == 0)
    {
        LARGE_INTEGER f;
        QueryPerformanceFrequency(&f); // will always succeed
        frequency = f.QuadPart;
    }

    LARGE_INTEGER count;
    QueryPerformanceCounter(&count); // will always succeed
    return 1000 * count.QuadPart / frequency;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int glutGet(GLenum state)
{
    if (state == GLUT_ELAPSED_TIME)
    {
        return int(Milliseconds() - GLUT::start);
    }
    else if (state == GLUT_WINDOW_WIDTH)
    {
        RECT rect;
        GetClientRect(GLUT::hWnd, &rect);
        return rect.right;
    }
    else if (state == GLUT_WINDOW_HEIGHT)
    {
        RECT rect;
        GetClientRect(GLUT::hWnd, &rect);
        return rect.bottom;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void glutInit(int *, char **)
{
    HMODULE shCore = LoadLibraryA("Shcore.dll");
    if (shCore != 0)
    {
        typedef HRESULT(WINAPI* PFN_SETPROCESSDPIAWARENESS)(_In_ PROCESS_DPI_AWARENESS value);
        PFN_SETPROCESSDPIAWARENESS SetProcessDpiAwareness_ = (PFN_SETPROCESSDPIAWARENESS)
            GetProcAddress(shCore, "SetProcessDpiAwareness");
        if (SetProcessDpiAwareness_ != 0)
        {
            SetProcessDpiAwareness_(PROCESS_PER_MONITOR_DPI_AWARE);
        }

        FreeLibrary(shCore);
    }

    GLUT::start = Milliseconds();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void glutInitDisplayMode(unsigned int)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void glutInitWindowSize(int width, int height)
{
    GLUT::width = width;
    GLUT::height = height;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int glutCreateWindow(char *name)
{
    // Window class
    WNDCLASSEXA wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc_;
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hInstance = GetModuleHandle(0);
    wc.lpszClassName = WINDOW_CLASS_NAME;
    RegisterClassExA(&wc);

    // Window
    RECT rect;
    SetRect(&rect, 0, 0, GLUT::width, GLUT::height);
    DWORD dwStyle = WS_OVERLAPPEDWINDOW;
    AdjustWindowRect(&rect, dwStyle, FALSE);
    GLUT::hWnd = CreateWindowA(WINDOW_CLASS_NAME, name, dwStyle, CW_USEDEFAULT, CW_USEDEFAULT,
        rect.right - rect.left, rect.bottom - rect.top, 0, 0, 0, 0);
    assert(GLUT::hWnd != 0);

    // GL context
    PIXELFORMATDESCRIPTOR pfd;
    memset(&pfd, 0, sizeof(pfd));
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cStencilBits = 8;

    GLUT::hDC = GetDC(GLUT::hWnd);
    int pixelFormat = ChoosePixelFormat(GLUT::hDC, &pfd);

    SetPixelFormat(GLUT::hDC, pixelFormat, &pfd);
    HGLRC hRC = wglCreateContext(GLUT::hDC);
    wglMakeCurrent(GLUT::hDC, hRC);

    glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)wglGetProcAddress("glBindFramebuffer");
    assert(glBindFramebuffer != 0);

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void glutDisplayFunc(void (*func)(void))
{
    GLUT::DisplayFunc = func;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void glutReshapeFunc(void (*func)(int width, int height))
{
    GLUT::ReshapeFunc= func;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void glutPassiveMotionFunc(void (*func)(int x, int y))
{
    GLUT::PassiveMotionFunc = func;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void glutMouseFunc(void (*func)(int button, int state, int x, int y))
{
    GLUT::MouseFunc = func;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void glutMainLoop(void)
{
    ShowWindow(GLUT::hWnd, SW_SHOWNORMAL);

    MSG msg = {0};

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            if (GLUT::DisplayFunc != nullptr)
            {
                GLUT::DisplayFunc();
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void glutSwapBuffers(void)
{
    SwapBuffers(GLUT::hDC);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void glutPostRedisplay(void)
{
}


#endif
