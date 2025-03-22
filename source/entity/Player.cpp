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

RhythmMultiplier::RhythmMultiplier(unsigned short damage, unsigned short score, unsigned int comboPointsRequired) : damage(damage), score(score), comboPointsRequired(comboPointsRequired){

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

    collisionBB = {(pos.x - 0.4533f * sprite.scale.x), pos.y - 1.0f * sprite.scale.y,
                   (pos.x + 0.4533f * sprite.scale.x), pos.y + 0.4167f * sprite.scale.y};

    collisionSprite.scale = { (collisionBB.maxX - collisionBB.minX) / 2.0f, (collisionBB.maxY - collisionBB.minY) / 2.0f };
    collisionSprite.translate = { (collisionBB.maxX + collisionBB.minX) / 2.0f, (collisionBB.maxY + collisionBB.minY) / 2.0f };

}

void Player::onUpdate(float deltaTime) {
    EntityLiving::onUpdate(deltaTime);
    weapon->onUpdate(deltaTime, pos);
    if (comboDecayTimer <= 0) {
        comboDecayTimer -= deltaTime;
        increaseComboPoints(-(Configuration::comboDecayAmount * deltaTime));
    }
}

void Player::onRender() const {
    Entity::onRender();
    weapon->onRender();
}

bool Player::canAttack() const {
    return weapon->canAttack();
}

void Player::attack(BeatOffset* beatOffset) {
    weapon->onAttack(beatOffset);
}

void Player::increaseComboPoints(float value) {
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
