#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 model;

layout(std140) uniform Camera {
    mat4 view;
    mat4 projection;
} camera;

out VertexData {
    vec3 normal;
    vec3 fragPos;
} output;

void main() {
    vec4 worldPos = model * vec4(position, 1.0);
    gl_Position = camera.projection * camera.view * worldPos;
    output.normal = normal;
    output.fragPos = worldPos.xyz;
}
