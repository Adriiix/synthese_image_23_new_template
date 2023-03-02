#version 330 core

in vec3 vFragColor;

out vec4 fFragColor;

void main() {
  fFragColor = vec4((vFragColor.x+vFragColor.y+vFragColor.z)/3, (vFragColor.x+vFragColor.y+vFragColor.z)/3, (vFragColor.x+vFragColor.y+vFragColor.z)/3, 1.);
};