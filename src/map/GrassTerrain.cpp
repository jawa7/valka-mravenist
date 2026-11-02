#include "GrassTerrain.h"

TerrainType GrassTerrain::getType() const {
    return TerrainType::Grass;
}

std::string GrassTerrain::getName() const {
    return "Tráva";
}

int GrassTerrain::getDefenseBonus() const {
    return 0;
}

int GrassTerrain::getMovementCost() const {
    return 1;
}

bool GrassTerrain::isPassableFor(UnitType) const {
    return true;
}
