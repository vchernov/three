uniform vec2 u_resolution;

float circle(vec2 uv, vec2 p, float r, float blur)
{
    float d = length(uv - p);
    return smoothstep(r, r - blur, d);
}

void main()
{
    vec2 uv = gl_FragCoord.xy / u_resolution.xy;
    uv -= 0.5;
    uv.x *= u_resolution.x / u_resolution.y;
    
    float mask = 0.0;
    mask += circle(uv, vec2(0.0, 0.0), 0.45, 0.02);
    
    vec3 color = vec3(1.0, 1.0, 0.0) * mask;
    gl_FragColor = vec4(color, 1.0);
}