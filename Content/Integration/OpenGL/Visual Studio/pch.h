#pragma once

#define NOESIS_GUI

#ifdef NOESIS_GUI
    #include <NoesisGUI.h>
#endif

#include <stdlib.h>

#ifdef _MSC_VER
    #include <windows.h>
    #include <GL/gl.h>
    #include "glut.h"
#else
    #include <GLUT/glut.h>
#endif
