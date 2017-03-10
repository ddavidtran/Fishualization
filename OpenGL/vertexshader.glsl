#version 440

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 TexCoord;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform float time;
uniform bool fishes;
uniform float fishspeed;

out vec3 normal;
out vec2 st;
out vec3 FragPos;


void main(){

  vec3 pos = Position;
  float fs = max(fishspeed, 0.98);
  if(fishes){
    pos.x = pos.x + fishspeed*(pos.z - 0.2)*0.09*sin(10.0*pos.z + 6.0*time);
  }

  gl_Position = (P * V * M) * vec4(pos, 1.0f);
  normal = transpose(inverse(mat3(M))) * Normal;
  FragPos = vec3(M * vec4(pos, 1.0));
  st = TexCoord;
}
