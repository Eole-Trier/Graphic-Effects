#version 460 core
layout (location = 0) out vec4 FragColor;

uniform vec4 lightColor;

void main()
{           
    FragColor = vec4(lightColor.rgb, 1.0);
}