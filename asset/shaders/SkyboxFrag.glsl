#version 460 core  

layout(location = 0) out vec4 outputColor;
smooth in vec3 TexCoords;
smooth in float visibility;
smooth in vec4 ioEyeSpacePosition;
uniform samplerCube skybox;
vec3 skyColor = vec3(0.1, 0.1, 0.4);
void main() {
    outputColor = texture(skybox, TexCoords);
    outputColor = mix(vec4(skyColor, .1), outputColor, abs(ioEyeSpacePosition.z / ioEyeSpacePosition.w));
}