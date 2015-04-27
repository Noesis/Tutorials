////////////////////////////////////////////////////////////////////////////////////////////////////
/// Hello Triangle: An OpenGL ES 2.0 Example
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <stdlib.h>

#include <android_native_app_glue.h>
#include <android/native_window.h>
#include <android/log.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>


#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "HelloTriangle", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "HelloTriangle", __VA_ARGS__))


#define NOESIS_GUI

#ifdef NOESIS_GUI
    #include <NoesisGUI.h>
    using namespace Noesis;
#endif


struct UserData
{
    android_app* app;

    bool animating;

    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    EGLConfig pixelFormat;

    GLuint fbo;

    GLuint vShader;
    GLuint fShader;
    GLuint programObject;

    GLint width;
    GLint height;

#ifdef NOESIS_GUI
    Ptr<IRenderer> xamlRenderer;
    RenderCommands xamlCommands;
#endif
};

#ifdef NOESIS_GUI
////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisErrorHandler(const NsChar* filename, NsInt line, const NsChar* desc)
{
    LOGE("Error: %s [%d] : %s", filename, line, desc);
    exit(-1);
}

////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisInit(UserData* userData)
{
    Noesis::GUI::InitOpenGL(NoesisErrorHandler);

    Ptr<AndroidResourceProvider> provider = *new AndroidResourceProvider(
        userData->app->activity->assetManager, "NoesisGUI/", "");
    Noesis::GUI::AddResourceProvider(provider.GetPtr());

    Ptr<FrameworkElement> xaml = Noesis::GUI::LoadXaml<FrameworkElement>("UI.xaml");

    userData->xamlRenderer = Noesis::GUI::CreateRenderer(xaml.GetPtr());
    userData->xamlRenderer->SetSize(userData->width, userData->height);
    userData->xamlRenderer->SetAntialiasingMode(Noesis::Gui::AntialiasingMode_PPAA);
}

////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisResize(UserData* userData)
{
    userData->xamlRenderer->SetSize(userData->width, userData->height);
}

////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisTick()
{
    // Tick kernel
    Noesis::GUI::Tick();
}

