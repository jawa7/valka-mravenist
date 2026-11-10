#pragma once

#include <string>
#include "UnitType.h"

enum class TerrainType {
    Grass,
    Rock
};

class Terrain {
public:
    virtual ~Terrain() = default;

    virtual TerrainType getType() const = 0;
    virtual std::string getName() const = 0;
    virtual int getDefenseBonus() const = 0;
    virtual int getMovementCost() const = 0;
    virtual bool isPassableFor(UnitType unitType) const = 0;
};
