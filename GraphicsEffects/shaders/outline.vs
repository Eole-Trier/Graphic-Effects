#version 460 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTexCoords;
layout (location = 2) in vec3 inNormal;

uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vec4(inPos, 1.0);
}
