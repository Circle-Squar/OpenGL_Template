#version 330 core
out vec4 FragColor;

in vec3 ColorPos;

void main(){
  vec3 Color;
  Color.g = (ColorPos.r + 1.0) / 2;
  Color.r = (ColorPos.g + 1.0) / 2;
  Color.b = (ColorPos.b + 1.0) / 2;

  FragColor = vec4(Color, 1.0);
}
