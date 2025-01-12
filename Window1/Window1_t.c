#include "Window1_t.h"

#if WindowX11111
// typedef GLXContext (*glXCreateContextAttribsARBProc)(Display *, GLXFBConfig, GLXContext, Bool, const int *);
// static bool ctxErrorOccurred = false;
// static int ctxErrorHandler(Display *dpy, XErrorEvent *ev)
// {
// 	ctxErrorOccurred = true;
// 	return 0;
// }
// static Bool WaitForMapNotify(Display *d, XEvent *e, char *arg)
// {
// 	return d && e && arg && (e->type == MapNotify) && (e->xmap.window == *(Window *)arg);
// }
// XSetWindowAttributes attr = {
// 	0,
// };
// static void describe_fbconfig(GLXFBConfig fbconfig, Display *Xdisplay)
// {
// 	int doublebuffer;
// 	int red_bits, green_bits, blue_bits, alpha_bits, depth_bits;

// 	glXGetFBConfigAttrib(Xdisplay, fbconfig, GLX_DOUBLEBUFFER, &doublebuffer);
// 	glXGetFBConfigAttrib(Xdisplay, fbconfig, GLX_RED_SIZE, &red_bits);
// 	glXGetFBConfigAttrib(Xdisplay, fbconfig, GLX_GREEN_SIZE, &green_bits);
// 	glXGetFBConfigAttrib(Xdisplay, fbconfig, GLX_BLUE_SIZE, &blue_bits);
// 	glXGetFBConfigAttrib(Xdisplay, fbconfig, GLX_ALPHA_SIZE, &alpha_bits);
// 	glXGetFBConfigAttrib(Xdisplay, fbconfig, GLX_DEPTH_SIZE, &depth_bits);

// 	fprintf(stderr, "FBConfig selected:\n"
// 					"Doublebuffer: %s\n"
// 					"Red Bits: %d, Green Bits: %d, Blue Bits: %d, Alpha Bits: %d, Depth Bits: %d\n",
// 			doublebuffer == True ? "Yes" : "No",
// 			red_bits, green_bits, blue_bits, alpha_bits, depth_bits);
// }
// // Helper to check for extension string presence.  Adapted from:
// //   http://www.opengl.org/resources/features/OGLextensions/
// static bool isExtensionSupported(const char *extList, const char *extension)
// {
// 	const char *start;
// 	const char *where, *terminator;

// 	/* Extension names should not have spaces. */
// 	where = strchr(extension, ' ');
// 	if (where || *extension == '\0')
// 		return false;

// 	/* It takes a bit of care to be fool-proof about parsing the
// 	   OpenGL extensions string. Don't be fooled by sub-strings,
// 	   etc. */
// 	for (start = extList;;)
// 	{
// 		where = strstr(start, extension);

// 		if (!where)
// 			break;

// 		terminator = where + strlen(extension);

// 		if (where == start || *(where - 1) == ' ')
// 			if (*terminator == ' ' || *terminator == '\0')
// 				return true;

// 		start = terminator;
// 	}

// 	return false;
// }
// int initialWindow1(Window1 *win, int xw, int yw, const char *t)
// {
// 	win->wi = xw;
// 	win->he = yw;
// 	win->title = t;
// 	win->Xdisplay = XOpenDisplay(NULL);
// 	if (!win->Xdisplay)
// 	{
// 		// fatalError("Couldn't connect to X server\n");
// 	}
// 	win->Xscreen = DefaultScreen(win->Xdisplay);
// 	win->Xroot = RootWindow(win->Xdisplay, win->Xscreen);

// 	win->fbconfigs = glXChooseFBConfig(win->Xdisplay, win->Xscreen, VisData, &win->numfbconfigs);
// 	win->fbconfig = 0;
// 	for (int i = 0; i < win->numfbconfigs; i++)
// 	{
// 		win->visual = (XVisualInfo *)glXGetVisualFromFBConfig(win->Xdisplay, win->fbconfigs[i]);
// 		if (!win->visual)
// 			continue;

// 		win->pict_format = XRenderFindVisualFormat(win->Xdisplay, win->visual->visual);
// 		if (!win->pict_format)
// 			continue;

// 		win->fbconfig = win->fbconfigs[i];
// 		if (win->visual->depth == 24)
// 		{
// 			break;
// 		}
// 		XFree(win->visual);
// 	}

// 	if (!win->fbconfig)
// 	{
// 		// fatalError("No matching FB config found");
// 	}

