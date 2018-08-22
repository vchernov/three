#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 model;

layout(std140) uniform Camera
{
    mat4 view;
    mat4 projection;
} camera;

void main()
{
    gl_Position = camera.projection * camera.view * model * vec4(position, 1.0);
}
