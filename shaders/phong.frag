#version 330 core

in VertexData {
    vec3 normal;
    vec3 fragPos;
} input;

uniform mat4 model;
uniform vec3 color;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 fragColor;

void main() {
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 fragNormal = normalize(normalMatrix * input.normal); //TODO: optimize
    
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    vec3 lightDir = normalize(lightPos - input.fragPos);
    float diff = max(dot(fragNormal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - input.fragPos);
    vec3 reflectDir = reflect(-lightDir, fragNormal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
    vec3 specular = specularStrength * spec * lightColor;
    
    fragColor = vec4(clamp(ambient + diffuse + specular, 0, 1) * color, 1.0);
}
