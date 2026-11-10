#include "RockTerrain.h"

TerrainType RockTerrain::getType() const {
    return TerrainType::Rock;
}

std::string RockTerrain::getName() const {
    return "Kamení";
}

int RockTerrain::getDefenseBonus() const {
    return 1;
}

int RockTerrain::getMovementCost() const {
    return 2;
}

bool RockTerrain::isPassableFor(UnitType unitType) const {
    return unitType != UnitType::WaterBeetle;
}
