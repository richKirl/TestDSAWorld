#ifndef __WINDOW1_T__
#define __WINDOW1_T__
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Math1/WTMath.h"
#include "../Camera1/Camera1.h"

struct Window1_t
{
    int wi, he;
    GLFWwindow* win;
    
};
typedef struct Window1_t Window1;
void Initialize(int w, int h);
void initWindow(Window1 *w,int ww, int hh,const char* c);
void processInput(Window1 *w,Camera1 *camera);
void updateWindow(Window1 *w);
void closeWindow(Window1 *w);

#endif