// 	describe_fbconfig(win->fbconfig, win->Xdisplay);

// 	/* Create a colormap - only needed on some X clients, eg. IRIX */
// 	win->cmap = XCreateColormap(win->Xdisplay, win->Xroot, win->visual->visual, AllocNone);

// 	attr.colormap = win->cmap;
// 	attr.background_pixmap = None;
// 	attr.border_pixmap = None;
// 	attr.border_pixel = 0;
// 	attr.event_mask =
// 		StructureNotifyMask |
// 		EnterWindowMask |
// 		LeaveWindowMask |
// 		ExposureMask |
// 		ButtonPressMask |
// 		ButtonReleaseMask |
// 		OwnerGrabButtonMask |
// 		KeyPressMask |
// 		PointerMotionMask|
// 		KeyReleaseMask;

// 	win->attr_mask =
// 		//	CWBackPixmap|
// 		CWColormap |
// 		CWBorderPixel |
// 		CWEventMask;

// 	win->width = DisplayWidth(win->Xdisplay, DefaultScreen(win->Xdisplay)) / 2;
// 	win->height = DisplayHeight(win->Xdisplay, DefaultScreen(win->Xdisplay)) / 2;
// 	win->x = win->width / 2, win->y = win->height / 2;

// 	// win->width=xw;
// 	// win->height=yw;

// 	win->window_handle = XCreateWindow(win->Xdisplay,
// 									   win->Xroot,
// 									   win->x - 100, win->y - 200, xw, yw,
// 									   0,
// 									   win->visual->depth,
// 									   InputOutput,
// 									   win->visual->visual,
// 									   win->attr_mask, &attr);

// 	if (!win->window_handle)
// 	{
// 		// fatalError("Couldn't create the window\n");
// 	}
// 	// #if USE_GLX_CREATE_WINDOW
// 	// 	fputs("glXCreateWindow ", stderr);
// 	// 	int glXattr[] = { None };
// 	// 	glX_window_handle = glXCreateWindow(Xdisplay, fbconfig, window_handle, glXattr);
// 	// 	if( !glX_window_handle ) {
// 	// 		// fatalError("Couldn't create the GLX window\n");
// 	// 	}
// 	// #else
// 	win->glX_window_handle = win->window_handle;
// 	// #endif

// 	win->textprop.value = (unsigned char *)win->title;
// 	win->textprop.encoding = XA_STRING;
// 	win->textprop.format = 8;
// 	win->textprop.nitems = strlen(win->title);

// 	win->hints.x = win->x;
// 	win->hints.y = win->y;
// 	win->hints.width = xw;
// 	win->hints.height = yw;
// 	win->hints.flags = USPosition | USSize;

// 	win->startup_state = XAllocWMHints();
// 	win->startup_state->initial_state = NormalState;
// 	win->startup_state->flags = StateHint;

// 	XSetWMProperties(win->Xdisplay, win->window_handle, &win->textprop, &win->textprop,
// 					 NULL, 0,
// 					 &win->hints,
// 					 win->startup_state,
// 					 NULL);

// 	XFree(win->startup_state);

// 	XMapWindow(win->Xdisplay, win->window_handle);
// 	XIfEvent(win->Xdisplay, &win->ev, WaitForMapNotify, (char *)&win->window_handle);

// 	if ((win->del_atom = XInternAtom(win->Xdisplay, "WM_DELETE_WINDOW", 0)) != None)
// 	{
// 		XSetWMProtocols(win->Xdisplay, win->window_handle, &win->del_atom, 1);
// 	}
// 	// // Redirect Close
// 	// Atom atomWmDeleteWindow = XInternAtom(Xdisplay, "WM_DELETE_WINDOW", False);
// 	// XSetWMProtocols(Xdisplay, window_handle, &atomWmDeleteWindow, 1);
// 	printf("Making context current\n");
// 	int dummy;
// 	if (!glXQueryExtension(win->Xdisplay, &dummy, &dummy))
// 	{
// 		// fatalError("OpenGL not supported by X server\n");
// 	}

