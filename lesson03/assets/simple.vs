#version 330 core

uniform mat4 mvp;

in vec3 pos;
in vec3 col;

out vec3 color;

void main()
{
    gl_Position = mvp * vec4(pos, 1.0);
    color = col;
}
