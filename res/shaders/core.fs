#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec3 Normal;
in vec3 PixelPos;
uniform vec3 LightPos;
uniform vec3 ViewPos;
void main()
{
       // ambient
       vec3 ambient = 0.2 * ourColor;
       // diffuse
       vec3 norm = normalize(Normal);
       vec3 lightDir = normalize(LightPos - PixelPos);
       float diff = 0.8f * max(dot(norm, lightDir), 0.0f);
       vec3 diffuse = diff * ourColor;
       // specular
       vec3 viewDir = normalize(ViewPos-PixelPos);
       vec3 halfAngle = normalize(lightDir + viewDir);
       float spec = 0.9f * pow(max(dot(norm, halfAngle), 0.0f), 32);
       vec3 specular = spec * ourColor;

       FragColor = vec4(ambient + diffuse + specular, 1.0f);
}