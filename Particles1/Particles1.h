#ifndef __PARTICLES1_T__
#define __PARTICLES1_T__
#include "../Math1/WTMath.h"
#include "../Buffs1/Buff1.h"
#include "../Shaders1/ShProgram1.h"
#include "../Transform1/Transform1.h"
#include <time.h>
static vec3 particleVerts[6] =
{
    // Front face
    (vec3){-1.5f, 1.5f, 1.5f}, (vec3){1.5f, 1.5f, 1.5f}, (vec3){1.5f, -1.5f, 1.5f},
    (vec3){1.5f, -1.5f, 1.5f}, (vec3){-1.5f, -1.5f, 1.5f}, (vec3){-1.5f, 1.5f, 1.5f}
};
static const char *pathParticleVert = "asset/shaders/ParticleShaderV.glsl";
static const char *pathParticleFrag = "asset/shaders/ParticleShaderF.glsl";

struct Particle_t
{
    float vel;
    float life;
    vec3 pos;
    vec3 scale;
};
typedef struct Particle_t Particle;

struct Particles_t
{
    Buff1 buff;
    ShProgram1 shader;
    vec3 *VertObj;
    Transform1 transform;
    mat4 modelV;
    vec3 pos;
    int sumInds;
    int sumt;
};

typedef struct Particles_t Particles;

void InitParticles(Particles* particles);
void RenderParticles(Particles *particles,mat4 *P,mat4 *O);
void closeParticles(Particles* particles);
void SetPosRotScaleP(Particles* particlesj,vec3 p,float rotateDegree, vec3 rotateX, vec3 rotateY, vec3 rotateZ, vec3 scale);
#endif