#version 330 core

in vec3 vFragColor;
in vec2 vVertexPosition; // la variale de position qui entre 

out vec4 fFragColor;

void main() {
  float alpha=2;
  float beta=70;
  float a = alpha * exp(-beta * pow(distance(vVertexPosition,vec2(0,0)),2));
  // fFragColor = vec4((vFragColor.x+vFragColor.y+vFragColor.z)/3, (vFragColor.x+vFragColor.y+vFragColor.z)/3, (vFragColor.x+vFragColor.y+vFragColor.z)/3, 1.); // pour le gris
  fFragColor = vec4(a*vFragColor.x, a*vFragColor.y, a*vFragColor.z, 1.);
};