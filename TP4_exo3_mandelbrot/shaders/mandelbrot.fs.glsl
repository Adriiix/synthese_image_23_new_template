#version 330 core

in vec2 vVertexPosition;
out vec4 fFragColor;

vec2 complexSqr(vec2 z){
    vec2 result = vec2(pow(z.x,2)-pow(z.y,2), 2*z.x*z.y);
    return result;
}

bool isMandelbrot (vec2 c){
    int N = 200;
    vec2 sum = vec2(0,0);

    for (int i=0; i<N; i++)
    {
        sum=complexSqr(sum) + c;
        if (length(sum)>2)
        {
            return false;
        }   
    }
    return true;
}



void main()
{

    bool color = isMandelbrot(vVertexPosition);
    
    if (color == true)
    {
        fFragColor = vec4(0.f, 0.f,0.f, 1.f);
    }
    else {
        fFragColor = vec4(1.);
    }
    
    
}