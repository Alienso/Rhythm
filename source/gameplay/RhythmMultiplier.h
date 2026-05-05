//
// Created by Vladimir Arsenijevic on 5.5.2026..
//

#ifndef RHYTHM_RHYTHMMULTIPLIER_H
#define RHYTHM_RHYTHMMULTIPLIER_H

#include <array>

class RhythmMultiplier{
public:
    RhythmMultiplier(unsigned short damageMultiplier, unsigned short scoreMultiplier, unsigned int comboPointsRequired);

    static void cleanUp();
    [[nodiscard]] static unsigned int getMaxComboPoints();

    unsigned short damageMultiplier;
    unsigned short scoreMultiplier;
    unsigned int comboPointsRequired;

    static std::array<RhythmMultiplier*, 5> levels;
};


#endif //RHYTHM_RHYTHMMULTIPLIER_H
