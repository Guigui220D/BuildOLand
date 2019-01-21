#pragma once

#include "LivingEntity.h"

class BlackWarrior : public LivingEntity {
public:
    BlackWarrior(World *world, unsigned id);

    inline void setDirection(unsigned char dir) { direction = dir; };

protected:
    std::string getTextureName() override;
    std::vector<sf::IntRect> getIdleAnim() override;
    std::vector<sf::IntRect> getNorthWalkAnim() override;
    std::vector<sf::IntRect> getSouthWalkAnim() override;
    std::vector<sf::IntRect> getEastWalkAnim() override;
    std::vector<sf::IntRect> getWestWalkAnim() override;

    void updateMovement(float dt) override;

    virtual std::vector<unsigned char> getBytes() override;

private:
    unsigned char direction = 0;
    unsigned char prevDir = 100;
    bool isInverse = false;
};



