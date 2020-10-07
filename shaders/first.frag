#version 330 core

uniform vec2 u_resolution;
uniform float u_time;

out vec4 fragColor;

void main()
{
    vec2 uv = gl_FragCoord.xy / u_resolution.xy;
    uv.x *= u_resolution.x / u_resolution.y;
    
    //vec3 color = vec3(uv.x, uv.y, 0.0);
    vec3 color = vec3(uv.x, uv.y, abs(sin(u_time)));
    
    fragColor = vec4(color, 1.0);
}
