#version 330 core

uniform mat4 mvp;

in vec3 pos;
in vec3 normal;

out vec3 color;

void main()
{
    gl_Position = mvp * vec4(pos, 1.0);
    color = (normal + vec3(1.0, 1.0, 1.0)) / 2.0;
}
