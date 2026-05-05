//
// Created by Vladimir Arsenijevic on 5.5.2026.
//

#include "RhythmMultiplier.h"

std::array<RhythmMultiplier*, 5> RhythmMultiplier::levels = {
        new RhythmMultiplier(1,1,100),
        new RhythmMultiplier(1,2,250),
        new RhythmMultiplier(2,4,400),
        new RhythmMultiplier(4,8,600),
        new RhythmMultiplier(8,16,900)
};

RhythmMultiplier::RhythmMultiplier(unsigned short damageMultiplier, unsigned short scoreMultiplier, unsigned int comboPointsRequired)
        : damageMultiplier(damageMultiplier), scoreMultiplier(scoreMultiplier), comboPointsRequired(comboPointsRequired){

}

void RhythmMultiplier::cleanUp() {
    for (RhythmMultiplier* level : RhythmMultiplier::levels){
        delete level;
    }
}

unsigned int RhythmMultiplier::getMaxComboPoints() {
    return RhythmMultiplier::levels[RhythmMultiplier::levels.size() - 1]->comboPointsRequired;
}