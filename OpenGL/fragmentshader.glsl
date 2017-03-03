#version 440

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform sampler2D tex;
//uniform sampler2D shadowMap;


in vec3 normal;
in vec2 st;
in vec3 FragPos;
//in vec4 FragPosLightSpace;

out vec4 fragcolor;

void main() {

	vec3 color = texture(tex, st).rgb;
    vec3 normal = normalize(-normal);
    vec3 lightColor = vec3(1.0);
    // Ambient
    vec3 ambient = 0.15 * color;
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
    // Calculate shadow
    //float shadow = ShadowCalculation(FragPosLightSpace,lightDir);
    vec3 lighting = (ambient  + (diffuse + specular)) * color;
	fragcolor = vec4(1.0,1.0,1.0, 1.0);
}