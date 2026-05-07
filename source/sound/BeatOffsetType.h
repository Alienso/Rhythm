//
// Created by Alienson on 22.3.2025..
//

#ifndef RHYTHM_BEATOFFSETTYPE_H
#define RHYTHM_BEATOFFSETTYPE_H


class BeatOffsetType{

public:
    [[nodiscard]] static BeatOffsetType* from(float beatOffset);
    static void cleanUp();

    static BeatOffsetType* MISS;
    static BeatOffsetType* GOOD;
    static BeatOffsetType* PERFECT;

    float damageMultiplier;
    float comboMultiplier;
    float scoreMultiplier;

private:
    BeatOffsetType(float damageMultiplier, float comboMultiplier, float scoreMultiplier);
};



#endif //RHYTHM_BEATOFFSETTYPE_H
