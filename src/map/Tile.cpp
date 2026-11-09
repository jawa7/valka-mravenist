#include "Tile.h"

#include <stdexcept>
#include <utility>

Tile::Tile(int x, int y, std::unique_ptr<Terrain> terrain)
    : m_x(x), m_y(y), m_terrain(std::move(terrain)) {
    if (!m_terrain) {
        throw std::invalid_argument("Tile requires a terrain");
    }
}

int Tile::getX() const {
    return m_x;
}

int Tile::getY() const {
    return m_y;
}

const Terrain& Tile::getTerrain() const {
    return *m_terrain;
}

void Tile::setTerrain(std::unique_ptr<Terrain> terrain) {
    if (!terrain) {
        throw std::invalid_argument("Tile requires a terrain");
    }
    m_terrain = std::move(terrain);
}

Unit* Tile::getUnit() const {
    return m_unit;
}

Chamber* Tile::getChamber() const {
    return m_chamber;
}

bool Tile::hasUnit() const {
    return m_unit != nullptr;
}

bool Tile::hasChamber() const {
    return m_chamber != nullptr;
}

bool Tile::isOccupied() const {
    return hasUnit() || hasChamber();
}

bool Tile::placeUnit(Unit* unit) {
    if (unit == nullptr || isOccupied()) {
        return false;
    }
    m_unit = unit;
    return true;
}

Unit* Tile::removeUnit() {
    return std::exchange(m_unit, nullptr);
}

bool Tile::placeChamber(Chamber* chamber) {
    if (chamber == nullptr || isOccupied()) {
        return false;
    }
    m_chamber = chamber;
    return true;
}

Chamber* Tile::removeChamber() {
    return std::exchange(m_chamber, nullptr);
}
