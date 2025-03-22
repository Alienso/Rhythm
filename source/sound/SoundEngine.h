//
// Created by Alienson on 11.8.2024..
//

#ifndef RHYTHM_SOUNDENGINE_H
#define RHYTHM_SOUNDENGINE_H


#include "Sound.h"
#include "portaudio.h"
#include "BeatOffset.h"

class SoundEngine {

public:
    SoundEngine();
    ~SoundEngine();

    void play(Sound* sound, float volume = 1.0);
    void stop(SoundInstance* sound);
    void pause(SoundInstance* sound);

    void seek(int seconds); //TODO

    void onUpdate(float deltaTime);
    [[nodiscard]] BeatOffset* getBeatOffset() const;

private:
    static const inline int FRAMES_PER_BUFFER = 1024;
    std::vector<SoundInstance*> soundsPlaying{10};
    SoundInstance* currentSong = nullptr;
    float onUpdateTimer = 1.0f;
};

#endif //RHYTHM_SOUNDENGINE_H
