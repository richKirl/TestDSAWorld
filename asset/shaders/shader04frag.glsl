#version 460 core

include asset/shaders/Ambient.glsl

include asset/shaders/Diffuse.glsl

include asset/shaders/Specular.glsl 

layout(location = 0) out vec4 outputColor;
smooth in vec3 ioVColor;
smooth in vec3 ioVertexTexNormal;
smooth in vec4 ioEyeSpacePosition;
smooth in float visibility;
smooth in vec4 posRelativeToCam;
uniform AmbientLight ambientL;
uniform DiffuseLight diffuseL;
uniform Material materialL;
uniform vec4 color;
uniform int type;
uniform samplerCube skybox;
vec3 skyColor = vec3(0.1, 0.1, 0.2);

void main() {
    vec3 normal = normalize(ioVertexTexNormal);

    vec3 lightColor = getAmbientLightColor(ambientL) + getDiffuseLightColor(diffuseL, normal) + getSpecularHighlightColor(posRelativeToCam.xyz, normal, ioEyeSpacePosition.xyz, materialL, diffuseL);
    if(type == 1) {
        outputColor = vec4(ioVColor, 1.0) * vec4(1, 1, 1, 1.0) * vec4(lightColor, 1.0);
        outputColor = mix(vec4(skyColor, 1.0), outputColor, visibility);
    }
    if(type == 2) {
        float ratio = 1.00 / 1.33;
        vec3 I = normalize(vec3(posRelativeToCam-ioEyeSpacePosition));
        vec3 R = reflect(I, normal);
        outputColor = mix(vec4(ioVColor, 0.3), vec4(texture(skybox, R).rgb, 0.2), 0.5) * vec4(lightColor, 1.0);  //*vec4(lightColor, 1.0)
        outputColor = mix(vec4(skyColor, 1.), outputColor, visibility);  //abs(ioEyeSpacePosition.z / ioEyeSpacePosition.w))
    }
}
