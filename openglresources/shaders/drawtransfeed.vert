#version 300 es                                                    
#define ATTRIBUTE_POSITION      0
#define ATTRIBUTE_TEXCOORD      1
                                                                   
layout(location = ATTRIBUTE_POSITION) in vec3 a_position;
layout(location = ATTRIBUTE_TEXCOORD) in vec2 a_texcoord;

out vec2 texPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

vec4 pos;

void main()                                                        
{
    //pos = model * view * projection * vec4(a_position, 1.0);
    pos = projection * vec4(a_position, 1.0);
    texPos = a_texcoord;
    gl_Position = pos;
}
