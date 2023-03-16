#version 330 core

layout(location = 0) in vec2 aVertexPosition;

layout(location = 1) in vec2 aVertexTexture;

out vec2 vVertexPosition;

void main()
{
    vVertexPosition = aVertexPosition; // on sort la variable position
  
    gl_Position = vec4(aVertexPosition, 0., 1.);

}

