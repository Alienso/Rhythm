//
// Created by Alienson on 3.8.2024..
//

#include "Rhythm.h"
#include "Reference.h"
#include "glad.h"

static void initTextures(AssetManager<Texture>& textureManager) {
    Textures::BLANK = textureManager.createAsset("resource/texture/blank.png", GL_RGBA);
    Textures::BACKGROUND = textureManager.createAsset("resource/texture/background/SpaceBackgroundHD.png", GL_RGBA);

    Textures::BIKER = textureManager.createAsset("resource/texture/character/Biker/Biker.png", GL_RGBA);
    Textures::NIGHTMARE = textureManager.createAsset("resource/texture/entity/Nightmare2.png", GL_RGBA);

    Textures::CURSOR = textureManager.createAsset("resource/texture/ui/cursor_white.png", GL_RGBA);
    Textures::MULTIPLIER_FRAME = textureManager.createAsset("resource/texture/ui/multiplier_frame.png", GL_RGBA);

    Textures::PISTOL = textureManager.createAsset("resource/texture/weapon/pistol_rotated.png", GL_RGBA);

    Textures::MIST = textureManager.createAsset("resource/texture/particle/mist64.png", GL_RGBA);
    Textures::PARTICLE_GUNSHOT = textureManager.createAsset("resource/texture/particle/gunshot.png", GL_RGBA);
    Textures::FLAME_CIRCLE = textureManager.createAsset("resource/texture/particle/flame_circle.png", GL_RGBA);
}

static void initShaders(AssetManager<Shader>& shaderManager) {
    Shaders::SPRITE = shaderManager.createAsset("shader/sprite.vs", "shader/sprite.fs");
    Shaders::SPRITE_STATIC = shaderManager.createAsset("shader/sprite_static.vs", "shader/sprite.fs");
    Shaders::SPRITE_INSTANCED = shaderManager.createAsset("shader/sprite_instanced.vs", "shader/sprite.fs");
    Shaders::TEXTURE = shaderManager.createAsset("shader/texture.vs", "shader/texture.fs");
    Shaders::TEXTURE_MONO = shaderManager.createAsset("shader/texture.vs", "shader/texture_mono.fs");
    Shaders::TEXTURE_PARALLAX = shaderManager.createAsset("shader/texture_parallax.vs", "shader/texture.fs");
}

static void initSounds(AssetManager<Sound>& soundManager){
    Sounds::MTYN = soundManager.createAsset("resource/sound/music/More_Than_You_Know.wav", 123, 18000);
    Sounds::DISSOLUTION = soundManager.createAsset("resource/sound/music/dissolution.wav", 140, 2000);
    Sounds::DEVASTATION = soundManager.createAsset("resource/sound/music/Devastation.wav", 130, 0);
    Sounds::REVOLVER_SHOOT = soundManager.createAsset("resource/sound/effect/pistol_gunshot2.wav");
    Sounds::REVOLVER_SHOOT_WEAK = soundManager.createAsset("resource/sound/effect/pistol_weak2.wav");
    Sounds::SLASH_1 = soundManager.createAsset("resource/sound/effect/slash_1.wav");
}

static void initParticles() {
    AffineTransformations trans({0,0}, {0.05,0.05}, M_PI/4.0);
    Particles::REVOLVER_SHOOT = new Particle(Textures::PARTICLE_GUNSHOT, 5, trans, 0.25);
}

void Rhythm::initAssets(){
    initTextures(textureManager);
    initShaders(shaderManager);
    initSounds(soundManager);
    initParticles();
}