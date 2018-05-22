
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

    void updateMovement(double dt) override;

private:
    unsigned short direction = 0;
    unsigned short prevDir = 100;
    bool isInverse = false;
};



