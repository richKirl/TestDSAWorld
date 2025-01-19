#include "Window1_t.h"

void Initialize(int w, int h)
{
    glClearColor(0.5f, 0.6f, 0.7f, 1.0f);
    glViewport(0, 0, w, h);
}

void processInput(Window1 *w, Camera1 *camera)
{
    if (glfwGetKey(w->win, GLFW_KEY_W) == GLFW_PRESS)
        moveBy(camera, 1.0f);
    if (glfwGetKey(w->win, GLFW_KEY_S) == GLFW_PRESS)
        moveBy(camera, -1.0f);
    if (glfwGetKey(w->win, GLFW_KEY_D) == GLFW_PRESS)
        rotateBy(camera, 1.0f);
    if (glfwGetKey(w->win, GLFW_KEY_A) == GLFW_PRESS)
        rotateBy(camera, -1.0f);
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
