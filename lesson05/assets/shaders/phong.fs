#version 330 core

in  vec3 vertex_direction_eyespace;
in  vec3 lightdirection_eyespace;
in  vec3 normal_eyespace;
in  vec3 normal_worldspace;

uniform vec3 color;
uniform vec3 lightcolor;
uniform vec3 camerapos;

out vec4 fragColor;

float ambient_strength = 0.1f;
float specular_strength = 0.5;

void main() {
    // light source
    vec3 l = normalize(lightdirection_eyespace);

    // normal
    vec3 n = normalize(normal_eyespace);

    // eye position
    vec3 e = normalize(vertex_direction_eyespace);
    vec3 r = reflect(-l, n);

    // calculate diffuse
    float cosTheta = clamp(dot(n, l), 0, 1);

    // calculate specular
    float cosAlpha = clamp(dot(e,r), 0, 1);

    vec3 ambient = ambient_strength * lightcolor;
    vec3 diffuse = cosTheta * lightcolor;
    vec3 specular = pow(cosAlpha, 32) * specular_strength * lightcolor;

    vec3 result = (ambient + diffuse + specular) * color;

    fragColor = vec4(result, 1.0);
}
