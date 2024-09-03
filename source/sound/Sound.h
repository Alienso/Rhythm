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
    explicit Sound(const char* path, unsigned int bpm = 60, unsigned int initialOffset = 0);
    unsigned int ID;
    unsigned short numChannels = 0;
    unsigned int sampleRate = 0;
    unsigned int bpm;
    unsigned int beatInitialOffset;

    friend SoundInstance;

private:
    std::vector<int16_t> audioData;
};

class SoundInstance{
public:
    explicit SoundInstance(Sound* sound, float volume = 1.0);

    [[nodiscard]] int16_t getNextValue();
    [[nodiscard]] unsigned long getOffset() const;
    [[nodiscard]] size_t getDataSize() const;
    [[nodiscard]] unsigned int getSampleRate() const;
    [[nodiscard]] unsigned int getNumberOfChannels() const;
    [[nodiscard]] unsigned long getNextBeatOffset() const;
    [[nodiscard]] unsigned long getPreviousBeatOffset() const;

    void seek(int seconds);

    PaStream *paStream = nullptr;
    float volume = 1.0;
    float spb;

private:
    unsigned long offset = 0;
    Sound* sound = nullptr;
};


#endif //RHYTHM_SOUND_H
