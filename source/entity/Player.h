//
// Created by Alienson on 10.8.2024..
//

#ifndef RHYTHM_PLAYER_H
#define RHYTHM_PLAYER_H


#include "EntityLiving.h"
#include "reference/Reference.h"
#include "weapon/RangedWeaponBase.h"
#include "weapon/PistolWeapon.h"
#include "sound/BeatOffset.h"

class Rhythm;

class RhythmMultiplier{
public:
    RhythmMultiplier(unsigned short damage, unsigned short score, unsigned int comboPointsRequired);
    static void cleanUp();

    unsigned short damage;
    unsigned short score;
    unsigned int comboPointsRequired;

    static std::array<RhythmMultiplier*, 5> levels;
};

class Player : public EntityLiving{

public:
    Player();
    ~Player() override = default;

    void onUpdate(float deltaTime) override;
    void onRender() const override;

    [[nodiscard]] bool canAttack() const;
    void attack(BeatOffset* beatOffset);
    void increaseComboPoints(float value);
    [[nodiscard]] RhythmMultiplier* getRhythmMultiplier() const;
    [[nodiscard]] RhythmMultiplier* getNextRhythmMultiplier() const;

    RangedWeaponBase* weapon = new PistolWeapon();

private:
    float comboDecayTimer = 0;
    float comboPoints = 0.0f;
    unsigned int rhythmMultiplierIndex = 0;

    void resetBeatDecay();

    friend Rhythm;

};


#endif //RHYTHM_PLAYER_H
