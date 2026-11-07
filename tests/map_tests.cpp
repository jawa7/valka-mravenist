#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "GameBoard.h"
#include "RockTerrain.h"
#include "TestMapFactory.h"

class Unit {};
class Chamber {};

static void testBoardInitialization() {
    GameBoard board(5, 4);
    assert(board.getWidth() == 5);
    assert(board.getHeight() == 4);
    assert(board.getTileCount() == 20);
    assert(board.getTile(0, 0)->getTerrain().getType() == TerrainType::Grass);
    assert(board.getTile(4, 3)->getX() == 4);
    assert(board.getTile(4, 3)->getY() == 3);
}

static void testPositionValidation() {
    GameBoard board(5, 4);
    assert(board.isValidPosition(0, 0));
    assert(board.isValidPosition(4, 3));
    assert(!board.isValidPosition(-1, 0));
    assert(!board.isValidPosition(5, 0));
    assert(!board.isValidPosition(0, 4));
}

static void testNeighbors() {
    GameBoard board(5, 4);
    assert(board.getNeighbors(0, 0).size() == 2);
    assert(board.getNeighbors(2, 0).size() == 3);
    assert(board.getNeighbors(2, 2).size() == 4);
}

static void testTerrainChange() {
    GameBoard board(3, 3);
    board.setTerrain(1, 1, std::make_unique<RockTerrain>());
    const Terrain& terrain = board.getTile(1, 1)->getTerrain();
    assert(terrain.getType() == TerrainType::Rock);
    assert(terrain.getMovementCost() == 2);
    assert(terrain.getDefenseBonus() == 1);
    assert(!terrain.isPassableFor(UnitType::WaterBeetle));
    assert(terrain.isPassableFor(UnitType::Worker));
}

static void testOccupancy() {
    GameBoard board(3, 3);
    Tile* tile = board.getTile(1, 1);
    Unit unit;
    Unit otherUnit;
    Chamber chamber;

    assert(!tile->isOccupied());
    assert(tile->placeUnit(&unit));
    assert(!tile->placeUnit(&otherUnit));
    assert(!tile->placeChamber(&chamber));
    assert(tile->removeUnit() == &unit);
    assert(!tile->isOccupied());
    assert(tile->placeChamber(&chamber));
    assert(tile->hasChamber());
}

static void testFactoryMap() {
    auto board = TestMapFactory::create();
    assert(board->getWidth() == 10);
    assert(board->getHeight() == 8);
    assert(board->getTile(3, 2)->getTerrain().getType() == TerrainType::Rock);
    assert(board->getTile(0, 0)->getTerrain().getType() == TerrainType::Grass);
}

int main() {
    testBoardInitialization();
    testPositionValidation();
    testNeighbors();
    testTerrainChange();
    testOccupancy();
    testFactoryMap();
    std::cout << "All map tests passed\n";
    return 0;
}
