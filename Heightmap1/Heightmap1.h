#ifndef __HEIGHTMAP1__
#define __HEIGHTMAP1__

#include "../Buffs1/Buff1.h"
#include "../Math1/WTMath.h"
#include "../Shaders1/ShProgram1.h"
#include "../Transform1/Transform1.h"
#include "../Math1/WTMath.h"
struct Heightmap1_t
{
		int rows;
		int columns;
		int numHills;
		int hillRadiusMin;
		int hillRadiusMax;
		float hillMinHeight;
		float hillMaxHeight;
    f32 **heighData;
    vec3 *ColorObj,*VertObj,*NormalsObj;
     int *Inds;
    ShProgram1 shaderMain;
    int sumInds;
     int SInds;
    int sumt;
    float d;
    Transform1 transform;
    mat4 model;
    Buff1 buffTemp;
};

typedef struct Heightmap1_t Heightmap1;

void initH(Heightmap1 *heightmap,int rows,int columns,int numHills, int hillRadiusMin, int hillRadiusMax, float hillMinHeight, float hillMaxHeight);
void setShader(Heightmap1 *heightmap,ShProgram1 *shader);
void RenderHeightMap(Heightmap1 *heightmap,mat4 *view,mat4 *proj,int type);
void SetPosRotScaleH(Heightmap1 *heightmap,vec3 p,float rotateDegree, vec3 rotateX, vec3 rotateY, vec3 rotateZ, vec3 scale);
void closeH(Heightmap1 *heightmap);
#endif