// 	// #if USE_GLX_CREATE_CONTEXT_ATTRIB
// #define GLX_CONTEXT_MAJOR_VERSION_ARB 0x2091
// #define GLX_CONTEXT_MINOR_VERSION_ARB 0x2092
// 	win->render_context = NULL;
// 	if (isExtensionSupported(glXQueryExtensionsString(win->Xdisplay, DefaultScreen(win->Xdisplay)), "GLX_ARB_create_context"))
// 	{
// 		typedef GLXContext (*glXCreateContextAttribsARBProc)(Display *, GLXFBConfig, GLXContext, Bool, const int *);
// 		glXCreateContextAttribsARBProc glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddressARB("glXCreateContextAttribsARB");
// 		if (glXCreateContextAttribsARB)
// 		{
// 			printf("Initialisation\n");
// 			int context_attribs[] =
// 				{
// 					GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
// 					GLX_CONTEXT_MINOR_VERSION_ARB, 6,
// 					GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
// 					// GLX_CONTEXT_FLAGS_ARB        , GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
// 					None};

// 			int (*oldHandler)(Display *, XErrorEvent *) = XSetErrorHandler(&ctxErrorHandler);

// 			win->render_context = glXCreateContextAttribsARB(win->Xdisplay, win->fbconfig, 0, True, context_attribs);

// 			XSync(win->Xdisplay, False);
// 			XSetErrorHandler(oldHandler);
// 		}
// 		else
// 		{
// 			fputs("glXCreateContextAttribsARB could not be retrieved\n", stderr);
// 		}
// 	}
// 	else
// 	{
// 		fputs("glXCreateContextAttribsARB not supported\n", stderr);
// 	}

// 	if (!win->render_context)
// 	{
// 		fputs("using fallback\n", stderr);
// 		// #else
// 		// 	{
// 		// #endif
// 		// win->render_context = glXCreateNewContext(win->Xdisplay, win->fbconfig, GLX_RGBA_TYPE, 0, True);
// 		// 		if (!render_context) {
// 		// 			// fatalError("Failed to create a GL context\n");
// 		// 		}
// 	}

// 	if (!glXMakeContextCurrent(win->Xdisplay, win->glX_window_handle, win->glX_window_handle, win->render_context))
// 	{
// 		// fatalError("glXMakeCurrent failed for window\n");
// 	}

// 	return 0;
// }

// int closeWindow1(Window1 *win)
// {
// 	glXMakeCurrent(win->Xdisplay, 0, 0);
// 	glXDestroyContext(win->Xdisplay, win->render_context);

// 	XFree(win->visual);
// 	XFreeColormap(win->Xdisplay, win->cmap);
// 	XDestroyWindow(win->Xdisplay, win->window_handle);

// 	XCloseDisplay(win->Xdisplay);
// 	return 0;
// }

// void updateBuffer(Window1 *win)
// {
// 	glXSwapBuffers(win->Xdisplay, win->glX_window_handle);
// }
#endif
void Initialize(int w, int h)
{

    glClearColor(0.5f, 0.6f, 0.7f, 1.0f);
    glViewport(0, 0, w, h);
}

void processInput(Window1 *w, Camera1 *camera)
{
    if (glfwGetKey(w->win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(w->win, GLFW_TRUE);
    if (glfwGetKey(w->win, GLFW_KEY_W) == GLFW_PRESS)
        moveBy(camera, 1.0f);
    if (glfwGetKey(w->win, GLFW_KEY_S) == GLFW_PRESS)
        moveBy(camera, -1.0f);
    if (glfwGetKey(w->win, GLFW_KEY_D) == GLFW_PRESS)
        rotateBy(camera, 1.0f);
    if (glfwGetKey(w->win, GLFW_KEY_A) == GLFW_PRESS)
        rotateBy(camera, -1.0f);
    // if(glfwGetKey(window, GLFW_KEY_TAB)  == GLFW_PRESS){
    //     tab=true;
    //     // toggleWariframe=!toggleWariframe;
    // }
    // if(glfwGetKey(window, GLFW_KEY_TAB)  == GLFW_RELEASE)
    //     tab=false;
}

void initWindow(Window1 *w, int ww, int hh, const char *c)
{
    w->wi = ww;
    w->he = hh;

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 8);
    w->win = glfwCreateWindow(w->wi, w->he, c, NULL, NULL);
    if (!w->win)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(w->win);

    glfwSetCursorPos(w->win, w->wi / 2, w->he / 2);
    // tell GLFW to capture our mouse
    glfwSetInputMode(w->win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glewExperimental = true;
    glewInit();
    glfwSwapInterval(1);

    Initialize(ww, hh);
}

void updateWindow(Window1 *w)
{
    glfwSwapBuffers(w->win);
    glfwPollEvents();
}

void closeWindow(Window1 *w)
{
    glfwDestroyWindow(w->win);

    glfwTerminate();
}
