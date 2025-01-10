#ifndef __SKYBOX1_T__
#define __SKYBOX1_T__

#include "../Shaders1/ShProgram1.h"
#include "../Buffs1/Buff1.h"
#include "../Math1/WTMath.h"
// #include "../Shaders1/Shaders1.h"

static vec3 SkyboxVerts[36] =
    {
        // Front face
        (vec3){-1000.f, 1000.f, 1000.f}, (vec3){1000.f, 1000.f, 1000.f}, (vec3){1000.f, -1000.f, 1000.f}, (vec3){1000.f, -1000.f, 1000.f}, (vec3){-1000.f, -1000.f, 1000.f}, (vec3){-1000.f, 1000.f, 1000.f},
        // Back face
        (vec3){1000.f, 1000.f, -1000.f}, (vec3){-1000.f, 1000.f, -1000.f}, (vec3){-1000.f, -1000.f, -1000.f}, (vec3){-1000.f, -1000.f, -1000.f}, (vec3){1000.f, -1000.f, -1000.f}, (vec3){1000.f, 1000.f, -1000.f},
        // Left face
        (vec3){-1000.f, 1000.f, -1000.f}, (vec3){-1000.f, 1000.f, 1000.f}, (vec3){-1000.f, -1000.f, 1000.f}, (vec3){-1000.f, -1000.f, 1000.f}, (vec3){-1000.f, -1000.f, -1000.f}, (vec3){-1000.f, 1000.f, -1000.f},
        // Right face
        (vec3){1000.f, 1000.f, 1000.f}, (vec3){1000.f, 1000.f, -1000.f}, (vec3){1000.f, -1000.f, -1000.f}, (vec3){1000.f, -1000.f, -1000.f}, (vec3){1000.f, -1000.f, 1000.f}, (vec3){1000.f, 1000.f, 1000.f},
        // Top face
        
        (vec3){-1000.f, 1000.f, -1000.f}, (vec3){1000.f, 1000.f, -1000.f}, (vec3){1000.f, 1000.f, 1000.f}, (vec3){1000.f, 1000.f, 1000.f}, (vec3){-1000.f, 1000.f, 1000.f}, (vec3){-1000.f, 1000.f, -1000.f},
        
        // Bottom face
        (vec3){-1000.f, -1000.f, 1000.f}, (vec3){1000.f, -1000.f, 1000.f}, (vec3){1000.f, -1000.f, -1000.f}, (vec3){1000.f, -1000.f, -1000.f}, (vec3){-1000.f, -1000.f, -1000.f}, (vec3){-1000.f, -1000.f, 1000.f}
    };
struct Skybox1_t
{
    
    //LoadSetShaders(&shaderMain, shader03vert, shader03frag);

    Buff1 buff;
    ShProgram1 shaderMain;
    unsigned int TextureID;
    //createVBOBuff(&buffTemp);
};

typedef struct Skybox1_t Skybox1;

void PrepareShaderAndBuffer(Skybox1 *sk,const char* v,const char* f);
unsigned int loadTexture(Skybox1 *sk,char const *path);
void LoadTexturesSkybox(Skybox1 *sk);
void RenderSkybox(Skybox1 *sk,mat4 *view,mat4 *proj);
void ClearSkybox(Skybox1 *sk);

#endif