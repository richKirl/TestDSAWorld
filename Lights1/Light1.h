#ifndef __LIGHT1_T__
#define __LIGHT1_T__

#include "../Math1/WTMath.h"
#include <stdbool.h>
#include "../Buffs1/Buff1.h"
struct AmbientLight_t
{
	vec3 color;
	bool isOn;
};
typedef struct AmbientLight_t AmbientLight;
struct DiffuseLight_t
{
	vec3 color;
	vec3 direction;
	float factor;
	bool isOn;
};
typedef struct DiffuseLight_t DiffuseLight;
struct Light1_t
{
    AmbientLight ambient;
    DiffuseLight diffuse;
};

typedef struct Light1_t Light1;
void setLightAmbientAndDiffuse(Light1* light,
unsigned int ShaderProgram,
vec3 pEye,
vec3 dcolor, 
vec3 ddir, 
float dfac, 
bool dOn, 
vec3 acol, 
bool aOn);


#endif