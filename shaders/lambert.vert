#version 330 core

layout (location = 0) in vec3 position;
layout (location = 3) in vec3 normal;

uniform mat4 model;

layout(std140) uniform Camera {
    mat4 view;
    mat4 projection;
} camera;

out VertexData {
    vec3 normal;
    vec3 worldPos;
} vertex;

void main() {
    vec4 worldPos = model * vec4(position, 1.0);
    gl_Position = camera.projection * camera.view * worldPos;
    vertex.normal = normal;
    vertex.worldPos = worldPos.xyz;
}
