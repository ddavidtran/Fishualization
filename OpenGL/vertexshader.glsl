#version 440

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 TexCoord;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;


out vec3 normal;
out vec2 st;
out vec3 FragPos;


void main(){
  gl_Position = (P * V * M) * vec4(Position, 1.0);
  normal = transpose(inverse(mat3(M))) * Normal;
  FragPos = vec3(M * vec4(Position, 1.0));
  st = TexCoord;
}
