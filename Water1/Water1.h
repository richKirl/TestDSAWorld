#ifndef __WATER1_T__
#define __WATER1_T__
#include "../Shaders1/ShProgram1.h"
#include "../Buffs1/Buff1.h"
#include "../Math1/WTMath.h"
#include "../Transform1/Transform1.h"
struct Water1_t
{
    ShProgram1 shaderMain;
    Buff1 buffTemp;
    vec3 *ColorObj,*VertObj,*NormalsObj;
    float xx;
    float yy;
    int resolution;
    Transform1 transform;
    int sumInds;
    unsigned int TextureID;
    mat4 model;
};

typedef struct Water1_t Water1;
void PreparePlane(Water1 *water,ShProgram1 *shaderMain, float xw, float yw, int resolution);
void RenderObjectW(Water1 *water,mat4 *view,mat4 *proj,int type,float dtime);
void CloseObjectW(Water1 *water);
void SetPosRotScaleW(Water1 *water,vec3 p,float rotateDegree, vec3 rotateX, vec3 rotateY, vec3 rotateZ, vec3 scale);
void SetTextureForW(Water1 *water,unsigned int *Texture);
#endif