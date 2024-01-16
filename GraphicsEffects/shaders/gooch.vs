#version 460 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTexCoords;
layout (location = 2) in vec3 inNormal;

out vec2 texCoords;
out vec3 normal;
out vec3 fragPos;

uniform mat4 mvp;
uniform mat4 model;

void main()
{
    gl_Position = mvp * vec4(inPos, 1.0);
    fragPos = vec3(model * vec4(inPos, 1.0));

    texCoords = inTexCoords;
    normal = normalize(mat3(model) * inNormal);
}
