#version 460 core

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

layout(location = 0) in vec3 vPos;

void main()
{
    mat4 mvpMatrix = proj * view * model;
    gl_Position = mvpMatrix * vec4(vPos, 1.0);
}