#version 330 core

in VertexData
{
    vec3 color;
} fragIn;

out vec4 fragColor;

void main()
{
    fragColor = vec4(fragIn.color, 1.0);
}
