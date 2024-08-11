#version 460 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform vec2 translation;
uniform float rotation;
uniform vec2 scale;

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

    mat3 transformationMatrix;
    if (rotation != 0){
        mat3 aspectFix;
        aspectFix[0] = vec3(0.5625,0,0);
        aspectFix[1] = vec3(0,1,0);
        aspectFix[2] = vec3(0,0,1);

        mat3 aspectFix2;
        aspectFix2[0] = vec3(1.78888,0,0);
        aspectFix2[1] = vec3(0,1,0);
        aspectFix2[2] = vec3(0,0,1);

        transformationMatrix = translationMatrix * aspectFix * rotationMatrix * aspectFix2 * scaleMatrix; //TODO
    }else{
        transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
    }
    gl_Position = vec4(transformationMatrix * vec3(aPos, 1.0f), 1.0f);

	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}