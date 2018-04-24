#include "ItemAir.h"

ItemAir::ItemAir() : Item("AIR") {

}

bool ItemAir::isPlaceable() {
    return false;
}

bool ItemAir::isGround() {
    return false;
}
