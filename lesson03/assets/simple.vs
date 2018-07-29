#version 330 core

uniform mat4 mvp;

in vec3 col;
in vec2 pos;

out vec3 color;

void main()
{
    gl_Position = mvp * vec4(pos, 0.0, 1.0);
    color = col;
}
