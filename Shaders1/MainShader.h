#ifndef __MAINSHADER1_T__
#define __MAINSHADER1_T__
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static const char *pathMainVert = "asset/shaders/shader04vert.glsl";
static const char *pathMainFrag = "asset/shaders/shader04frag.glsl";
static const char *pathSkyboxVert = "asset/shaders/SkyboxVert.glsl";
static const char *pathSkyboxFrag = "asset/shaders/SkyboxFrag.glsl";

static const char *pathUtility[] = {
    "asset/shaders/tnoise.glsl",
    "asset/shaders/Ambient.glsl",
    "asset/shaders/Diffuse.glsl",
    "asset/shaders/Specular.glsl"};
static const char *sInclude = "include ";
//table data for shader;
struct MainShader_t
{
    long Vsz;
    long Fsz;
    long nlinesV;
    long nlinesF;
    const char** FileVertexShaderMain;
    const char** FileFragmentShaderMain;
    //printToFileforDebug
};

typedef struct MainShader_t MainShader;

void initMainShader(MainShader *mShader);
void testOpenFile(MainShader *mShader,char *p,const char **FileMain,int *countL1);
void openMainFiles(MainShader *mShader,const char **pathUtility,const char *sInclude,const char *pathMainVert,const char **FileMain);
void calculateOpenFile(MainShader *mShader,char *p,long *sz,long *nlines);
void CalculateMainFiles(MainShader *mShader,const char **pathUtility,const char *sInclude,const char *pathMainVert,long *sz,long *nlines);
void FileWrite(MainShader *mShader,const char* p,const char** fileW,long sz);
void PrintLines(MainShader *mShader,const char** linesW,long sz);
void FreeMemoryForShader(MainShader *mShader,const char **FileVertexShaderMain,long nlinesV);

#endif