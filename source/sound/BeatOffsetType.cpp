//
// Created by Alienson on 22.3.2025.
//

#include "BeatOffsetType.h"
#include "reference/Configuration.h"

BeatOffsetType* BeatOffsetType::MISS = new BeatOffsetType(0.25f, 0, 0.25f);
BeatOffsetType* BeatOffsetType::GOOD = new BeatOffsetType(1.0f, 1.0f, 1.0f);
BeatOffsetType* BeatOffsetType::PERFECT = new BeatOffsetType(1.0f, 1.5f, 1.0f);

BeatOffsetType::BeatOffsetType(float damageMultiplier, float comboMultiplier, float scoreMultiplier) : damageMultiplier(damageMultiplier), comboMultiplier(comboMultiplier), scoreMultiplier(scoreMultiplier) {

}

BeatOffsetType *BeatOffsetType::from(float beatOffset) {
    if (beatOffset < Configuration::allowedBeatOffsetPerfect)
        return PERFECT;
    else if (beatOffset < Configuration::allowedBeatOffsetGood)
        return GOOD;
    else return MISS;
}

void BeatOffsetType::cleanUp() {
    delete MISS;
    delete GOOD;
    delete PERFECT;
}
