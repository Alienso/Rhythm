//
// Created by Alienson on 11.8.2024..
//

#ifndef RHYTHM_SOUND_H
#define RHYTHM_SOUND_H


#include <vector>
#include <cstdint>
#include "portaudio.h"

class SoundInstance;

class Sound {

public:
    explicit Sound(const char* path);
    unsigned int ID;
    unsigned short numChannels = 0;
    unsigned int sampleRate = 0;

    friend SoundInstance;

private:
    std::vector<int16_t> audioData;
};

class SoundInstance{
public:
    explicit SoundInstance(Sound* sound, float volume = 1.0);

    [[nodiscard]] int16_t getNextValue();
    [[nodiscard]] unsigned int getOffset() const;
    [[nodiscard]] size_t getDataSize() const;
    PaStream *paStream = nullptr;
    float volume = 1.0;
private:
    unsigned int offset = 0;
    Sound* sound = nullptr;
};


#endif //RHYTHM_SOUND_H
