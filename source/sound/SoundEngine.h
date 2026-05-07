//
// Created by Alienson on 11.8.2024..
//

#ifndef RHYTHM_SOUNDENGINE_H
#define RHYTHM_SOUNDENGINE_H


#include "Sound.h"
#include "portaudio.h"
#include "BeatOffsetType.h"

class SoundEngine {

public:
    SoundEngine();
    ~SoundEngine();

    void play(Sound* sound, float volume = 1.0);
    static void stop(SoundInstance* sound);
    static void pause(SoundInstance* sound);

    void seek(int seconds);

    void onUpdate(float deltaTime);

private:
    static const inline int FRAMES_PER_BUFFER = 1024;
    std::vector<SoundInstance*> soundsPlaying{30, nullptr};
    SoundInstance* currentSong = nullptr;
    float onUpdateTimer = 1.0f;

    static SoundInstance* playStream(Sound* sound, float volume = 1.0);

};

#endif //RHYTHM_SOUNDENGINE_H
