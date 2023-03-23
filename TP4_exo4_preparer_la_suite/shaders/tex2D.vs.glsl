#version 330 core

layout(location = 0) in vec2 aVertexPosition;

layout(location = 1) in vec2 aVertexTexture;

out vec2 vVertexPosition;
out vec2 vVertexTexture;

//uniform mat3 uModelMatrix;

mat3 rotate(float a){
  return mat3(
    vec3(cos(radians(a)),sin(radians(a)),0),
    vec3(-sin(radians(a)),cos(radians(a)),0),
    vec3(0,0,1)
);
};

void main()
{
    vVertexPosition = aVertexPosition; // on sort la variable position
    vVertexTexture = aVertexTexture; 

    gl_Position = vec4(aVertexPosition, 0., 1.); 

}

