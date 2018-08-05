#version 330 core

in vec3 position;
in vec3 normal;

out vec3 vertex_direction_eyespace;
out vec3 lightdirection_eyespace;

out vec3 normal_worldspace;
out vec3 normal_eyespace;

uniform mat4 model;
uniform mat4 view;
uniform mat4 mvp;
uniform vec3 lightpos;

void main() {
    // output position of the vertex
    gl_Position = mvp * vec4(position, 1.0);

    // calculate vertex-to-camera direction in eye space
    vec3 position_eyespace = (view * model * vec4(position, 1.0)).xyz;
    vertex_direction_eyespace = vec3(0,0,0) - position_eyespace;

    // calculate light-to-vertex direction in eye space
    vec3 position_worldspace = (model * vec4(position, 1.0)).xyz;
    vec3 light_direction_worldspace = lightpos - position_worldspace.xyz;
    lightdirection_eyespace = (view * vec4(light_direction_worldspace, 0.0)).xyz;

    // vertex normals in world and eye space
    normal_worldspace = (transpose(inverse(model)) * vec4(normal, 0.0)).xyz;
    normal_eyespace = (transpose(inverse(view * model)) * vec4(normal, 0.0)).xyz;
}
