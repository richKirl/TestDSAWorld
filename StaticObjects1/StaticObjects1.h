#ifndef __STATICOBJECTS1_T__
#define __STATICOBJECTS1_T__

#include "../Shaders1/ShProgram1.h"
#include "../Buffs1/Buff1.h"
#include "../Math1/WTMath.h"
#include "../Transform1/Transform1.h"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
struct StaticObject1_t
{
    ShProgram1 shaderMain;
    Buff1 buffTemp;
    vec3 *ColorObj,*VertObj,*NormalsObj;
    const char* ModelPath;
    C_STRUCT aiLogStream stream;
    const C_STRUCT aiScene* scene;
    int sumInds;
    int sumt;
    float d;
    Transform1 transform;
    mat4 model;
};

typedef struct StaticObject1_t StaticObject1;

/* ---------------------------------------------------------------------------- */
// void SetPathForObj(StaticObject1 *Obj,const char* p);
void recursive_calculate(StaticObject1 *Obj,const C_STRUCT aiScene *sc, const C_STRUCT aiNode *nd);
void recursive_read(StaticObject1 *Obj,const C_STRUCT aiScene *sc, const C_STRUCT aiNode *nd);
void PrepareObject(StaticObject1 *Obj,const char *pModel,ShProgram1 *shaderMain);
void RenderObject(StaticObject1 *Obj,mat4 *view,mat4 *proj,int type);
void CloseObject(StaticObject1 *Obj);
void SetPosRotScale(StaticObject1 *Obj,vec3 p,float rotateDegree, vec3 rotateX, vec3 rotateY, vec3 rotateZ, vec3 scale);

#endif