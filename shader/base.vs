#version 460 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform vec2 translation;
uniform float rotation;
uniform vec2 scale;

uniform uint row;
uniform uint rowMax;
uniform uint column;
uniform uint columnMax;

uniform bool invertTex;

uniform float time;

void main(){

	mat3 translationMatrix;
	translationMatrix[0] = vec3(1,0,0);
	translationMatrix[1] = vec3(0,1,0);
	translationMatrix[2] = vec3(translation.x,translation.y,1);

	mat3 rotationMatrix;
	float sinT = sin(rotation);
	float cosT = cos(rotation);
    rotationMatrix[0] = vec3(cosT,sinT,0);
    rotationMatrix[1] = vec3(-sinT,cosT,0);
    rotationMatrix[2] = vec3(0,0,1);

    mat3 scaleMatrix;
    scaleMatrix[0] = vec3(scale.x,0,0);
    scaleMatrix[1] = vec3(0,scale.y,0);
    scaleMatrix[2] = vec3(0,0,1);

    mat3 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
    gl_Position = vec4(transformationMatrix * vec3(aPos, 1.0f), 1.0f);

    if (invertTex){
	    TexCoord = vec2((float(column) - aTexCoord.x + 1.0) / columnMax, (float(rowMax - 1 - row) + aTexCoord.y) / rowMax);
	}else{
	    TexCoord = vec2((float(column) + aTexCoord.x) / columnMax, (float(rowMax - 1 - row) + aTexCoord.y) / rowMax);
	}
}