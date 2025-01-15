#ifndef __PICKING1_T__
#define __PICKING1_T__

#include <GL/glew.h>
#include <stdbool.h>
#include "../Math1/WTMath.h"
#include "../Shaders1/ShProgram1.h"

static const char *pathPickingVert = "asset/shaders/PickingVert.glsl";
static const char *pathPickingFrag = "asset/shaders/PickingFrag.glsl";

struct Picking1_t
{
    ShProgram1 shader;
    GLuint FBO,RBO,cRBO,dRBO;
    f32 *temp;
};

typedef struct Picking1_t Picking1;

void initFBORBO(Picking1 *p,int w,int h);
void bindAsReadBindAsDrawBlit(Picking1 *p,int w,int h);
void bindFBO(Picking1 *p);
void bbrd(Picking1 *p);
void delbrd(Picking1 *p);
#endif