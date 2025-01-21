#ifndef __CONFIGS1_T__
#define __CONFIGS1_T__
#include <stdlib.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
struct Configs1_t
{
    const char *test;

    const char *skyboxRight;
    const char *skyboxLeft;

    const char *skyboxTop;
    const char *skyboxBottom;
    const char *skyboxBack;
    const char *skyboxFront;

    const char *pathSkyboxVert;
    const char *pathSkyboxFrag;

    const char *pathMainVert;
    const char *pathMainFrag;

    const char *pathNormalsV;
    const char *pathNormalsF;
    const char *pathNormalsG;

    const char *particlesShadersV;
    const char *particlesShadersF;

    const char *pathUtilitytNoise;
    const char *pathUtilitytAmbient;
    const char *pathUtilitytDiffuse;
    const char *pathUtilitytSpecular;
    const char *separateInclude;

    const char *pathPickingVert;
    const char *pathPickingFrag;

    const char *pathSuzanneNotOptimaze;
    const char *pathSuzanneOptimaze;
};

typedef struct Configs1_t Configs1;
void ReadInitConf(Configs1 *c);
void EraseMemoryConf(Configs1 *c);

#endif