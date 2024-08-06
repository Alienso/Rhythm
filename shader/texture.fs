#version 450 core
out vec4 FragColor;

in vec2 TexCoords;

layout(binding=0) uniform sampler2D texture1;

void main(){
    FragColor = texture(texture1, TexCoords);
}