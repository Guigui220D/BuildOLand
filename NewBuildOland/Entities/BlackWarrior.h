
#pragma once


#include "LivingEntity.h"

class BlackWarrior : public LivingEntity {
public:
    BlackWarrior(World *world, unsigned id);
protected:
    std::string getTextureName() override;
    std::vector<IntRect> getIdleAnim() override;
    std::vector<IntRect> getNorthWalkAnim() override;
    std::vector<IntRect> getSouthWalkAnim() override;
    std::vector<IntRect> getEastWalkAnim() override;
    std::vector<IntRect> getWestWalkAnim() override;

    void updateMovement(float dt) override;

    virtual BlackWarrior* clone() const { return new BlackWarrior(*this); };

    virtual std::vector<unsigned char> getBytes() override;

private:
    unsigned char direction = 0;
    unsigned char prevDir = 100;
    bool isInverse = false;
};



