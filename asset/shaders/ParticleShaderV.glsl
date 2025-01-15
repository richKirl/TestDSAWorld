#version 460 core

layout(location = 0) in vec3 aPos;

uniform mat4 modelView;

uniform mat4 proj;

void main()
{
    gl_Position = proj * modelView * vec4(aPos.xy,0,1.0);
}


