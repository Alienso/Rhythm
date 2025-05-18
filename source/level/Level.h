//
// Created by Alienson on 1.8.2024..
//

#ifndef RHYTHM_LEVEL_H
#define RHYTHM_LEVEL_H


#include "render/sprite/Sprite.h"
#include "reference/Reference.h"
#include "render/ParallaxTexture.h"
#include "render/sprite/SpriteInstanced.h"
#include "Tile.h"
#include "Room.h"

class Level {
public:
    explicit Level(const char* path);
    ~Level();

    void onRender();
    void onUpdate(float deltaTime);

    Room& getCurrentRoom();
    static void increaseScore(unsigned int amount, float scoreMultiplier);

    static inline int score = 0;
    float tileScale;
    ParallaxTexture background{ {"resource/texture/background/ParallaxMountain/sky.png",
                                 "resource/texture/background/ParallaxMountain/far-clouds.png",
                                 "resource/texture/background/ParallaxMountain/near-clouds.png",
                                 "resource/texture/background/ParallaxMountain/far-mountains.png",
                                 "resource/texture/background/ParallaxMountain/mountains.png",
                                 "resource/texture/background/ParallaxMountain/trees.png"},
                                {0.1f, 0.3f, 0.5f, 0.6f, 0.6f, 1.0f} }; //TODO this should be a parameter

private:
    std::vector<SpriteInstanced> tileSprites;
    unsigned int currentRoomIndex = 0;
    std::vector<Room> rooms;

    void loadTiles(const char* path, std::unordered_map<unsigned int, TilePositions>& sprites);

};


#endif //RHYTHM_LEVEL_H
