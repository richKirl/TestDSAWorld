#include "Water1.h"

void PreparePlane(Water1 *water,ShProgram1 *shaderMain, float xw, float yw, int resolution)
{
    createVBOBuff(&water->buffTemp);
    water->shaderMain=shaderMain[0];
    //24*24*6
    water->VertObj = malloc(sizeof(vec3)*6*resolution*resolution);
    water->ColorObj = malloc(sizeof(vec3)*6*resolution*resolution);
    water->NormalsObj = malloc(sizeof(vec3)*6*resolution*resolution);
    unsigned int VCount=0;
    for (float i = 0; i < resolution; i++)//z
    {
        for (float j = 0; j < resolution; j++)//x
        {
            water->VertObj[VCount]  =(vec3){(float)j,(float)0,(float)i+1.f};
            water->VertObj[VCount+1]=(vec3){(float)j+1.f,(float)0,(float)i+1.f};
            water->VertObj[VCount+2]=(vec3){(float)j+1.f,(float)0,(float)i};
            water->VertObj[VCount+3]=(vec3){(float)j+1.f,(float)0,(float)i};
            water->VertObj[VCount+4]=(vec3){(float)j,(float)0,(float)i};
            water->VertObj[VCount+5]=(vec3){(float)j,(float)0,(float)i+1.f};
            water->ColorObj[VCount]  =(vec3){0.1,0.1,0.3};
            water->ColorObj[VCount+1]=(vec3){0.1,0.1,0.3};
            water->ColorObj[VCount+2]=(vec3){0.1,0.1,0.3};
            water->ColorObj[VCount+3]=(vec3){0.1,0.1,0.3};
            water->ColorObj[VCount+4]=(vec3){0.1,0.1,0.3};
            water->ColorObj[VCount+5]=(vec3){0.1,0.1,0.3};
            water->NormalsObj[VCount]  =(vec3){0,-1,0};
            water->NormalsObj[VCount+1]=(vec3){0,-1,0};
            water->NormalsObj[VCount+2]=(vec3){0,-1,0};
            water->NormalsObj[VCount+3]=(vec3){0,-1,0};
            water->NormalsObj[VCount+4]=(vec3){0,-1,0};
            water->NormalsObj[VCount+5]=(vec3){0,-1,0};
            VCount+=6;
        }
        
    }
    water->sumInds=6*resolution*resolution;
    loadData(&water->buffTemp, 9, water->sumInds, true, false, true, water->VertObj, water->NormalsObj, NULL, water->ColorObj);
    free(water->VertObj);
    free(water->ColorObj);
    free(water->NormalsObj);
    
}

void RenderObjectW(Water1 *water,mat4 *view,mat4 *proj,int type,float dtime)
{
    glEnable(GL_BLEND);
    // glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
        
        
        useSh(&water->shaderMain);
        SetUniformFloat(dtime,water->shaderMain.shaderProgram,"time");
        SetUniformInt(type,water->shaderMain.shaderProgram,"type");
        SetUniformMat4(proj,water->shaderMain.shaderProgram,"proj");
        SetUniformMat4(view,water->shaderMain.shaderProgram,"view");
        SetUniformMat4(&water->model,water->shaderMain.shaderProgram,"model");
        mat3 t= Transposedm3(Inversem4((mat3){
            water->model.v[0], water->model.v[1], water->model.v[2],
            water->model.v[4], water->model.v[5], water->model.v[6],
            water->model.v[8], water->model.v[9], water->model.v[10]}));
        SetUniformMat3(&t,water->shaderMain.shaderProgram,"norm");
        glBindVertexArray(water->buffTemp.VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, water->TextureID);
        glDrawArrays(GL_TRIANGLES, 0, water->sumInds);
        
        glBindVertexArray(0);
    glDisable(GL_BLEND);
}

void CloseObjectW(Water1 *water)
{
    deleteVBOBuff(&water->buffTemp);
    delSh(&water->shaderMain);
}

void SetPosRotScaleW(Water1 *water, vec3 p, float rotateDegree, vec3 rotateX, vec3 rotateY, vec3 rotateZ, vec3 scale)
{
    SetPRS(&water->transform,p,rotateDegree,rotateX,rotateY,rotateZ,scale);
    water->model=GetModel(&water->transform);
}

void SetTextureForW(Water1 *water,unsigned int *Texture)
{
    water->TextureID=Texture[0];
    SetUniformInt(0,water->shaderMain.shaderProgram,"skybox");
}
