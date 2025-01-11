#include "ShProgram1.h"
#include <stdio.h>
void LoadVertexShader(ShProgram1 *sh, const char *shader)
{
    
    CalculateMainFiles(&sh->sh,pathUtility,sInclude,shader,&sh->sh.Vsz,&sh->sh.nlinesV);
    sh->sh.FileVertexShaderMain    = malloc(sizeof (char *)*sh->sh.nlinesV);
    openMainFiles(&sh->sh,pathUtility,sInclude,shader,sh->sh.FileVertexShaderMain);

    sh->shaderV = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sh->shaderV, sh->sh.nlinesV, sh->sh.FileVertexShaderMain, NULL);
    glCompileShader(sh->shaderV);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(sh->shaderV, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(sh->shaderV, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s\n", infoLog);
    }
    
}

void LoadFragmentShader(ShProgram1 *sh, const char *shader)
{
    CalculateMainFiles(&sh->sh,pathUtility,sInclude,shader,&sh->sh.Fsz,&sh->sh.nlinesF);
    sh->sh.FileFragmentShaderMain    = malloc(sizeof (char *)*sh->sh.nlinesF);
    openMainFiles(&sh->sh,pathUtility,sInclude,shader,sh->sh.FileFragmentShaderMain);
    sh->shaderF = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sh->shaderF, sh->sh.nlinesF, sh->sh.FileFragmentShaderMain, NULL);
    glCompileShader(sh->shaderF);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(sh->shaderF, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(sh->shaderF, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n %s\n", infoLog);
    }
}

void LoadGeometryShader(ShProgram1 *sh, const char *shader)
{
}


void LoadSetShaders(ShProgram1 *sh, const char *shaderV, const char *shaderF)
{
    initMainShader(&sh->sh);
    LoadVertexShader(sh, shaderV);
    LoadFragmentShader(sh, shaderF);

    sh->shaderProgram = glCreateProgram();
    glAttachShader(sh->shaderProgram, sh->shaderV);
    glAttachShader(sh->shaderProgram, sh->shaderF);
    glLinkProgram(sh->shaderProgram);
    // check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(sh->shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(sh->shaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n %s\n", infoLog);
    }
    glDeleteShader(sh->shaderV);
    glDeleteShader(sh->shaderF);
    FreeMemoryForShader(&sh->sh,sh->sh.FileVertexShaderMain,sh->sh.nlinesV);
    FreeMemoryForShader(&sh->sh,sh->sh.FileFragmentShaderMain,sh->sh.nlinesF);
}

void useSh(ShProgram1 *sh)
{
    glUseProgram(sh->shaderProgram);
}
void resetSh()
{
    glUseProgram(0);
}
void delSh(ShProgram1 *sh)
{
    glDeleteProgram(sh->shaderProgram);
}
