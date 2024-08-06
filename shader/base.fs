#version 460 core

out vec4 FragColor;

in vec2 TexCoord;

layout(binding=0) uniform sampler2D texture1;

void main(){
    FragColor = texture(texture1, TexCoord);
}