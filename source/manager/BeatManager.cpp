//
// Created by Vladimir Arsenijevic on 6.5.2026.
//

#include <cassert>
#include <GLFW/glfw3.h>
#include "BeatManager.h"

void BeatManager::buildBeatFrames(SoundInstance *soundInstance_) {
    soundInstance = soundInstance_;
    currentFramIndex = 0;

    int soundFramesPerBeat = soundInstance_->spb * soundInstance_->getSampleRate() * soundInstance_->getNumberOfChannels();
    int totalBeatFrames = (soundInstance_->getDataSize() - soundInstance_->getFirstBeatOffset()) / soundFramesPerBeat; //approximation
    beatFrames.clear();
    beatFrames.reserve(totalBeatFrames);

    long currentSoundFrame = (long)soundInstance_->getFirstBeatOffset() - soundFramesPerBeat / 2; //Offset this by half of beat frame
    long soundFramesPerSecond = soundInstance_->getSampleRate() * soundInstance_->getNumberOfChannels();

    while (true){
        float begin = currentSoundFrame * 1.0f / soundFramesPerSecond;
        currentSoundFrame += soundFramesPerBeat;
        float end = currentSoundFrame * 1.0f / soundFramesPerSecond;
        beatFrames.emplace_back(begin, end);

        if (currentSoundFrame >= soundInstance_->getDataSize())
            break;
    }
}

void BeatManager::onUpdate() {
    float currentSecond = soundInstance->getOffset() / soundInstance->getNumberOfChannels() * 1.0f / soundInstance->getSampleRate();

    if (currentSecond > beatFrames[currentFramIndex].end) {
        if ((size_t)currentFramIndex < beatFrames.size() - 1){
            currentFramIndex++;
        }
    }
}

BeatTimeFrame &BeatManager::getCurrentFrame() {
    return beatFrames[currentFramIndex];
}

float BeatManager::getCurrentOffset() {
    return abs(getCurrentFrame().middle - soundInstance->getCurrentRuntime());
}
