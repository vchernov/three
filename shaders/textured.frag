#version 330 core

in VertexData {
    vec2 texCoord;
} i;

uniform sampler2D tex;

out vec4 fragColor;

void main() {
    fragColor = texture2D(tex, i.texCoord);
}
