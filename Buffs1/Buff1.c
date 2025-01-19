#include "Buff1.h"

void createVBOBuff(Buff1 *buff)
{
    glCreateVertexArrays(1, &buff->VAO);
    glCreateBuffers(1, &buff->VBO);
    // glCreateBuffers(1, &VBO1);
    glCreateBuffers(1, &buff->EBO);
}

void loadData(Buff1 *buff, size_t sz, size_t vn, bool Color, bool TexCoord, bool Normals, vec3 *verts, vec3 *norms, vec2 *texCoords, vec3 *colors, bool withInds, int *Inds, int nn)
{
    if (Color == true && TexCoord == false && Normals == false&& withInds == false)
    {
        // 6*3
        buff->temp = malloc(sizeof(f32) * sz * vn);

        size_t ttt = 0;

        for (size_t i = 0; i < vn; i++)
        {
            buff->temp[ttt    ] = verts[i].x;
            buff->temp[ttt + 1] = verts[i].y;
            buff->temp[ttt + 2] = verts[i].z;
            buff->temp[ttt + 3] = colors[i].x;
            buff->temp[ttt + 4] = colors[i].y;
            buff->temp[ttt + 5] = colors[i].z;
            ttt += sz;
        }
        glNamedBufferData(buff->VBO, sizeof(f32) * sz * vn, &buff->temp[0], GL_STATIC_DRAW);

        glEnableVertexArrayAttrib(buff->VAO, 0);
        glVertexArrayAttribBinding(buff->VAO, 0, 0);
        glVertexArrayAttribFormat(buff->VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);

        glEnableVertexArrayAttrib(buff->VAO, 1);
        glVertexArrayAttribBinding(buff->VAO, 1, 0);
        glVertexArrayAttribFormat(buff->VAO, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32));

        glVertexArrayVertexBuffer(buff->VAO, 0, buff->VBO, 0, 6 * sizeof(f32));
    }
    if (Color == true && TexCoord == false && Normals == true&& withInds == false)
    {
        // 6*3
        buff->temp = malloc(sizeof(f32) * sz * vn);

        size_t ttt = 0;

        for (size_t i = 0; i < vn; i++)
        {
            buff->temp[ttt    ] = verts[i].x;
            buff->temp[ttt + 1] = verts[i].y;
            buff->temp[ttt + 2] = verts[i].z;
            buff->temp[ttt + 3] = colors[i].x;
            buff->temp[ttt + 4] = colors[i].y;
            buff->temp[ttt + 5] = colors[i].z;
            buff->temp[ttt + 6] = norms[i].x;
            buff->temp[ttt + 7] = norms[i].y;
            buff->temp[ttt + 8] = norms[i].z;
            ttt += sz;
        }
        glNamedBufferData(buff->VBO, sizeof(f32) * sz * vn, &buff->temp[0], GL_STATIC_DRAW);
        

        glEnableVertexArrayAttrib(buff->VAO, 0);
        glVertexArrayAttribBinding(buff->VAO, 0, 0);
        glVertexArrayAttribFormat(buff->VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);

        glEnableVertexArrayAttrib(buff->VAO, 1);
        glVertexArrayAttribBinding(buff->VAO, 1, 0);
        glVertexArrayAttribFormat(buff->VAO, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32));

        glEnableVertexArrayAttrib(buff->VAO, 2);
        glVertexArrayAttribBinding(buff->VAO, 2, 0);
        glVertexArrayAttribFormat(buff->VAO, 2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(f32));
        glVertexArrayVertexBuffer(buff->VAO, 0, buff->VBO, 0, 9 * sizeof(f32));
    }
    if (Color == true && TexCoord == false && Normals == true&& withInds == true)
    {
        // 6*3
        printf("3\n");
        buff->temp = malloc(sizeof(f32) * sz * vn);

        size_t ttt = 0;

        for (size_t i = 0; i < vn; i++)
        {
            buff->temp[ttt    ] = verts[i].x;
            buff->temp[ttt + 1] = verts[i].y;
            buff->temp[ttt + 2] = verts[i].z;
            buff->temp[ttt + 3] = colors[i].x;
            buff->temp[ttt + 4] = colors[i].y;
            buff->temp[ttt + 5] = colors[i].z;
            buff->temp[ttt + 6] = norms[i].x;
            buff->temp[ttt + 7] = norms[i].y;
            buff->temp[ttt + 8] = norms[i].z;
            ttt += sz;
        }
        glNamedBufferData(buff->VBO, sizeof(f32) * sz * vn, &buff->temp[0], GL_STATIC_DRAW);
        glNamedBufferData(buff->EBO, nn * sizeof(unsigned int),&Inds[0], GL_STATIC_DRAW);

        glEnableVertexArrayAttrib(buff->VAO, 0);
        glVertexArrayAttribBinding(buff->VAO, 0, 0);
        glVertexArrayAttribFormat(buff->VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);

        glEnableVertexArrayAttrib(buff->VAO, 1);
        glVertexArrayAttribBinding(buff->VAO, 1, 0);
        glVertexArrayAttribFormat(buff->VAO, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32));

        glEnableVertexArrayAttrib(buff->VAO, 2);
        glVertexArrayAttribBinding(buff->VAO, 2, 0);
        glVertexArrayAttribFormat(buff->VAO, 2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(f32));
        
        glVertexArrayVertexBuffer(buff->VAO, 0, buff->VBO, 0, 9 * sizeof(f32));
        glVertexArrayElementBuffer(buff->VAO, buff->EBO);
    }
    if (Color == false && TexCoord == false && Normals == false&& withInds == false)
    {
        // 6*3
        buff->temp = malloc(sizeof(f32) * sz * vn);

        size_t ttt = 0;

        for (size_t i = 0; i < vn; i++)
        {
            buff->temp[ttt    ] = verts[i].x;
            buff->temp[ttt + 1] = verts[i].y;
            buff->temp[ttt + 2] = verts[i].z;
            // buff->temp[ttt + 3] = colors[i].x;
            // buff->temp[ttt + 4] = colors[i].y;
            // buff->temp[ttt + 5] = colors[i].z;
            // buff->temp[ttt + 6] = norms[i].x;
            // buff->temp[ttt + 7] = norms[i].y;
            // buff->temp[ttt + 8] = norms[i].z;
            ttt += sz;
        }
        glNamedBufferData(buff->VBO, sizeof(f32) * sz * vn, &buff->temp[0], GL_STATIC_DRAW);

        glEnableVertexArrayAttrib(buff->VAO, 0);
        glVertexArrayAttribBinding(buff->VAO, 0, 0);
        glVertexArrayAttribFormat(buff->VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);

        // glEnableVertexArrayAttrib(buff->VAO, 1);
        // glVertexArrayAttribBinding(buff->VAO, 1, 0);
        // glVertexArrayAttribFormat(buff->VAO, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32));

        // glEnableVertexArrayAttrib(buff->VAO, 2);
        // glVertexArrayAttribBinding(buff->VAO, 2, 0);
        // glVertexArrayAttribFormat(buff->VAO, 2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(f32));
        glVertexArrayVertexBuffer(buff->VAO, 0, buff->VBO, 0, 3 * sizeof(f32));
    }
}

