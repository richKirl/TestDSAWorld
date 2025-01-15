#version 460 core

layout(location = 0) out vec4 oCol;

uniform vec4 col;

void main()
{
    oCol = col;
}