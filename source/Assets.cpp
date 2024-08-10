//
// Created by Alienson on 3.8.2024..
//

#include "Rhythm.h"
#include "Assets.h"
#include "glad.h"

void Rhythm::initAssets(){
    Textures::BLANK = textureManager.createAsset("resource/texture/blank.png", GL_RGBA);
    Textures::BACKGROUND = textureManager.createAsset("resource/texture/background/SpaceBackgroundHD.png", GL_RGBA);
    Textures::BIKER = textureManager.createAsset("resource/texture/character/Biker/Biker.png", GL_RGBA);
    Textures::CURSOR = textureManager.createAsset("resource/texture/cursor_white.png", GL_RGBA);
    Textures::PISTOL = textureManager.createAsset("resource/texture/weapon/pistol.png", GL_RGBA);

    Shaders::ENTITY = shaderManager.createAsset("shader/base.vs", "shader/base.fs");
    Shaders::SPRITE = shaderManager.createAsset("shader/sprite.vs", "shader/base.fs");
    Shaders::TEXTURE = shaderManager.createAsset("shader/texture.vs", "shader/texture.fs");
    Shaders::TEXTURE_MONO = shaderManager.createAsset("shader/texture.vs", "shader/texture_mono.fs");
}