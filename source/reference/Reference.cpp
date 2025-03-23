//
// Created by Alienson on 3.8.2024..
//

#include "Rhythm.h"
#include "Reference.h"
#include "glad/glad.h"

static void initTextures(AssetManager<Texture>& textureManager) {
    Textures::BLANK = textureManager.createAsset("resource/texture/blank.png", GL_RGBA);
    Textures::BACKGROUND = textureManager.createAsset("resource/texture/background/SpaceBackgroundHD.png", GL_RGBA);

    Textures::BIKER = textureManager.createAsset("resource/texture/character/Biker/Biker.png", GL_RGBA);
    Textures::NIGHTMARE = textureManager.createAsset("resource/texture/entity/Nightmare.png", GL_RGBA);

    Textures::CURSOR = textureManager.createAsset("resource/texture/ui/cursor_white.png", GL_RGBA);
    Textures::MULTIPLIER_FRAME = textureManager.createAsset( "resource/texture/ui/multiplier_frame.png", GL_RGBA);
    Textures::COLLISION_BOX = textureManager.createAsset("resource/texture/ui/collision_box.png", GL_RGBA);

    Textures::PISTOL = textureManager.createAsset("resource/texture/weapon/pistol_rotated.png", GL_RGBA);

    Textures::MIST = textureManager.createAsset("resource/texture/particle/mist64.png", GL_RGBA);
    Textures::PARTICLE_GUNSHOT = textureManager.createAsset("resource/texture/particle/gunshot2.png", GL_RGBA);
    Textures::FLAME_CIRCLE = textureManager.createAsset("resource/texture/particle/flame_circle.png", GL_RGBA);

    Textures::BRICK_TILE = textureManager.createAsset("resource/texture/tile/stone_brick.png", GL_RGBA);
    Textures::METAL_SLAB_TILE = textureManager.createAsset("resource/texture/tile/metal_slab.png", GL_RGBA);
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
    Sounds::BEAT_MISS = soundManager.createAsset("resource/sound/effect/beat_miss.wav");
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

static void initTiles(AssetManager<Tile>& tileManager){
    Tiles::BRICK = tileManager.createAsset(500, Textures::BRICK_TILE);
    Tiles::METAL_SLAB = tileManager.createAsset(501, Textures::METAL_SLAB_TILE, true, false, glm::vec2{0, -0.3}, glm::vec2{1, 0.4545}); //TODO feels like this offset is affected by scale
}

void Rhythm::initAssets(){
    initTextures(textureManager);
    initShaders(shaderManager);
    initSounds(soundManager);
    initParticles();
    initTiles(tileManager);
}