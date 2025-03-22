//
// Created by Alienson on 22.3.2025..
//

#ifndef RHYTHM_BEATOFFSET_H
#define RHYTHM_BEATOFFSET_H


class BeatOffset{

public:
    [[nodiscard]] static BeatOffset* from(float beatOffset);
    static void cleanUp();

    static BeatOffset* MISS;
    static BeatOffset* GOOD;
    static BeatOffset* PERFECT;

    float damageMultiplier;
    float comboMultiplier;
    float scoreMultiplier;

private:
    BeatOffset(float damageMultiplier, float comboMultiplier, float scoreMultiplier);
};



#endif //RHYTHM_BEATOFFSET_H
