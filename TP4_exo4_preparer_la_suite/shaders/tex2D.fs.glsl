#version 330 core

in vec2 vVertexTexture; 

out vec4 fFragColor;

uniform sampler2D uTexture;

void main()
{

    vec4 color = texture(uTexture,vVertexTexture);

    //fFragColor = vec4(1.,0.,0., 1.);
    fFragColor = vec4(color.xyz,1.);
    
}

