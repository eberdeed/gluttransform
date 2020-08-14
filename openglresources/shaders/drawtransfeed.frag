#version 300 es                                  
precision highp float;                         

in vec2 texPos;


layout(location = 0) out vec4 fragColor;         

uniform highp sampler2D s_texture;
uniform highp sampler2DArray sides;
uniform int index;

vec4 color1, color2;

void main()                                      
{
    
     color1 = texture( s_texture, texPos);
     color2 = texture( sides, vec3(texPos, float(index)));
     fragColor = mix(color1, color2, 0.5);
    //fragColor = vec4(1.0, 1.0, 1.0, 1.0);
}                                                    
