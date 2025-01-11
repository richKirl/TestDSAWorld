#version 460 core  
layout(location = 0) in vec3 vertexPosition;

smooth out vec3 TexCoords;
smooth out float visibility;
smooth out vec4 ioEyeSpacePosition;
uniform mat4 proj;
uniform mat4 view;

float density = 0.036;
float gradient = 1.5;
void main() {
     TexCoords = vertexPosition;
     mat4 mvpMatrix = proj * view;
     vec4 pos = mvpMatrix * vec4(vertexPosition, 1.0);
     float distance = length(pos.xyz);
     visibility = exp(-pow((distance * density), gradient));
     visibility = clamp(visibility, 0.0, 1.);
     ioEyeSpacePosition = pos.xyww;
     gl_Position = pos.xyww;
}
