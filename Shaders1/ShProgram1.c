#include "ShProgram1.h"
#include <stdio.h>
void LoadVertexShader(ShProgram1 *sh, const char *shader)
{
    sh->shaderV = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sh->shaderV, 1, &shader, NULL);
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
    sh->shaderF = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sh->shaderF, 1, &shader, NULL);
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
