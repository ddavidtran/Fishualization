#version 330 core

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform sampler2D tex;
uniform vec3 fogcolor;


in vec3 normal;
in vec2 st;
in vec3 FragPos;

out vec4 fragcolor;

void main() {

	vec3 color = texture(tex, st).rgb;
    vec3 normal = normalize(-normal);
    vec3 lightColor = vec3(1.0);
    // Ambient
    vec3 ambient = 0.3 * color;
    // Diffuse
    vec3 lightDir = normalize(FragPos - lightPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    // Specular
    vec3 viewDir = normalize(FragPos + viewPos);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;    

    float viewLength = length(FragPos.z - viewPos.z);

    float f = (2.0 - viewLength) / (2.0 - 0.1);
    if(f < 0.0)
    {
        f = 0.0;
    }
    else if(f > 1.0)
    {
        f = 1.0;
    }
    //vec3 lighting = f*(ambient  + (diffuse + specular) * color) + (1.0-f) * fogcolor;
        vec3 lighting = (ambient  + (diffuse + specular) * color);

	fragcolor = vec4(lighting, 1.0);
}