void deleteVBOBuff(Buff1 *buff)
{
    free(buff->temp);
    glDeleteVertexArrays(1, &buff->VAO);
    glDeleteBuffers(1, &buff->VBO);
    glDeleteBuffers(1, &buff->EBO);
}

void SetUniformMat4(mat4 *m,unsigned int ShaderProgram,const char* name)
{
    GLint matrixId1 = glGetUniformLocation(ShaderProgram,name);
    glUniformMatrix4fv(matrixId1, 1, GL_FALSE, &m->v[0]);
}
void SetUniformMat3(mat3 *m,unsigned int ShaderProgram,const char* name)
{
    GLint matrixId1 = glGetUniformLocation(ShaderProgram,name);
    glUniformMatrix3fv(matrixId1, 1, GL_FALSE, &m->v[0]);
}
void SetUniformInt(int n,unsigned int ShaderProgram,const char* name)
{
    GLint matrixId1 = glGetUniformLocation(ShaderProgram,name);
    glUniform1i(matrixId1, n);
}

void SetUniformFloat(float n, unsigned int ShaderProgram, const char *name)
{
    GLint matrixId1 = glGetUniformLocation(ShaderProgram,name);
    glUniform1f(matrixId1, n);
}

void SetUniformBool(bool n, unsigned int ShaderProgram, const char *name)
{
    GLint matrixId1 = glGetUniformLocation(ShaderProgram,name);
    glUniform1i(matrixId1, n);
}

void SetUniformVec3(vec3 n, unsigned int ShaderProgram, const char *name)
{
    GLint matrixId1 = glGetUniformLocation(ShaderProgram,name);
    glUniform3fv(matrixId1,1, (GLfloat*)&n);
}

void SetUniformVec4(vec4 n, unsigned int ShaderProgram, const char *name)
{
    GLint matrixId1 = glGetUniformLocation(ShaderProgram,name);
    glUniform3fv(matrixId1,1, (GLfloat*)&n);
}