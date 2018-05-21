#include "WornConcrete.h"
#include "../States/StateGame.h"

WornConcrete::WornConcrete(sf::IntRect textureRect, std::string name, sf::Color mapColor) : Ground(textureRect, name,
                                                                                                   mapColor) {

}

Ground *WornConcrete::getGroundOnBreak(StateGame *stateGame) {
    return stateGame->getTileset()->getGroundByName("CONCRETE");
}