////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisPreRender(UserData* userData)
{
    // Update renderer
    userData->xamlRenderer->Update(HighResTimer::Seconds() - HighResTimer::StartTime());
        // ...Do something useful here because Update() is concurrent...
    userData->xamlCommands = userData->xamlRenderer->WaitForUpdate();

    // Render offscreen textures
    if (userData->xamlCommands.offscreenCommands != 0)
    {
        userData->xamlRenderer->Render(userData->xamlCommands.offscreenCommands.GetPtr());
        userData->xamlCommands.offscreenCommands.Reset();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisPostRender(UserData* userData)
{
    // Render GUI to the active surface
    userData->xamlRenderer->Render(userData->xamlCommands.commands.GetPtr());
    userData->xamlCommands.commands.Reset();
}

////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisShutdown(UserData* userData)
{
    // free renderer resources
    userData->xamlCommands.offscreenCommands.Reset();
    userData->xamlCommands.commands.Reset();
    userData->xamlRenderer.Reset();

    // shut down NoesisGUI
    Noesis::GUI::Shutdown();
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////
GLuint LoadShader(const char *shaderSrc, GLenum type)
{
    // Create the shader object
    GLuint shader = glCreateShader(type);
    if (shader == 0)
    {
        LOGE("Unable to create shader [type=%X]", type);
        return 0;
    }

    // Load the shader source
    glShaderSource(shader, 1, &shaderSrc, NULL);

    // Compile the shader
    glCompileShader(shader);

    // Check the compile status
    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled)
    {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1)
        {
            char msg[512];
            glGetShaderInfoLog(shader, 512, NULL, msg);
            LOGE("Error compiling shader: %s", msg);
        }
        glDeleteShader(shader);

        return 0;
    }

    return shader;
}

////////////////////////////////////////////////////////////////////////////////////////////////
bool UpdateDisplaySize(UserData* userData)
{
    GLint w, h;
    w = userData->app->contentRect.left - userData->app->contentRect.right;
    h = userData->app->contentRect.top - userData->app->contentRect.bottom;

    if (w == 0 || h == 0)
    {
        w = ANativeWindow_getWidth(userData->app->window);
        h = ANativeWindow_getHeight(userData->app->window);

        if (w == 0 || h == 0)
        {
            eglQuerySurface(userData->display, userData->surface, EGL_WIDTH, &w);
            eglQuerySurface(userData->display, userData->surface, EGL_HEIGHT, &h);
        }
    }

    if (userData->width != w || userData->height != h)
    {
        userData->width = w;
        userData->height = h;
        LOGI("Surface size: %dx%d", w, h);
        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
bool InitDisplay(UserData* userData)
{
    // initialize OpenGL ES and EGL
    EGLSurface surface;
    EGLContext context;

    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    if (eglInitialize(display, 0, 0) == EGL_FALSE)
    {
        LOGE("Can't initialize display");
        return false;
    }

    if (!eglBindAPI(EGL_OPENGL_ES_API))
    {
        LOGE("Can't bind OpenGL ES API");
        return false;
    }

    // Here specify the attributes of the desired configuration.
    // Below, we select an EGLConfig with at least 8 bits per color
    // component compatible with on-screen windows
    const EGLint attribs[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_BLUE_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_RED_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 24,
        EGL_STENCIL_SIZE, 8,
        EGL_NONE
    };

    // Here, the application chooses the configuration it desires. In this
    // sample, we have a very simplified selection process, where we pick
    // the first EGLConfig that matches our criteria
    EGLint numConfigs;
    EGLConfig config;
    eglChooseConfig(display, attribs, &config, 1, &numConfigs);
    if (numConfigs < 1)
    {
        LOGE("Unable to eglChooseConfig");
        return false;
    }

    // EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
    // guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
    // As soon as we picked a EGLConfig, we can safely reconfigure the
    // ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID.
    EGLint format;
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

    ANativeWindow_setBuffersGeometry(userData->app->window, 0, 0, format);

    surface = eglCreateWindowSurface(display, config, userData->app->window, NULL);

    // Specify an OpenGL ES 2.0 context
    const EGLint contextAttribs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE 
    };
    context = eglCreateContext(display, config, NULL, contextAttribs);

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
    {
        LOGE("Unable to eglMakeCurrent");
        return false;
    }

    GLint fbo;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &fbo);

    // Create a shader for rendering the triangle
    const char vShaderStr[] =
        "attribute vec4 vPosition; \n"
        "void main() \n"
        "{ \n"
        "  gl_Position = vPosition; \n"
        "} \n";
    const char fShaderStr[] =
        "precision mediump float; \n"
        "void main() \n"
        "{ \n"
        "  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); \n"
        "} \n";

    // Load the vertex/fragment shaders
    GLuint vertexShader = LoadShader(vShaderStr, GL_VERTEX_SHADER);
    if (vertexShader == 0)
    {
        return false;
    }
    GLuint fragmentShader = LoadShader(fShaderStr, GL_FRAGMENT_SHADER);
    if (fragmentShader == 0)
    {
        return false;
    }

    // Create the program object
    GLuint programObject = glCreateProgram();
    if (programObject == 0)
    {
        LOGE("Unable to create shader program object");
        return false;
    }

    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);

    // Bind vPosition to attribute 0
    glBindAttribLocation(programObject, 0, "vPosition");

    // Link the program
    glLinkProgram(programObject);

    // Check the link status
    GLint linked;
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
    if (!linked)
    {
        GLint infoLen = 0;
        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1)
        {
            char msg[512];
            glGetProgramInfoLog(programObject, 512, NULL, msg);
            LOGE("Error linking program: %s", msg);
        }
        glDeleteProgram(programObject);

        return false;
    }

    // Store all created objects
    userData->display = display;
    userData->context = context;
    userData->surface = surface;
    userData->pixelFormat = config;
    userData->fbo = fbo;
    userData->vShader = vertexShader;
    userData->fShader = fragmentShader;
    userData->programObject = programObject;

    UpdateDisplaySize(userData);

    // Initialize GL state
    glClearColor(0.005f, 0.015f, 0.025f, 1.0f);

