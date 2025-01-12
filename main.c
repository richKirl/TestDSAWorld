#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <sys/time.h>
#include "Window1/Window1_t.h"
#include "Time1/Time1_t.h"
#include "Shaders1/Shaders1.h"
#include "StaticObjects1/StaticObjects1.h"
#include "Skybox1/Skybox1.h"
#include "Lights1/Light1.h"
#include <time.h>
#include "Water1/Water1.h"
#include <wchar.h>
#include <string.h>
#include "Shaders1/MainShader.h"
#include "Camera1/Camera1.h"

bool firstMouse = false;
bool tab = false;
bool mouseHandleInCenter=false;
Window1 win;
Camera1 camera;

vec2 mousePos = (vec2){0.0f, 0.0f};

bool Update(float deltaTime)
{
    return true;
}
float dt = 0.0f;

vec2 WindowCenterPos(Window1 *win)
{
    return (vec2){win->wi / 2, win->he / 2};
}
static void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}
//
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    win.wi = width;
    win.he = height;
    glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    if (mouseHandleInCenter)
    {
        vec2 curMPos = WindowCenterPos(&win);
        vec2 delta = Subv2(curMPos, (vec2){xposIn, yposIn});
        rotateBy(&camera, -delta.x);
        rotateUD(&camera, -delta.y);
        glfwSetCursorPos(window, win.wi / 2, win.he / 2);
    }
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
    {
        tab=!tab;
        tab ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE):glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        
        // mouseHandleInCenter ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE):glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if(firstMouse)
        {
            glfwSetInputMode(win.win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            mouseHandleInCenter=!mouseHandleInCenter;
            firstMouse =!firstMouse;
        }
    }     

}

static void onMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    if( button==GLFW_MOUSE_BUTTON_LEFT )
    {
        if(!firstMouse)
        {
            glfwSetInputMode(win.win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            firstMouse =true;
            mouseHandleInCenter=true;
        }
    } 
}

int main(int argc, char *argv[])
{
    GLFWwindow *window;

    initWindow(&win, 1200, 900, "Test Game");
    window = win.win;
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetKeyCallback(window,key_callback);
    glfwSetMouseButtonCallback(window,onMouseButton);
    CameraInit(&camera, (vec3){0.0f, 0.0f, 3.0f}, (vec3){0.0f, 0.0f, -1.0f}, (vec3){0.0f, 1.0f, 0.0f}, (vec3){0, 0, 0}, 1.1f);

    Time1 ti;
    //   Initialize(1200, 900);
    initT(&ti);
    const char *path = "asset/models/SuzanneMiddle1.fbx";
    const char *path1 = "asset/models/SuzanneMiddle1.fbx";
    // printf("-1\n");

    StaticObject1 Obj1;
    StaticObject1 Obj2; // main

    LoadSetShaders(&Obj1.shaderMain, pathMainVert, pathMainFrag);
    PrepareObject(&Obj1, path, &Obj1.shaderMain);
    PrepareObject(&Obj2, path1, &Obj1.shaderMain);
    // printf("-2\n");
    SetPosRotScale(&Obj1, (vec3){20.0f, -1.0f, -15.0f}, 0.0f, (vec3){1.0f, 0.0f, 0.0f}, (vec3){0.0f, 1.0f, 0.0f}, (vec3){0.0f, 0.0f, 1.0f}, (vec3){5.5f, 5.5f, 5.5f});
    SetPosRotScale(&Obj2, (vec3){-10.0f, -1.0f, -15.0f}, 0.0f, (vec3){1.0f, 0.0f, 0.0f}, (vec3){0.0f, 1.0f, 0.0f}, (vec3){0.0f, 0.0f, 1.0f}, (vec3){2.5f, 2.5f, 2.5f});
    Water1 water;
    PreparePlane(&water, &Obj1.shaderMain, 0, 0, 300);
    SetPosRotScaleW(&water, (vec3){-100.0f, -2.24f, -100.0f}, 0.0f, (vec3){1.0f, 0.0f, 0.0f}, (vec3){0.0f, 1.0f, 0.0f}, (vec3){0.0f, 0.0f, 1.0f}, (vec3){1.f, 1.f, 1.f});

    Light1 light;
    // setLightAmbientAndDiffuse(&light,Obj1.shaderMain.shaderProgram,(vec3){0.0f,0.0f,5.0f},(vec3){1.0f,1.0f,1.0f},(vec3){0.0f,-1.0f,-1.0f},0.5f,true,(vec3){0.5f,0.5f,0.5f},true);

    Skybox1 skybox;

    PrepareShaderAndBuffer(&skybox, pathSkyboxVert, pathSkyboxFrag);
    LoadTexturesSkybox(&skybox);
    SetTextureForW(&water, &skybox.TextureID);
    glEnable(GL_MULTISAMPLE_ARB);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1);
    glDisable(GL_DITHER);
    //   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //   testAddQ();
    while (!glfwWindowShouldClose(win.win))
    {
        mat4 P = Perspectivem4(80.0f, (float)win.wi / win.he, 1.0f, 1100.0f);
        mat4 V = lookAtm4(camera.cameraPos, camera.vp, camera.cameraUp); // Addv3(cameraPos,cameraFront)
        //-----------------------------------------------------------------------------------------
        // updateIOFromWindow
        processInput(&win, &camera);
        // updateTime
        provideT(&ti);
        if (!Update((float)ti.deltaTime))
        {
            break;
        }
        // Render
        //  Render()models;
        //   if(tab) toggleWariframe=!toggleWariframe;
        
        //-----------------------------------------------------------------------------------------
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // setLightAmbientAndDiffuse(&light,Obj1.shaderMain.shaderProgram,(vec3){0.0f,0.0f,5.0f},(vec3){0.8f, 0.8f, 0.8f},(vec3){0.0f,-1.0f,-1.0f},0.5f,true,(vec3){0.8f, 0.8f, 0.8f},false);

        // resetSh();

        RenderObject(&Obj1, &V, &P, 1);
        RenderObject(&Obj2, &V, &P, 1);
        RenderObjectW(&water, &V, &P, 2, dt);
        setLightAmbientAndDiffuse(&light, Obj1.shaderMain.shaderProgram, (vec3){0.0f, 0.0f, 5.0f}, (vec3){1.0f, 1.0f, 1.0f}, (vec3){0.0f, -1.0f, -1.0f}, 0.5f, true, (vec3){0.5f, 0.5f, 0.5f}, true);

        RenderSkybox(&skybox, &V, &P);
        //-----------------------------------------------------------------------------------------
        // Present frame
        // UpdateBufferFromWindow
        // updateTime
        updateT(&ti);
        //-----------------------------------------------------------------------------------------
        if (dt == 360.0f)
            dt = 0.1f;
        dt += 0.01f;
        updateWindow(&win);
    }
    CloseObject(&Obj1);
    CloseObject(&Obj2);
    CloseObjectW(&water);
    ClearSkybox(&skybox);
    closeWindow(&win);
    return 0;
}