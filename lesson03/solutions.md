# Solutions to exercises
Below are the solutions to the exercises.

### Exercise 01: Use the position of the cube for the color
Change the vertex and fragment shaders as follows

```
#version 330 core

uniform mat4 mvp;

in vec3 col;
in vec3 pos;

out vec3 color;
out vec3 position;

void main()
{
    gl_Position = mvp * vec4(pos, 1.0);
    position = pos;
    color = col;
}
```

```
#version 330 core

in vec3 color;
in vec3 position;
out vec4 outcol;

void main()
{
    outcol = vec4(position + vec3(0.5, 0.5, 0.5), 1.0);
}
```

### Exercise 02: Move the cube to the right
Change the vertex shader to
```
#version 330 core

uniform mat4 mvp;

in vec3 col;
in vec3 pos;

out vec3 color;

void main()
{
    gl_Position = mvp * vec4(pos, 1.0) + vec4(1.0 ,0.0, 0.0, 0.0);
    color = col;
}
```
