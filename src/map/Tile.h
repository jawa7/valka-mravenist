#pragma once

#include <memory>
#include "Terrain.h"

class Unit;
class Chamber;

class Tile {
private:
    int m_x;
    int m_y;
    std::unique_ptr<Terrain> m_terrain;
    Unit* m_unit = nullptr;
    Chamber* m_chamber = nullptr;

public:
    Tile(int x, int y, std::unique_ptr<Terrain> terrain);

    int getX() const;
    int getY() const;

    const Terrain& getTerrain() const;
    void setTerrain(std::unique_ptr<Terrain> terrain);

    Unit* getUnit() const;
    Chamber* getChamber() const;

    bool hasUnit() const;
    bool hasChamber() const;
    bool isOccupied() const;

    bool placeUnit(Unit* unit);
    Unit* removeUnit();

    bool placeChamber(Chamber* chamber);
    Chamber* removeChamber();
};
