#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

uniform float offset;

out vec2 TexCoords;

void main(){
    TexCoords = vec2(aTexCoords.x + offset, aTexCoords.y);
    gl_Position = vec4(aPos, 1.0);
}