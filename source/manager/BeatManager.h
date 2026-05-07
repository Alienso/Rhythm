//
// Created by Vladimir Arsenijevic on 6.5.2026.
//

#ifndef RHYTHM_BEATMANAGER_H
#define RHYTHM_BEATMANAGER_H

#include <vector>
#include "sound/Sound.h"

// Create time frames for beats, but don't make boundaries based on beat to beat, but instead use middles between the two beats.
// This way, the middle of the timeframe is the beat itself, so calculating how offbeat something is, is how off the middle the button is pressed.
// Current beat is always the timeframe currently selected

class BeatTimeFrame {
public:
    BeatTimeFrame(float begin_, float end_) : begin(begin_), end(end_){
        middle = (end_ + begin_) / 2.0f;
    }
    float begin;
    float middle;
    float end;
};

class BeatManager {
public:
    static void buildBeatFrames(SoundInstance* soundInstance);
    static void onUpdate();
    static BeatTimeFrame& getCurrentFrame();
    static float getCurrentOffset();

private:
    BeatManager() = default;

    static inline SoundInstance* soundInstance = nullptr;
    static inline int currentFramIndex = 0;
    static inline std::vector<BeatTimeFrame> beatFrames = {};

};


#endif //RHYTHM_BEATMANAGER_H
