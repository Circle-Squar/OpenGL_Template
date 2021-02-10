#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 Modul;

uniform float Fixx;
uniform float Fixy;

out vec3 ColorPos;

void main(){
  vec3 FixPos;
  vec4 Pos;

  Pos = Modul * vec4(aPos, 1.0);

  if(Fixx > Fixy){
    FixPos.x = Pos.x * (Fixy / Fixx);
    FixPos.y = Pos.y;
  }
  else{
    FixPos.x = Pos.x ;
    FixPos.y = Pos.y * (Fixx / Fixy);
  }

  FixPos.z = Pos.z;

  gl_Position = vec4(FixPos, 1.0);

  ColorPos = FixPos;
}
