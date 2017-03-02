#version 440

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform sampler2D tex;
uniform sampler2D shadowMap;


in vec3 normal;
in vec2 st;
in vec3 FragPos;
in vec4 FragPosLightSpace;

out vec4 fragcolor;

float random(vec2 seed, int i){
	vec3 seed3 = vec3(seed,i);
    return fract(sin(dot(seed3.xyz ,vec3(12.9898,78.233, 45.164))) * 43758.5453);
}

float ShadowCalculation(vec4 fragPosLightSpace, vec3 lightDir)
{

	
	vec2 poissonDisk[10] = vec2[]( 
   vec2( -0.94201624, -0.39906216 ), 
   vec2( 0.94558609, -0.76890725 ), 
   vec2( -0.094184101, -0.92938870 ), 
   vec2( 0.34495938, 0.29387760 ), 
   vec2( -0.91588581, 0.45771432 ), 
   vec2( -0.81544232, -0.87912464 ), 
   vec2( -0.38277543, 0.27676845 ), 
   vec2( 0.97484398, 0.75648379 ), 
   vec2( 0.44323325, -0.97511554 ), 
   vec2( 0.53742981, -0.47373420 ) 
   
);

    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // Transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 

    // Get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;

    // Check whether current frag pos is in shadow	
	//Solving shadow acne
	float bias = 0.005;  
	//float shadow = currentDepth > closestDepth + bias ? 0.0 : 1.0; 
	float visibility = 1.0;
	for (int i=0;i<4;i++){
		int index = int(10.0*random(floor(FragPos.xy*1000.0), i))%10;
		  if ( texture( shadowMap, projCoords.xy + poissonDisk[index]/5500.0 ).z  <  projCoords.z-bias ){
			visibility-=0.2;
		  }
	}

    return visibility;
} 

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
    float shadow = ShadowCalculation(FragPosLightSpace,lightDir);       
    vec3 lighting = (ambient + (shadow) * (diffuse + specular)) * color; 
	fragcolor = vec4(lighting, 1.0f);
}