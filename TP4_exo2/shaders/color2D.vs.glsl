#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

//les variables qui vont sortir pour aller dans l'autre shader
out vec3 vFragColor;
out vec2 vVertexPosition;

mat3 translate(float tx, float ty){
  return mat3(
    vec3(1, 0, 0),
    vec3(0, 1, 0),
    vec3(tx, ty, 1)
);
}

mat3 scale(float sx, float sy){
  return mat3(
    vec3(sx, 0, 0),
    vec3(0, sy, 0),
    vec3(0, 0, 1)
);
}

mat3 rotate(float a){
  return mat3(
    vec3(cos(radians(a)),sin(radians(a)),0),
    vec3(-sin(radians(a)),cos(radians(a)),0),
    vec3(0,0,1)
);
};


void main() {
  vFragColor = aVertexColor; 
  vVertexPosition = aVertexPosition; // on sort la variable position

  //gl_Position = vec4((translate(1,1)*vec3(aVertexPosition,1.)).xy, 0., 1.); // translation de (1,0)
  //gl_Position = vec4((rotate(180)*vec3(aVertexPosition,1.)).xy, 0., 1.); 
  //gl_Position = vec4((translate(0.5,0)*rotate(45)*scale(0.5,0.5)*vec3(aVertexPosition,1.)).xy, 0., 1.); 
  //gl_Position = vec4((rotate(45)*translate(0.5,0)*scale(0.5,0.5)*vec3(aVertexPosition,1.)).xy, 0., 1.); 
  
  gl_Position = vec4((vec3(aVertexPosition,1.)).xy, 0., 1.); 
};