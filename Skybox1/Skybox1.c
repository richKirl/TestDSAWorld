#include "Skybox1.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stbimage/stb_image.h"
#define GL_CLAMP_TO_EDGE                  0x812F
void PrepareShaderAndBuffer(Skybox1 *sk,const char* v,const char* f)
{
    
    LoadSetShaders(&sk->shaderMain, v, f);
    createVBOBuff(&sk->buff);
    glNamedBufferData(sk->buff.VBO, sizeof(f32) * 3 * 36, &SkyboxVerts[0], GL_STATIC_DRAW);

    glEnableVertexArrayAttrib(sk->buff.VAO, 0);
    glVertexArrayAttribBinding(sk->buff.VAO, 0, 0);
    glVertexArrayAttribFormat(sk->buff.VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayVertexBuffer(sk->buff.VAO, 0, sk->buff.VBO, 0, 3 * sizeof(f32));
}
unsigned int loadTexture(Skybox1 *sk,char const *path)
{
    unsigned int textureID;
    // glGenTextures(1, &textureID);
    glCreateTextures(GL_TEXTURE_CUBE_MAP,1,&textureID);

    glTextureStorage2D(textureID, 1, GL_RGBA8,1024,1024);
    int width, height, nrComponents;

    const char *paths[]={
        "asset/skybox/ttextures/right.png",
        "asset/skybox/ttextures/left.png",
        
        "asset/skybox/ttextures/top.png",
        "asset/skybox/ttextures/bottom.png",
        "asset/skybox/ttextures/back.png",
        "asset/skybox/ttextures/front.png"
        
    };
    // glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for (unsigned int i = 0; i < 6; i++)
    {
        if(i==2){
            // stbi_set_flip_vertically_on_load(true);
        }
        if(i==3)stbi_set_flip_vertically_on_load(false);
        unsigned char *data = stbi_load(paths[i], &width, &height, &nrComponents, 0);
        if (data)
        {
            glTextureSubImage3D(textureID, 0, 0, 0, i, width, height, 1, GL_RGB, GL_UNSIGNED_BYTE, data);

            stbi_image_free(data);
        }
        else
        {
            printf("Texture failed to load at path: %s\n", path);
            stbi_image_free(data);
        }
    }
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glTextureParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    SetUniformInt(0,sk->shaderMain.shaderProgram,"skybox");
    return textureID;
}
void LoadTexturesSkybox(Skybox1 *sk)
{
    sk->TextureID=loadTexture(sk,NULL);
}

void RenderSkybox(Skybox1 *sk,mat4 *view,mat4 *proj)
{
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_FALSE);
    useSh(&sk->shaderMain);

    SetUniformMat4(&(mat4){
        view->v[0],view->v[1],view->v[2],   0,
        view->v[4],view->v[5],view->v[6],   0,
        view->v[8],view->v[9],view->v[10],  0,
        0,          0,          0,          1
    },sk->shaderMain.shaderProgram,"view");
    SetUniformMat4(proj,sk->shaderMain.shaderProgram,"proj");
    glBindVertexArray(sk->buff.VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, sk->TextureID);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // glBindVertexArray(0);
    // useSh(0);
    // resetSh();
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
}

void ClearSkybox(Skybox1 *sk)
{
    glDeleteVertexArrays(1, &sk->buff.VAO);
    glDeleteBuffers(1, &sk->buff.VBO);
    glDeleteBuffers(1, &sk->buff.EBO);
    delSh(&sk->shaderMain);
}