#ifdef NOESIS_GUI
    NoesisInit(userData);
#endif

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////
void ResizeDisplay(UserData* userData)
{
    if (userData->display == EGL_NO_DISPLAY)
    {
        return;
    }

    if (UpdateDisplaySize(userData))
    {
        // display size changed
#ifdef NOESIS_GUI
        NoesisResize(userData);
#endif
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
void DrawFrame(UserData* userData)
{
    if (userData->display == EGL_NO_DISPLAY)
    {
        return;
    }

#ifdef NOESIS_GUI
    NoesisTick();

    NoesisPreRender(userData);
#endif

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Set display dimensions
    glViewport(0, 0, userData->width, userData->height);

    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Use the program object
    glUseProgram(userData->programObject);

    // Load the vertex data
    GLfloat vertices[] = { 0.0f,0.5f,0.0f, -0.5f,-0.5f,0.0f, 0.5f,-0.5f,0.0f };
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(0);

    GLenum er = GL_NO_ERROR;
    while ((er = glGetError()) != GL_NO_ERROR)
    {
        LOGE("Pre %d", er);
    }

    glDrawArrays(GL_TRIANGLES, 0, 3);

    er = GL_NO_ERROR;
    while ((er = glGetError()) != GL_NO_ERROR)
    {
        LOGE("Post %d", er);
    }

#ifdef NOESIS_GUI
    NoesisPostRender(userData);
#endif

    // End
    glFlush();
    eglSwapBuffers(userData->display, userData->surface);
}

////////////////////////////////////////////////////////////////////////////////////////////////
void ShutdownDisplay(UserData* userData)
{
    if (userData->display == EGL_NO_DISPLAY)
    {
        return;
    }

#ifdef NOESIS_GUI
    NoesisShutdown(userData);
#endif

    glDeleteProgram(userData->vShader);
    glDeleteProgram(userData->fShader);
    glDeleteProgram(userData->programObject);

    eglMakeCurrent(userData->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    if (userData->context != EGL_NO_CONTEXT)
    {
        eglDestroyContext(userData->display, userData->context);
    }
    if (userData->surface != EGL_NO_SURFACE)
    {
        eglDestroySurface(userData->display, userData->surface);
    }

    eglTerminate(userData->display);

    userData->animating = false;
    userData->display = EGL_NO_DISPLAY;
    userData->context = EGL_NO_CONTEXT;
    userData->surface = EGL_NO_SURFACE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
void KeyDown(UserData* userData, int keyCode)
{
#ifdef NOESIS_GUI
    // TODO: translate key code to NoesisGUI key enum
    Key key = Key_None;
    userData->xamlRenderer->KeyDown(key);
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////
void KeyUp(UserData* userData, int keyCode)
{
#ifdef NOESIS_GUI
    // TODO: translate key code to NoesisGUI key enum
    Key key = Key_None;
    userData->xamlRenderer->KeyUp(key);
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////
void MouseDown(UserData* userData, float x, float y)
{
#ifdef NOESIS_GUI
    userData->xamlRenderer->MouseButtonDown((int)x, (int)y, MouseButton_Left);
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////
void MouseUp(UserData* userData, float x, float y)
{
#ifdef NOESIS_GUI
    userData->xamlRenderer->MouseButtonUp((int)x, (int)y, MouseButton_Left);
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////
void MouseMove(UserData* userData, float x, float y)
{
#ifdef NOESIS_GUI
    userData->xamlRenderer->MouseMove((int)x, (int)y);
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////
int32_t HandleInput(android_app* app, AInputEvent* event)
{
    UserData* userData = (UserData*)app->userData;

    switch (AInputEvent_getType(event))
    {
        case AINPUT_EVENT_TYPE_KEY:
        {
            switch (AKeyEvent_getAction(event))
            {
                case AKEY_EVENT_ACTION_DOWN:
                {
                    KeyDown(userData, AKeyEvent_getKeyCode(event));
                    break;
                }
                case AKEY_EVENT_ACTION_UP:
                {
                    KeyUp(userData, AKeyEvent_getKeyCode(event));
                    break;
                }
            }
            break;
        }
        case AINPUT_EVENT_TYPE_MOTION:
        {
            size_t numPointers = AMotionEvent_getPointerCount(event);
            if (numPointers > 0)
            {
                int32_t action = AMotionEvent_getAction(event);

                switch (action & AMOTION_EVENT_ACTION_MASK)
                {
                    case AMOTION_EVENT_ACTION_DOWN:
                    case AMOTION_EVENT_ACTION_POINTER_DOWN:
                    {
                        float x = AMotionEvent_getX(event, 0);
                        float y = AMotionEvent_getY(event, 0) - app->contentRect.top;
                        MouseDown(userData, x, y);
                        break;
                    }
                    case AMOTION_EVENT_ACTION_UP:
                    case AMOTION_EVENT_ACTION_POINTER_UP:
                    {
                        float x = AMotionEvent_getX(event, 0);
                        float y = AMotionEvent_getY(event, 0) - app->contentRect.top;
                        MouseUp(userData, x, y);
                        break;
                    }
                    case AMOTION_EVENT_ACTION_MOVE:
                    {
                        float x = AMotionEvent_getX(event, 0);
                        float y = AMotionEvent_getY(event, 0) - app->contentRect.top;
                        MouseMove(userData, x, y);
                        break;
                    }
                }
            }
            break;
        }
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////
void HandleAppCmd(android_app* app, int32_t cmd)
{
    UserData* userData = (UserData*)app->userData;

    switch (cmd)
    {
        case APP_CMD_INIT_WINDOW:
        {
            // The window is being shown, get it ready
            if (userData->app->window)
            {
                InitDisplay(userData);
            }
            break;
        }
        case APP_CMD_CONTENT_RECT_CHANGED:
        {
            ResizeDisplay(userData);
            break;
        }
        case APP_CMD_WINDOW_RESIZED:
        {
            ResizeDisplay(userData);
            break;
        }
        case APP_CMD_WINDOW_REDRAW_NEEDED:
        {
            DrawFrame(userData);
            break;
        }
        case APP_CMD_TERM_WINDOW:
        {
            // The window is being hidden or closed, clean it up
            ShutdownDisplay(userData);
            break;
        }
        case APP_CMD_LOST_FOCUS:
        {
            // Stop animating
            userData->animating = false;
            DrawFrame(userData);
            break;
        }
        case APP_CMD_GAINED_FOCUS:
        {
            // Restart animating
            userData->animating = true;
            DrawFrame(userData);
            break;
        }
        case APP_CMD_CONFIG_CHANGED:
        {
            ResizeDisplay(userData);
            break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
void android_main(android_app* app)
{
    LOGI("android_main BEGIN");

    // Ensure app wrapper code is not discarded
    app_dummy();

    UserData userData;
    memset(&userData, 0, sizeof(UserData));
    app->userData = &userData;
    app->onAppCmd = HandleAppCmd;
    app->onInputEvent = HandleInput;
    userData.app = app;

    bool loop = true;
    while (loop)
    {
        // Read all pending events
        int events;
        android_poll_source* source;
        while (ALooper_pollAll(0, 0, &events, (void**)&source) >= 0)
        {
            // Process this event
            if (source)
            {
                source->process(app, source);
            }

            // Check if exiting occurs before window was created
            if (app->destroyRequested)
            {
                LOGI("App destroyed");
                loop = false;
                break;
            }
        }

        if (loop && userData.animating)
        {
            DrawFrame(&userData);
        }
    }

    LOGI("android_main END");

    exit(0);
}

