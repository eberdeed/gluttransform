#version 300 es

#define NUM_PARTICLES           36
#define ATTRIBUTE_POSITION      0
#define ATTRIBUTE_TEXCOORD      1
precision highp float;

layout(location = ATTRIBUTE_POSITION) in vec3 a_position;
layout(location = ATTRIBUTE_TEXCOORD) in vec2 a_texcoord;

out vec3 v_position;               
out vec2 v_texcoord;

uniform mat4 orientation;
uniform vec3 movement;
uniform float sign;
float inc = 0.0;
vec4 tmpPos;
void main()    
{   
    inc = 1.0 + (0.004 * sign);
    tmpPos = vec4(a_position, 1.0);
    tmpPos *= inc;
    tmpPos += vec4(movement, 1.0);
    tmpPos *= orientation;
    v_position = tmpPos.xyz;
    v_texcoord = a_texcoord;
    gl_Position = tmpPos;                      
}             

