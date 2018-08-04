#version 330 core

in vec3 color;
out vec4 outcol;

void main()
{
    outcol = vec4(color, 1.0);
}
