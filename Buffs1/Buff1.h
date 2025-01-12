#ifndef __BUFF1_T__
#define __BUFF1_T__

#include <GL/glew.h>
#include <stdbool.h>
#include "../Math1/WTMath.h"
struct Buff1_t
{
    GLuint VAO, VBO, EBO;
    f32 *temp;
};

typedef struct Buff1_t Buff1;

void createVBOBuff(Buff1 *buff);
void loadData(Buff1 *buff, size_t sz, size_t vn, bool Color, bool TexCoord, bool Normals, vec3 *verts, vec3 *norms, vec2 *texCoords, vec3 *colors);
void deleteVBOBuff(Buff1 *buff);
void SetUniformMat4(mat4 *m,unsigned int ShaderProgram,const char* name);
void SetUniformMat3(mat3 *m,unsigned int ShaderProgram,const char* name);
void SetUniformInt(int n,unsigned int ShaderProgram,const char* name);
void SetUniformFloat(float n,unsigned int ShaderProgram,const char* name);
void SetUniformBool(bool n,unsigned int ShaderProgram,const char* name);
void SetUniformVec3(vec3 n,unsigned int ShaderProgram,const char* name);
void SetUniformVec4(vec4 n, unsigned int ShaderProgram, const char *name);
// void RenderObject(Buff1 *buff);
#endif