#ifndef __WINDOW1_T__
#define __WINDOW1_T__

#include <stdlib.h>
#if WindowX11111
// #include <stdio.h>
// #include <stdbool.h>
// #include <string.h>
// #include <unistd.h>

// #include <X11/Xlib.h>
// #include <X11/Xutil.h>
// #include <X11/Xatom.h>
// #include <X11/extensions/Xrender.h>
// #include <X11/Xutil.h>
// #include <GL/gl.h>
// #include <GL/glx.h>
// static int VisData[] = {
//     GLX_X_RENDERABLE, True,
//     GLX_RENDER_TYPE, GLX_RGBA_BIT,
//     GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
//     GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
//     GLX_DOUBLEBUFFER, True,
//     GLX_RED_SIZE, 8,
//     GLX_GREEN_SIZE, 8,
//     GLX_BLUE_SIZE, 8,
//     GLX_ALPHA_SIZE, 8,
//     GLX_STENCIL_SIZE, 8,
//     GLX_DEPTH_SIZE, 24,
//     GLX_SAMPLE_BUFFERS, 1,
//     GLX_SAMPLES, 4,
//     None};
#endif
struct Window1_t
{
#if WindowX11111
    // int Xscreen;
    // Atom del_atom;
    // Colormap cmap;
    // Display *Xdisplay;
    // XVisualInfo *visual;
    // XRenderPictFormat *pict_format;
    // GLXFBConfig *fbconfigs, fbconfig;
    // int numfbconfigs;
    // GLXContext render_context;
    // Window Xroot, window_handle;
    // GLXWindow glX_window_handle;
    // int x, y, attr_mask;
    // XSizeHints hints;
    // XWMHints *startup_state;
    // XTextProperty textprop;
    // XEvent ev;
    // char *title; // = "Test Window";
#endif
    int width, height, wi, he;

};
typedef struct Window1_t Window1;
#if WindowX11111
// int initialWindow1(Window1 *win, int xw, int yw, const char *t);
// int closeWindow1(Window1 *win);
// void updateBuffer(Window1 *win);
#endif
#endif