#version 460 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec2 aOffset;
layout(binding = 0) uniform Matrices {
    mat3 aspectFix;
};

out vec2 TexCoord;

void main(){
    gl_Position = vec4(aspectFix * vec3( aPos+ aOffset, 1.0f), 1.0);
    TexCoord = aTexCoord;
}