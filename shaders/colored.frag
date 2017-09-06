#version 330 core

in VertexData {
    vec3 color;
} i;

out vec4 fragColor;

void main() {
    fragColor = vec4(i.color, 1.0);
}
