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

    void play(Sound* sound, float volume = 1.0);
    void stop(SoundInstance* sound);
    void pause(SoundInstance* sound);

    void onUpdate(float deltaTime);
    [[nodiscard]] int doAction() const;

    SoundInstance* currentSong = nullptr; //TODO move

private:
    static const inline int FRAMES_PER_BUFFER = 1024;
    std::vector<SoundInstance*> soundsPlaying{10};
    float onUpdateTimer = 1.0f;
};


#endif //RHYTHM_SOUNDENGINE_H
