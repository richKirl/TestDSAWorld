#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <sys/time.h>
#include "Window1/Window1_t.h"
#include "Time1/Time1_t.h"
#include "StaticObjects1/StaticObjects1.h"
#include "Skybox1/Skybox1.h"
#include "Lights1/Light1.h"
#include "Water1/Water1.h"
#include "Shaders1/MainShader.h"
#include "Camera1/Camera1.h"
#include "Particles1/Particles1.h"
#include "Picking1/Picking.h"
#include "Heightmap1/Heightmap1.h"
bool firstMouse = false;
bool tab = false;
bool mouseHandleInCenter = false;
bool screenshoot = false;
bool renderScene = true;
int idi[] = {100, 101};
Window1 win;
Camera1 camera;
Picking1 pick;

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
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
    {
        tab = !tab;
        tab ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {

        if (firstMouse)
        {
            glfwSetCursorPos(window, win.wi / 2, win.he / 2);
            glfwSetInputMode(win.win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            mouseHandleInCenter = !mouseHandleInCenter;
            firstMouse = !firstMouse;
        }
        else if (!firstMouse)
            glfwSetWindowShouldClose(win.win, GLFW_TRUE);
    }
    else if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
    {

        if (screenshoot)
        {

            // {
            // // glBindTexture(GL_TEXTURE_2D, compressed_decal_map);
            // // glTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGB_ARB, width, height,0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
            // // glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPRESSED_ARB, &compressed);
            // // /* if the compression has been successful */
            // // if (compressed == GL_TRUE)
            // // {
            // // glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT,&internalformat);
            // // glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPRESSED_IMAGE_SIZE_ARB,&compressed_size);
            // // unsigned char *img = (unsigned char *)malloc(compressed_size * sizeof(unsigned char));
            // // glGetCompressedTexImageARB(GL_TEXTURE_2D, 0, img);
            // // SaveTexture(width, height, compressed_size, img, internalFormat, 0);
            // }

            unsigned char tgaHeader[12] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            unsigned char header[6];
            unsigned char bits = 0;
            int colorMode = 0;
            unsigned char tempColors = 0;
            colorMode = 3;
            bits = 24;

            // Записываем ширину и высоту:
            header[0] = win.wi % 256;
            header[1] = win.wi / 256;
            header[2] = win.he % 256;
            header[3] = win.he / 256;
            header[4] = bits;
            header[5] = 0;
            unsigned char *output = malloc(win.wi * win.he * 3);
            glReadBuffer(GL_FRONT);
            glPixelStorei(GL_PACK_ALIGNMENT, 1);
            glReadPixels(0, 0, win.wi, win.he, GL_BGR, GL_UNSIGNED_BYTE, output);
            FILE *sFile = 0;
            sFile = fopen("Screen.tga", "wb");
            fwrite(tgaHeader, sizeof(tgaHeader), 1, sFile);
            fwrite(header, sizeof(header), 1, sFile);

            // Записываем данные изображения:
            fwrite(output, win.wi * win.he * colorMode, 1, sFile);
            fclose(sFile);
            free(output);
            screenshoot = !screenshoot;
        }
    }
}

static void onMouseButton(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (!firstMouse)
        {
            glfwSetInputMode(win.win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            firstMouse = true;
            mouseHandleInCenter = true;
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
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, onMouseButton);
    CameraInit(&camera, (vec3){0.0f, 0.0f, 3.0f}, (vec3){0.0f, 0.0f, -1.0f}, (vec3){0.0f, 1.0f, 0.0f}, (vec3){0, 0, 0}, 1.1f);

    Time1 ti;
    //   Initialize(1200, 900);
    initT(&ti);
    const char *path = "asset/models/SuzanneMiddle1.fbx";
    const char *path1 = "asset/models/SuzanneMiddle1.fbx";
    // printf("-1\n");

    StaticObject1 Obj1;
    StaticObject1 Obj2;

    LoadSetShaders(&Obj1.shaderMain, pathMainVert, pathMainFrag); // main
    PrepareObject(&Obj1, path, &Obj1.shaderMain);
    PrepareObject(&Obj2, path1, &Obj1.shaderMain);
    // printf("-2\n");
    SetPosRotScale(&Obj1, (vec3){20.0f, -1.0f, -15.0f}, 0.0f, (vec3){1.0f, 0.0f, 0.0f}, (vec3){0.0f, 1.0f, 0.0f}, (vec3){0.0f, 0.0f, 1.0f}, (vec3){5.5f, 5.5f, 5.5f});
    SetPosRotScale(&Obj2, (vec3){-10.0f, -1.0f, -15.0f}, 0.0f, (vec3){1.0f, 0.0f, 0.0f}, (vec3){0.0f, 1.0f, 0.0f}, (vec3){0.0f, 0.0f, 1.0f}, (vec3){2.5f, 2.5f, 2.5f});
    Water1 water;
    PreparePlane(&water, &Obj1.shaderMain, 0, 0, 200);//water/orplaneforcavern00200,-200,1.24,-200
    SetPosRotScaleW(&water, (vec3){-200.0f, 1.24f,-200.0f}, 0.0f, (vec3){1.0f, 0.0f, 0.0f}, (vec3){0.0f, 1.0f, 0.0f}, (vec3){0.0f, 0.0f, 1.0f}, (vec3){4.f, 1.f, 4.f});

    Light1 light;
    // setLightAmbientAndDiffuse(&light,Obj1.shaderMain.shaderProgram,(vec3){0.0f,0.0f,5.0f},(vec3){1.0f,1.0f,1.0f},(vec3){0.0f,-1.0f,-1.0f},0.5f,true,(vec3){0.5f,0.5f,0.5f},true);

    Skybox1 skybox;

    PrepareShaderAndBuffer(&skybox, pathSkyboxVert, pathSkyboxFrag);
    LoadTexturesSkybox(&skybox);
    SetTextureForW(&water, &skybox.TextureID);

    Particles particke;
    InitParticles(&particke);
    SetPosRotScaleP(&particke, (vec3){0.0f, 0.0f, 0.0f}, 0.0f, (vec3){1.0f, 0.0f, 0.0f}, (vec3){0.0f, 1.0f, 0.0f}, (vec3){0.0f, 0.0f, 1.0f}, (vec3){100.f, 100.f, 1.f});

    initFBORBO(&pick, win.wi, win.he);
    setFBO(&Obj1, &pick.shader);
    setFBO(&Obj2, &pick.shader);

    Heightmap1 heitmap;
    setShader(&heitmap, &Obj1.shaderMain);
    initH(&heitmap, 200, 200, 125, 10, 20, 1, 3); //caverns (200,200,125,10,20,1,3)scale400,50,400
    SetPosRotScaleH(&heitmap, (vec3){0.0f, 0.0f, 0.0f}, 0.0f, (vec3){1.0f, 0.0f, 0.0f}, (vec3){0.0f, 1.0f, 0.0f}, (vec3){0.0f, 0.0f, 1.0f}, (vec3){400.f, 50.f, 400.f});
    // glEnable(GL_MULTISAMPLE_ARB);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);
    glDisable(GL_DITHER);
    //   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //   testAddQ();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    while (!glfwWindowShouldClose(win.win))
    {
        mat4 Proj = Perspectivem4(80.0f, (float)win.wi / win.he, 1.0f, 1100.0f);
        mat4 View = lookAtm4(camera.cameraPos, camera.vp, camera.cameraUp); // Addv3(cameraPos,cameraFront)
        mat4 OrthoMat = setOrthoFrustumm4(0.0f, (float)win.wi, 0.0f, (float)win.he, -1.0f, 2.f);
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
        //-----------------------------------------------------------------------------------------
        // if(renderScene==true){
        bindFBOdefault(&pick);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // setLightAmbientAndDiffuse(&light,Obj1.shaderMain.shaderProgram,(vec3){0.0f,0.0f,5.0f},(vec3){0.8f, 0.8f, 0.8f},(vec3){0.0f,-1.0f,-1.0f},0.5f,true,(vec3){0.8f, 0.8f, 0.8f},false);
        // GUI
        RenderParticles(&particke, &Proj, &OrthoMat);
        // resetSh();
        // gameObjects
        RenderObject(&Obj1, &View, &Proj, 1);

        RenderObject(&Obj2, &View, &Proj, 1);

        // light
        setLightAmbientAndDiffuse(&light, Obj1.shaderMain.shaderProgram, (vec3){0.0f, 0.0f, 5.0f}, (vec3){1.0f, 1.0f, 1.0f}, (vec3){0.0f, -1.0f, -1.0f}, 0.5f, true, (vec3){0.5f, 0.5f, 0.5f}, true);
        // Skybox
        RenderSkybox(&skybox, &View, &Proj);
        // terrain
        RenderHeightMap(&heitmap, &View, &Proj, 1);
        // Water
        RenderObjectW(&water, &View, &Proj, 2, dt);
        // }

        //-----------------------------------------------------------------------------------------
        bindFBOdefault(&pick);
        // Present frame
        // UpdateBufferFromWindow
        // updateTime
        updateT(&ti);
        //-----------------------------------------------------------------------------------------
        if (dt == 360.0f)
            dt = 0.1f;
        dt += 0.01f;
        updateWindow(&win);
        if (glfwGetMouseButton(win.win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            renderScene = false;
            printf("LEFTBUTTON\n");
            int r;
            int g;
            int b;
            int fr;
            int fg;
            int fb;
            bindFBO(&pick);
            Initialize(win.wi, win.he);
            //
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            for (int i = 0; i < 2; i++)
            {
                r = idi[i] & 0xFF;
                g = (idi[i] >> 8) & 0xFF;
                b = (idi[i] >> 16) & 0xFF;
                fr = r / 255.0f;
                fg = g / 255.0f;
                fb = b / 255.0f;
            }
            RenderObjectFBO(&Obj1, &View, &Proj, (vec4){fr, fg, fb, 1.0});
            bindAsReadBindAsDrawBlit(&pick, win.wi, win.he);
            unsigned char data[4];
            glReadPixels(win.wi / 2, win.he / 2, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, data);
            int gr, gg, gb;
            gr = data[0];
            gg = data[1];
            gb = data[2];
            int pickedID = gr | (gg << 8) | (gb << 16);
            if (pickedID == 0x00ffffff)
            { // Full white, must be the background !
              // message = "background";
            }
            else
            {
                printf("mesh %d\n", pickedID);
            }
            renderScene = true;
        }
    }
    closeH(&heitmap);
    delbrd(&pick);
    closeParticles(&particke);
    CloseObject(&Obj1);
    CloseObject(&Obj2);
    CloseObjectW(&water);
    ClearSkybox(&skybox);
    closeWindow(&win);
    return 0;
}
