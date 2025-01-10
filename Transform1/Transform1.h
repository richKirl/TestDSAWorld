#ifndef __TRANSFORM1_T__
#define __TRANSFORM1_T__

#include "../Math1/WTMath.h"
struct Transform1_t
{
    mat4 model;
    mat4 Translate;
    mat4 Scale;
    mat4 Rotate;
    mat4 RotateX;
    mat4 RotateY;
    mat4 RotateZ;
    vec3 pos;
    vec3 dir;
    vec3 sc;
    vec3 rot;
};

typedef struct Transform1_t Transform1;
//SET POSITION ROTATE SCALE
void SetPRS(Transform1 *transform,vec3 p,float rotateDegree, vec3 rotateX, vec3 rotateY, vec3 rotateZ, vec3 scale);
mat4 GetModel(Transform1 *transform);
mat4 RotateQT(Transform1 *transform,mat4 m,float angle, vec3 ax);
#endif