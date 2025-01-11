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

float lastX =  1200.0f / 2.0;
float lastY =  900.0 / 2.0;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
bool firstMouse = true;
bool toggleWariframe = false;
bool tab=false;
bool toggleWarframe()
{
    return toggleWariframe;
}
// camera
vec3 cameraPos = (vec3){0.0f, 0.0f, 3.0f};
vec3 cameraFront = (vec3){0.0f, 0.0f, -1.0f};
vec3 cameraUp = (vec3){0.0f, 1.0f, 0.0f};
vec3 vp = (vec3){0, 0, 0};
float cameraSpeed = 1.1f;
vec2 mousePos = (vec2){0.0f, 0.0f};
void Resize(int w, int h)
{
    glViewport(0, 0, w, h);
}
bool Initialize(int w, int h)
{

    glClearColor(0.5f, 0.6f, 0.7f, 1.0f);
    glViewport(0, 0, w, h);
    return true;
}
bool Update(float deltaTime)
{
    return true;
}
float dt = 0.0f;
Window1 win;
vec3 getNormalView()
{
    return Normalizev3(Subv3(vp,cameraPos));
}
void rotateBy(float deg)
{
    Quaternion q;
    q=QAngleAxisdV3(deg,(vec3){0,1,0});
    mat4 rot;
    rot=ToMatrixQQ1(q);
    vec3 tN = getNormalView();
    vec4 rotViewVec = Mulmv4(rot, (vec4){tN.x, tN.y, tN.z, 0});

    vp = Addv3(cameraPos, (vec3){rotViewVec.x, rotViewVec.y, rotViewVec.z});
}
vec2 WindowCenterPos(Window1 *win)
{
    return (vec2){win->wi/2,win->he/2};
}
void rotateUD(float deg)
{
    vec3 viewVector = getNormalView();
    vec3 viewVectorNoY = Normalizev3((vec3){viewVector.x, 0.0f, viewVector.z});

    float currentAngleDegrees = Anglev3(viewVectorNoY,viewVector);
    if (viewVector.y < 0.0f) {
        currentAngleDegrees = -currentAngleDegrees;
    }

    float newAngleDegrees = currentAngleDegrees + deg;
    if (newAngleDegrees > -85.0f && newAngleDegrees < 85.0f)
    {
        vec3 rotationAxis = Crossv3(getNormalView(), cameraUp);
        rotationAxis = Normalizev3(rotationAxis);

        Quaternion q;
        q = QAngleAxisdV3(deg, rotationAxis);
        mat4 rot;
        rot = ToMatrixQQ1(q);
        vec3 tN = getNormalView();
        vec4 rotViewVec = Mulmv4(rot, (vec4){tN.x, tN.y, tN.z, 0});

        vp = Addv3(cameraPos, (vec3){rotViewVec.x, rotViewVec.y, rotViewVec.z});
    }
}
void moveBy(float deg)
{
    vec3 vOffset = getNormalView();
    vOffset = Mulv3c(vOffset, deg);
    cameraPos = Addv3(cameraPos, vOffset);
    vp = Addv3(vp, vOffset);
}
static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
 void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    win.wi =width; win.he=height;
    glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    vec2 curMPos=WindowCenterPos(&win);
    vec2 delta = Subv2(curMPos , (vec2){xposIn,yposIn});
    rotateBy(-delta.x);
    rotateUD(-delta.y);
    glfwSetCursorPos(window,win.wi/2,win.he/2);
}
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        moveBy(1.0f);
    if(glfwGetKey(window, GLFW_KEY_S)  == GLFW_PRESS)
        moveBy(-1.0f);
    if(glfwGetKey(window, GLFW_KEY_D)  == GLFW_PRESS)
        rotateBy(1.0f);
    if(glfwGetKey(window, GLFW_KEY_A)  == GLFW_PRESS)
        rotateBy(-1.0f);
    if(glfwGetKey(window, GLFW_KEY_TAB)  == GLFW_PRESS){
        tab=true;
        // toggleWariframe=!toggleWariframe;
    }
    if(glfwGetKey(window, GLFW_KEY_TAB)  == GLFW_RELEASE)
        tab=false;
}

int main(int argc, char *argv[])
{
    glfwSetErrorCallback(error_callback);
 
    if (!glfwInit())
        exit(EXIT_FAILURE);
 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 8);
    GLFWwindow* window = glfwCreateWindow(1200, 900, "Test Window", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetCursorPos(window,win.wi/2,win.he/2);
        // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glewExperimental = true;
    glewInit();
    glfwSwapInterval(1);



      Time1 ti;
      Initialize(1200, 900);
      initT(&ti);
      const char *path = "asset/models/SuzanneMiddle1.fbx";
      const char *path1 = "asset/models/SuzanneMiddle1.fbx";
      // printf("-1\n");
      win.wi = 1200;
      win.he = 900;
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
    while (!glfwWindowShouldClose(window))
    {
          mat4 P = Perspectivem4(80.0f, (float)win.wi / win.he, 1.0f, 1100.0f);
          mat4 V = lookAtm4(cameraPos, vp, cameraUp); // Addv3(cameraPos,cameraFront)
          //-----------------------------------------------------------------------------------------
          // updateIOFromWindow
          processInput(window);
          // updateTime
          provideT(&ti);
          if (!Update((float)ti.deltaTime))
          {
              break;
          }
          // Render
          //  Render()models;
        //   if(tab) toggleWariframe=!toggleWariframe;
        //   toggleWariframe ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE):glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    CloseObject(&Obj1);
    CloseObject(&Obj2);
    CloseObjectW(&water);
    ClearSkybox(&skybox);
    glfwDestroyWindow(window);
 
    glfwTerminate();
    return 0;
}