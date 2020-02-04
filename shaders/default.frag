#version 330 core

in VertexData
{
    vec3 normal;
    vec3 worldPos;
    vec2 texCoord;
} fragIn;

layout(std140) uniform Light
{
    vec3 diffuse;
    vec3 pos;
} light;

uniform mat4 model;
uniform sampler2D diffuseTex;

out vec4 fragColor;

float halfLambert(vec3 fragPos, vec3 fragNormal, vec3 lightPos)
{
    vec3 lightDir = normalize(lightPos - fragPos);
    float l = dot(fragNormal, lightDir) * 0.5 + 0.5;
    return max(pow(l, 1.2), 0.0);
}

void main()
{
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 fragNormal = normalize(normalMatrix * fragIn.normal);
    vec4 texColor = texture2D(diffuseTex, fragIn.texCoord);
    fragColor = vec4(light.diffuse * halfLambert(fragIn.worldPos, fragNormal, light.pos), 1.0) * texColor;
}
