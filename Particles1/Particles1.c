#include "Particles1.h"

void InitParticles(Particles* particles)
{
    createVBOBuff(&particles->buff);
    LoadSetShaders(&particles->shader, "asset/shaders/ParticleShaderV.glsl", "asset/shaders/ParticleShaderF.glsl");
    
    // particles->particle = malloc(sizeof(particles->particle) * 1);
    srand(time(NULL));
    // for (size_t i = 0; i < 256; i++)
    // {
    // particles->particle[0].life = rand() % 5;
    // particles->particle[0].vel = rand() % 1;
    // particles->particle[0].pos = (vec3){rand() % 5, rand() % 5, rand() % 5};
    int sc = rand() % 5;
    // particles->particle[0].scale = (vec3){sc, sc, sc};
    /* code */
    // }
    particles->sumt = 0;
    particles->sumInds = 6;
    particles->VertObj=malloc(sizeof(vec3) * 6);



    loadData(&particles->buff, 3, particles->sumInds, false, false, false, &particleVerts[0], NULL, NULL, NULL);
    free(particles->VertObj);
}

void RenderParticles(Particles *particles,mat4 *P,mat4 *O)
{
    // particles->particle[0].life-=0.1f;
    // particles->modelV;
    // particles->modelV=identitym4(particles->modelV);
    // particles->modelV=Scalem4v3(particles->modelV,(vec3){100,100,100});
    
    particles->modelV=GetModel(&particles->transform);
    // particles->modelV=Mulm4(P[0],particles->modelV);
    useSh(&particles->shader);
    glBindVertexArray(particles->buff.VAO);
    
    SetUniformMat4(&particles->modelV,particles->shader.shaderProgram,"modelView");
    SetUniformMat4(&O[0],particles->shader.shaderProgram,"proj");
    glDrawArrays(GL_TRIANGLES,0,6);
    glBindVertexArray(0);
    // resetSh();
}

void closeParticles(Particles *particles)
{
    // free(particles->VertObj);
    // free(particles->particle);
    deleteVBOBuff(&particles->buff);
    delSh(&particles->shader);
}

void SetPosRotScaleP(Particles *particlesj, vec3 p, float rotateDegree, vec3 rotateX, vec3 rotateY, vec3 rotateZ, vec3 scale)
{
    SetPRS(&particlesj->transform,p,rotateDegree,rotateX,rotateY,rotateZ,scale);
    
}
