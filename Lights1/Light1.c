#include "Light1.h"

void setLightAmbientAndDiffuse(Light1* light,
unsigned int ShaderProgram,
vec3 pEye,
vec3 dcolor, 
vec3 ddir, 
float dfac, 
bool dOn, 
vec3 acol, 
bool aOn)
{
    light->ambient.color=acol;
    light->ambient.isOn=aOn;

    light->diffuse.color=dcolor;
    light->diffuse.direction=ddir;
    light->diffuse.factor=dfac;
    light->diffuse.isOn=dOn;

    SetUniformVec3(light->ambient.color,ShaderProgram,      "ambientL.color");
    SetUniformBool(light->ambient.isOn,ShaderProgram,       "ambientL.isOn");

    SetUniformVec3(light->diffuse.color,ShaderProgram,      "diffuseL.color");
    SetUniformVec3(light->diffuse.direction,ShaderProgram,  "diffuseL.direction");
    SetUniformFloat(light->diffuse.factor,ShaderProgram,    "diffuseL.factor");
    SetUniformBool(light->diffuse.isOn,ShaderProgram,       "diffuseL.isOn");

    SetUniformFloat(32.0f,ShaderProgram,    "materialL.specularPower");
    SetUniformFloat(1.0f,ShaderProgram,    "materialL.specularIntensity");
    SetUniformBool(false,ShaderProgram,       "materialL.isEnabled");
}