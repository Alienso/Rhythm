//
// Created by Alienson on 10.8.2024..
//

#include "Player.h"
#include "reference/Global.h"
#include "physics/RayTrace.h"

std::array<RhythmMultiplier*, 5> RhythmMultiplier::levels = { new RhythmMultiplier(1,1,100),
                                                            new RhythmMultiplier(1,2,250),
                                                            new RhythmMultiplier(2,4,400),
                                                            new RhythmMultiplier(4,8,600),
                                                            new RhythmMultiplier(8,16,900) };

RhythmMultiplier::RhythmMultiplier(unsigned short damage, unsigned short score, unsigned int comboPointsRequired)
    : damage(damage), score(score), comboPointsRequired(comboPointsRequired){

}

void RhythmMultiplier::cleanUp() {
    for (RhythmMultiplier* level : RhythmMultiplier::levels){
        delete level;
    }
}

Player::Player() : EntityLiving(Textures::BIKER) {

    Global::physicsEngine->registerEntity(this);
    Global::player = this;
    speedModifier = 1.2f;

    sprite.scale = glm::vec2(0.1, 0.1);
    sprite.stateMachine = SpriteStateMachine(9, 8);
    sprite.stateMachine.setTexturesCount({6, 8, 6, 4, 6, 2, 4, 6, 6});
    commonStates[STATE_DEATH] = 2;
    commonStates[STATE_HURT] = 5;

    rebuildCollisionBoxes();

    collisionSprite.scale = { (collisionBB.maxX - collisionBB.minX) / 2.0f, (collisionBB.maxY - collisionBB.minY) / 2.0f };

}

Player::~Player() {
    delete currentWeapon; //TODO remove this once weapons are deleted from elsewhere
}

void Player::onUpdate(float deltaTime) {
    EntityLiving::onUpdate(deltaTime);
    currentWeapon->onUpdate(deltaTime, pos_);
    comboDecayTimer -= deltaTime;
    if (comboDecayTimer <= 0) {
        adjustComboPoints(-((float) Configuration::comboDecayAmount * deltaTime));
    }
}

void Player::onRender() const {
    Entity::onRender();
    currentWeapon->onRender();
}

void Player::rebuildCollisionBoxes() {
    collisionBB = {(pos_.x - 0.4533f * sprite.scale.x), pos_.y - 1.0f * sprite.scale.y,
                   (pos_.x + 0.4533f * sprite.scale.x), pos_.y + 0.4167f * sprite.scale.y};
    collisionSprite.translate = { (collisionBB.maxX + collisionBB.minX) / 2.0f, (collisionBB.maxY + collisionBB.minY) / 2.0f };
}

bool Player::canAttack() const {
    return currentWeapon->canAttack();
}

void Player::attack(BeatOffset* beatOffset) {
    currentWeapon->onAttack(beatOffset);
}

void Player::adjustComboPoints(float value) {
    comboPoints+= value;
    if (value > 0)
        resetBeatDecay();
    if (comboPoints < 0)
        comboPoints = 0;
    else if (comboPoints > RhythmMultiplier::levels[RhythmMultiplier::levels.size() - 1]->comboPointsRequired)
        comboPoints = RhythmMultiplier::levels[RhythmMultiplier::levels.size() - 1]->comboPointsRequired;
    if ((unsigned int)comboPoints < getRhythmMultiplier()->comboPointsRequired){
        if (rhythmMultiplierIndex != 0)
            rhythmMultiplierIndex--;
    }
    if ((unsigned int)comboPoints >= getNextRhythmMultiplier()->comboPointsRequired){
        rhythmMultiplierIndex++;
        if (rhythmMultiplierIndex > RhythmMultiplier::levels.size() - 1)
            rhythmMultiplierIndex = RhythmMultiplier::levels.size() - 1;
    }
}

RhythmMultiplier *Player::getRhythmMultiplier() const {
    assert(rhythmMultiplierIndex < RhythmMultiplier::levels.size());
    return RhythmMultiplier::levels[rhythmMultiplierIndex];
}
RhythmMultiplier *Player::getNextRhythmMultiplier() const {
    assert(rhythmMultiplierIndex < RhythmMultiplier::levels.size());
    if (rhythmMultiplierIndex == RhythmMultiplier::levels.size() - 1)
        return RhythmMultiplier::levels[rhythmMultiplierIndex];
    return RhythmMultiplier::levels[rhythmMultiplierIndex + 1];
}

void Player::resetBeatDecay() {
    comboDecayTimer = Configuration::comboDecayDelay;
}
