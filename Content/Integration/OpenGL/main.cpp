/* ============================================================================
**
** Demonstration of spinning cube
** Copyright (C) 2005  Julien Guertault
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License
** as published by the Free Software Foundation; either version 2
** of the License, or (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
**
** ========================================================================= */

/* ============================================================================
** The original version of this sample was taken from:
**  http://www.lousodrome.net/opengl/
** ========================================================================= */


#ifdef _MSC_VER
    #include "pch.h"
#endif


#ifdef NOESIS_GUI

using namespace Noesis;

Ptr<IRenderer> xamlRenderer;
int width, height;

#ifdef _MSC_VER
    #define GL_FRAMEBUFFER 0x8D40

    typedef void (WINAPI *PFNGLBINDFRAMEBUFFERPROC)(GLenum target, GLuint framebuffer);
    PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;

    typedef void (WINAPI * PFNGLUSEPROGRAMPROC)(GLuint program);
    PFNGLUSEPROGRAMPROC glUseProgram;
#endif

#endif

/*
** Function called to update rendering
*/
void DisplayFunc(void)
{
#ifdef NOESIS_GUI
    // Tick kernel
    Noesis::GUI::Tick();

    // Update UI
    xamlRenderer->Update(glutGet(GLUT_ELAPSED_TIME) / 1000.0f);
    // ...Do something useful here because Update() is concurrent...
    RenderCommands commands = xamlRenderer->WaitForUpdate();

    // Render offscreen textures
    if (commands.offscreenCommands != 0)
    {
        xamlRenderer->Render(commands.offscreenCommands.GetPtr());
    }
#endif

    static float alpha = 0;

    glClearColor(0, 0, 0, 0);

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
    glViewport(0, 0, width, height);
    glColorMask(true, true, true, true);

    /* Clear the buffer, clear the matrix */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    /* A step backward, then spin the cube */
    glTranslatef(0, 0, -10);
    glRotatef(30, 1, 0, 0);
    glRotatef(alpha, 0, 1, 0);

    /* We tell we want to draw quads */
    glBegin(GL_QUADS);

    /* Every four calls to glVertex, a quad is drawn */
    glColor3f(0, 0, 0); glVertex3f(-1, -1, -1);
    glColor3f(0, 0, 1); glVertex3f(-1, -1,  1);
    glColor3f(0, 1, 1); glVertex3f(-1,  1,  1);
    glColor3f(0, 1, 0); glVertex3f(-1,  1, -1);

    glColor3f(1, 0, 0); glVertex3f( 1, -1, -1);
    glColor3f(1, 0, 1); glVertex3f( 1, -1,  1);
    glColor3f(1, 1, 1); glVertex3f( 1,  1,  1);
    glColor3f(1, 1, 0); glVertex3f( 1,  1, -1);

    glColor3f(0, 0, 0); glVertex3f(-1, -1, -1);
    glColor3f(0, 0, 1); glVertex3f(-1, -1,  1);
    glColor3f(1, 0, 1); glVertex3f( 1, -1,  1);
    glColor3f(1, 0, 0); glVertex3f( 1, -1, -1);

    glColor3f(0, 1, 0); glVertex3f(-1,  1, -1);
    glColor3f(0, 1, 1); glVertex3f(-1,  1,  1);
    glColor3f(1, 1, 1); glVertex3f( 1,  1,  1);
    glColor3f(1, 1, 0); glVertex3f( 1,  1, -1);

    glColor3f(0, 0, 0); glVertex3f(-1, -1, -1);
    glColor3f(0, 1, 0); glVertex3f(-1,  1, -1);
    glColor3f(1, 1, 0); glVertex3f( 1,  1, -1);
    glColor3f(1, 0, 0); glVertex3f( 1, -1, -1);

    glColor3f(0, 0, 1); glVertex3f(-1, -1,  1);
    glColor3f(0, 1, 1); glVertex3f(-1,  1,  1);
    glColor3f(1, 1, 1); glVertex3f( 1,  1,  1);
    glColor3f(1, 0, 1); glVertex3f( 1, -1,  1);

    /* No more quads */
    glEnd();

    /* Rotate a bit more */
    alpha = alpha + 0.1;

#ifdef NOESIS_GUI
    // Draw GUI
    xamlRenderer->Render(commands.commands.GetPtr());
#endif

    /* End */
    glFlush();
    glutSwapBuffers();

    /* Update again and again */
    glutPostRedisplay();
}

/*
** Function called when the window is created or resized
*/
void ReshapeFunc(int width_, int height_)
{
    width = width_;
    height = height_;

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(20, width / (float) height, 5, 15);

    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();

#ifdef NOESIS_GUI
    xamlRenderer->SetSize(width, height);
#endif
}

void KeyboardFunc(unsigned char key, int x, int y)
{
#ifdef NOESIS_GUI
    if (key == 9)
    {
        xamlRenderer->KeyDown(Noesis::Key_Tab);
    }
    else if (key == 8)
    {
        xamlRenderer->KeyDown(Noesis::Key_Back);
    }
    else
    {
        xamlRenderer->Char(key);
    }
#endif
}

void KeyboardUpFunc(unsigned char key, int x, int y)
{
#ifdef NOESIS_GUI
    if (key == 9)
    {
        xamlRenderer->KeyUp(Noesis::Key_Tab);
    }
    else if (key == 8)
    {
        xamlRenderer->KeyUp(Noesis::Key_Back);
    }
#endif
}

void MouseFunc(int button, int state, int x, int y)
{
#ifdef NOESIS_GUI
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_UP)
        {
            xamlRenderer->MouseButtonUp(x, y, MouseButton_Left);
        }
        else
        {
            xamlRenderer->MouseButtonDown(x, y, MouseButton_Left);
        }
    }
#endif
}

void MouseMove(int x, int y)
{
#ifdef NOESIS_GUI
    xamlRenderer->MouseMove(x, y);
#endif
}

#ifdef NOESIS_GUI
void ErrorHandler(const NsChar* filename, NsInt line, const NsChar* desc)
{
    printf("\nERROR: %s\n\n", desc);
    exit(1);
}

void Shutdown(void)
{
    // Free global resources and shutdown kernel
    xamlRenderer.Reset();
    Noesis::GUI::Shutdown();
}
#endif

int main(int argc, char **argv)
{
    /* Creation of the window */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Spinning cube");

#ifdef _MSC_VER
    glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)wglGetProcAddress("glBindFramebuffer");
    glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
#endif

#ifdef NOESIS_GUI
    {
        Noesis::GUI::InitOpenGL(ErrorHandler);
        Noesis::GUI::AddResourceProvider("..");
        
        // Create the UI renderer
        Ptr<FrameworkElement> xaml = Noesis::GUI::LoadXaml<FrameworkElement>("UI.xaml");
        xamlRenderer = Noesis::GUI::CreateRenderer(xaml.GetPtr());
        xamlRenderer->SetAntialiasingMode(Noesis::Gui::AntialiasingMode_PPAA);

        atexit(Shutdown);
    }
#endif

    /* Declaration of the callbacks */
    glutDisplayFunc(&DisplayFunc);
    glutReshapeFunc(&ReshapeFunc);
    glutKeyboardFunc(&KeyboardFunc);
    glutKeyboardUpFunc(&KeyboardUpFunc);
    glutMouseFunc(&MouseFunc);
    glutMotionFunc(&MouseMove);
    glutPassiveMotionFunc(&MouseMove);

    /* Loop */
    glutMainLoop();

    /* Never reached */
    return 0;
}

/* ========================================================================= */
