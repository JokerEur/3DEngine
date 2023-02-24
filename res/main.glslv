#version 330 core

layout (location =  0) in vec3 v_posiotion;

out vec4 a_color;

void main(){
    a_color = vec4(0.5,0.5,0.5,1.0);
    gl_Position = vec4(v_posiotion , 1.0);
}