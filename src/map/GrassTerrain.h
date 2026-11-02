#pragma once

#include "Terrain.h"

class GrassTerrain : public Terrain {
public:
    TerrainType getType() const override;
    std::string getName() const override;
    int getDefenseBonus() const override;
    int getMovementCost() const override;
    bool isPassableFor(UnitType unitType) const override;
};
