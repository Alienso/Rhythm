//
// Created by Alienson on 11.8.2024..
//

#ifndef RHYTHM_SOUND_H
#define RHYTHM_SOUND_H


#include <vector>
#include <cstdint>
#include "portaudio.h"

class Sound {

public:
    explicit Sound(const char* path);

    unsigned int ID;
    int dataIndex = 0; //TODO fix class
    std::vector<int16_t> audioData;
    unsigned short numChannels = 0;
    unsigned int sampleRate = 0;
    PaStream *paStream = nullptr;
private:
};


#endif //RHYTHM_SOUND_H
