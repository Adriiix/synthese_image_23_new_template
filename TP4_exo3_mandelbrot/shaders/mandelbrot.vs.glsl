#version 330 core

layout(location = 0) in vec2 aVertexPosition;

out vec2 vVertexPosition;

void main()
{
    vVertexPosition = aVertexPosition;
    gl_Position = vec4(aVertexPosition, 0., 1.);
}