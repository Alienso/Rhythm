//
// Created by Alienson on 10.8.2024..
//

#ifndef RHYTHM_PLAYER_H
#define RHYTHM_PLAYER_H


#include "EntityLiving.h"
#include "reference/Reference.h"
#include "weapon/WeaponBase.h"
#include "weapon/PistolWeapon.h"
#include "sound/BeatOffset.h"

#include "gameplay/RhythmMultiplier.h"

class Rhythm; //For debugging purposes

class Player : public EntityLiving {

public:
    Player();

    void onUpdate(float deltaTime) override;
    void onRender() const override;

    [[nodiscard]] bool canAttack() const;
    void attack(BeatOffset* beatOffset);
    void adjustComboPoints(float value);
    [[nodiscard]] RhythmMultiplier* getCurrentRhythmMultiplier() const;
    [[nodiscard]] RhythmMultiplier* getNextRhythmMultiplier() const;

    WeaponBase* currentWeapon;

protected:
    void rebuildCollisionBoxes() override;

private:
    float comboDecayTimer = 0;
    float comboPoints = 0.0f;
    unsigned int rhythmMultiplierIndex = 0;

    void resetBeatDecayTimer();

    friend Rhythm; //For debugging purposes

};


#endif //RHYTHM_PLAYER_H
