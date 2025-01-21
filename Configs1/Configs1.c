#include "Configs1.h"

// test
// skyboxRight
// skyboxLeft
// skyboxTop
// skyboxBottom
// skyboxBack
// skyboxFront
// pathSkyboxVert
// pathSkyboxFrag
// pathMainVert
// pathMainFrag
// pathNormalsV
// pathNormalsF
// pathNormalsG
// particlesShadersV
// particlesShadersF
// pathUtilitytNoise
// pathUtilitytAmbient
// pathUtilitytDiffuse
// pathUtilitytSpecular
// separateInclude
// pathPickingVert
// pathPickingFrag
// pathSuzanneNotOptimaze
// pathSuzanneOptimaze
// #define lua_pushglobaltable(L) lua_pushvalue(L,LUA_GLOBALSINDEX)
void luaAccess(lua_State *L) // call this function with the table on the top of the stack
{
    // Push another reference to the table on top of the stack (so we know
    // where it is, and this function can work for negative, positive and
    // pseudo indices
    lua_getglobal(L, "arg");
    lua_pushvalue(L, -1);
    // stack now contains: -1 => table
    lua_pushnil(L);
    // stack now contains: -1 => nil; -2 => table
    while (lua_next(L, -2))
    {
        // stack now contains: -1 => value; -2 => key; -3 => table
        // copy the key so that lua_tostring does not modify the original
        lua_pushvalue(L, -2);
        // stack now contains: -1 => key; -2 => value; -3 => key; -4 => table
        const char *key = lua_tostring(L, -1);
        const char *value = lua_tostring(L, -2);
        printf("%s => %s\n", key, value);
        // pop value + copy of key, leaving original key
        lua_pop(L, 2);
        // stack now contains: -1 => key; -2 => table
    }
    // stack now contains: -1 => table (when lua_next returns 0 it pops the key
    // but does not push anything.)
    // Pop table
    lua_pop(L, 1);
    // Stack is now the same as it was on entry to this function
}

void runLua()
{
    printf("RunTest \n");
    int status;
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    status = luaL_dofile(L, "configCore.lua");
    const char *z;
    if (status)
    {
        fprintf(stderr, "Error: %s\n", lua_tostring(L, -1));
        return;
    }
    // lua_rawgeti(L,-1,0);
    // lua_pushnil(L);
    // while (lua_next(L,-2) != 0) {
    //     puts(lua_tostring(L,-2));
    //     lua_pop(L,1);
    // }
    // lua_pop(L,1);
    luaAccess(L);
    lua_close(L);
    printf("EndTest \n");
}

void ReadInitConf(Configs1 *c)
{
    runLua();
}

void EraseMemoryConf(Configs1 *c)
{
    c->test = NULL;

    c->skyboxRight = NULL;
    c->skyboxLeft = NULL;

    c->skyboxTop = NULL;
    c->skyboxBottom = NULL;
    c->skyboxBack = NULL;
    c->skyboxFront = NULL;

    c->pathSkyboxVert = NULL;
    c->pathSkyboxFrag = NULL;

    c->pathMainVert = NULL;
    c->pathMainFrag = NULL;

    c->pathNormalsV = NULL;
    c->pathNormalsF = NULL;
    c->pathNormalsG = NULL;

    c->particlesShadersV = NULL;
    c->particlesShadersF = NULL;

    c->pathUtilitytNoise = NULL;
    c->pathUtilitytAmbient = NULL;
    c->pathUtilitytDiffuse = NULL;
    c->pathUtilitytSpecular = NULL;
    c->separateInclude = NULL;

    c->pathPickingVert = NULL;
    c->pathPickingFrag = NULL;

    c->pathSuzanneNotOptimaze = NULL;
    c->pathSuzanneOptimaze = NULL;
}
