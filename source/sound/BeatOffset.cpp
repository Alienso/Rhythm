//
// Created by Alienson on 22.3.2025..
//

#include "BeatOffset.h"

BeatOffset* BeatOffset::MISS = new BeatOffset(0.25f, 0, 0.25f);
BeatOffset* BeatOffset::GOOD = new BeatOffset(1.0f, 1.0f, 1.0f);
BeatOffset* BeatOffset::PERFECT = new BeatOffset(1.0f, 1.5f, 1.0f);

BeatOffset::BeatOffset(float damageMultiplier, float comboMultiplier, float scoreMultiplier) : damageMultiplier(damageMultiplier), comboMultiplier(comboMultiplier), scoreMultiplier(scoreMultiplier) {

}

BeatOffset *BeatOffset::from(float beatOffset) {
    if (beatOffset < 0.01)
        return PERFECT;
    else if (beatOffset < 0.1)
        return GOOD;
    else return MISS;
}

void BeatOffset::cleanUp() {
    delete MISS;
    delete GOOD;
    delete PERFECT;
}
