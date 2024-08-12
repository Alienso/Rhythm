//
// Created by Alienson on 11.8.2024..
//

#ifndef RHYTHM_SOUNDENGINE_H
#define RHYTHM_SOUNDENGINE_H


#include "Sound.h"
#include "portaudio.h"

class SoundEngine {

public:
    SoundEngine();
    ~SoundEngine();

    void play(Sound* sound);
    void stop(SoundInstance* sound);
    void pause(SoundInstance* sound);

private:
    static const inline int FRAMES_PER_BUFFER = 1024;
};


#endif //RHYTHM_SOUNDENGINE_H
