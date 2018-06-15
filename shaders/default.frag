#version 330 core

in VertexData {
    vec3 normal;
    vec3 worldPos;
} fragIn;

layout(std140) uniform Light {
    vec3 diffuse;
    vec3 pos;
} light;

uniform mat4 model;

out vec4 fragColor;

float halfLambert(vec3 fragPos, vec3 fragNormal, vec3 lightPos) {
    vec3 lightDir = normalize(lightPos - fragPos);
    float l = dot(fragNormal, lightDir) * 0.5 + 0.5;
    return max(pow(l, 1.2), 0.0);
}

void main() {
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 fragNormal = normalize(normalMatrix * fragIn.normal);
    fragColor = vec4(light.diffuse * halfLambert(fragIn.worldPos, fragNormal, light.pos), 1.0);
}
