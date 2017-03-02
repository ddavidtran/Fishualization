#version 440

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 TexCoord;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat4 lightSpaceMatrix;

out vec3 normal;
out vec2 st;
out vec3 FragPos;
out vec4 FragPosLightSpace;

void main(){
  gl_Position = (P * V * MV) * vec4(Position, 1.0f);
  normal = transpose(inverse(mat3(MV))) * Normal;
  FragPos = vec3(MV * vec4(Position, 1.0));
  FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
  st = TexCoord;
}
