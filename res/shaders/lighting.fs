#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec3 Normal;
in vec3 PixelPos;
uniform vec3 LightPos;
uniform vec3 ViewPos;
void main()
{
    // Diffuse + Specular ONLY (no ambient - that was in pass 1)
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - PixelPos);
    float diff = 0.8 * max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * ourColor;
    
    vec3 viewDir = normalize(ViewPos - PixelPos);
    vec3 halfAngle = normalize(lightDir + viewDir);
    float spec = 0.9 * pow(max(dot(norm, halfAngle), 0.0), 32.0);
    vec3 specular = spec * ourColor;
    
    FragColor = vec4(diffuse + specular, 1.0);
}