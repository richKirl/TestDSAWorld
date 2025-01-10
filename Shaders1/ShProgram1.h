#ifndef __SHPROGRAM1_T__
#define __SHPROGRAM1_T__
#include <GL/glew.h>
struct ShProgram1_t
{
    unsigned int shaderProgram;
    GLuint shaderF;
    GLuint shaderV;
};

typedef struct ShProgram1_t ShProgram1;

void LoadVertexShader(ShProgram1 *sh, const char *shader);
void LoadFragmentShader(ShProgram1 *sh, const char *shader);
void LoadGeometryShader(ShProgram1 *sh, const char *shader);
void LoadSetShaders(ShProgram1 *sh, const char *shaderV, const char *shaderF);
void useSh(ShProgram1 *sh);
void resetSh();
void delSh(ShProgram1 *sh);
#endif