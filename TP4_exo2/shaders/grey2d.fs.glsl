#version 330 core

in vec3 vFragColor;
in vec2 vVertexPosition; // la variale de position qui entre 

out vec4 fFragColor;

void main() {
  float alpha=2;
  float beta=70;

  // float a = alpha * exp(-beta * pow(distance(vVertexPosition,vec2(0,0)),2)); // pour la particule

  // fFragColor = vec4((vFragColor.x+vFragColor.y+vFragColor.z)/3, (vFragColor.x+vFragColor.y+vFragColor.z)/3, (vFragColor.x+vFragColor.y+vFragColor.z)/3, 1.); // pour le gris

  //Textures procédurales 

  //float a = length(fract(5.0 * vVertexPosition));
  //float a = length(abs(fract(5.0 * vVertexPosition) * 2.0 - 1.0));
  //float a = mod(floor(10.0 * vVertexPosition.x) + floor(10.0 * vVertexPosition.y), 2.0);
  float a = smoothstep(0.3, 0.32, length(fract(5.0 * vVertexPosition) - 0.5));

  fFragColor = vec4(a*vFragColor.x, a*vFragColor.y, a*vFragColor.z, 1.);
};