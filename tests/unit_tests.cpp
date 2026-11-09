#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>

#include "GameBoard.h"
#include "RockTerrain.h"
#include "WorkerAnt.h"

// Explicit checks also run in Release builds (where assert() is disabled).
#define CHECK(condition) do { \
    if (!(condition)) { \
        throw std::runtime_error(std::string(__FILE__) + ":" + \
            std::to_string(__LINE__) + " failed: " #condition); \
    } \
} while (false)

class Chamber {};

class TestUnit final : public Unit {
public:
    TestUnit(int id, int colony, UnitType kind, int hp = 10,
             int attack = 1, int defense = 1, int range = 3, int ap = 2)
        : Unit(id, colony, hp, attack, defense, range, ap), kind_(kind) {}
    UnitType getType() const noexcept override { return kind_; }
private:
    UnitType kind_;
};

static_assert(std::is_abstract_v<Unit>);
static_assert(!std::is_copy_constructible_v<WorkerAnt>);
static_assert(!std::is_move_constructible_v<WorkerAnt>);

static void testStatsAndType() {
    WorkerAnt ant(42, 3);
    CHECK(ant.getId() == 42);
    CHECK(ant.getOwnerColonyId() == 3);
    CHECK(ant.getType() == UnitType::Worker);
    CHECK(ant.getMaxHp() == WorkerAnt::DefaultMaxHp);
    CHECK(ant.getCurrentHp() == ant.getMaxHp());
    CHECK(ant.getBaseAttack() == WorkerAnt::DefaultAttack);
    CHECK(ant.getBaseDefense() == WorkerAnt::DefaultDefense);
    CHECK(ant.getEffectiveDefense() == WorkerAnt::DefaultDefense);
    CHECK(ant.getMovementRange() == WorkerAnt::DefaultMovementRange);
    CHECK(ant.getActionPoints() == WorkerAnt::DefaultActionPoints);
    CHECK(ant.getMaxActionPoints() == WorkerAnt::DefaultActionPoints);
    CHECK(ant.isAlive());
    CHECK(!ant.isPlaced());
    CHECK(ant.getX() == -1 && ant.getY() == -1);
}

static void testInvalidStats() {
    auto rejects = [](int id, int colony, int hp, int attack, int defense,
                      int range, int ap) {
        try {
            TestUnit invalid(id, colony, UnitType::Worker, hp, attack, defense,
                             range, ap);
        } catch (const std::invalid_argument&) {
            return true;
        }
        return false;
    };
    CHECK(rejects(-1, 0, 10, 1, 1, 2, 1));
    CHECK(rejects(0, -1, 10, 1, 1, 2, 1));
    CHECK(rejects(0, 0, 0, 1, 1, 2, 1));
    CHECK(rejects(0, 0, 10, -1, 1, 2, 1));
    CHECK(rejects(0, 0, 10, 1, -1, 2, 1));
    CHECK(rejects(0, 0, 10, 1, 1, -1, 1));
    CHECK(rejects(0, 0, 10, 1, 1, 2, -1));
    CHECK(!rejects(0, 0, 10, 0, 0, 0, 0));
}

static void testPlacementAndOccupancy() {
    GameBoard board(3, 2);
    WorkerAnt ant(1, 0);
    WorkerAnt other(2, 1);
    CHECK(!ant.placeOnBoard(board, -1, 0));
    CHECK(!ant.placeOnBoard(board, 3, 0));
    CHECK(!ant.placeOnBoard(board, 0, 2));
    CHECK(ant.placeOnBoard(board, 0, 0));
    CHECK(ant.isPlaced());
    CHECK(ant.getX() == 0 && ant.getY() == 0);
    CHECK(board.getTile(0, 0)->getUnit() == &ant);
    CHECK(ant.getActionPoints() == ant.getMaxActionPoints());
    CHECK(!ant.placeOnBoard(board, 2, 0));
    CHECK(!other.placeOnBoard(board, 0, 0));
    CHECK(other.placeOnBoard(board, 1, 0));
    CHECK(!ant.canMoveTo(1, 0));
    CHECK(!ant.moveTo(1, 0));
    CHECK(ant.getActionPoints() == ant.getMaxActionPoints());
    other.removeFromBoard();
    CHECK(!other.isPlaced());
    CHECK(board.getTile(1, 0)->getUnit() == nullptr);
    CHECK(ant.canMoveTo(1, 0));
    ant.removeFromBoard();
    CHECK(!ant.isPlaced());
    CHECK(board.getTile(0, 0)->getUnit() == nullptr);
    CHECK(ant.placeOnBoard(board, 2, 1));
}

static void testChamberAndTerrainBlocking() {
    GameBoard board(4, 1);
    WorkerAnt ant(1, 0);
    Chamber chamber;
    CHECK(board.getTile(1, 0)->placeChamber(&chamber));
    CHECK(!ant.placeOnBoard(board, 1, 0));
    CHECK(ant.placeOnBoard(board, 0, 0));
    CHECK(!ant.canMoveTo(2, 0)); // Cannot pass through chamber.
    CHECK(!ant.canMoveTo(1, 0));
    CHECK(ant.getX() == 0);

    GameBoard rockyBoard(2, 1);
    rockyBoard.setTerrain(1, 0, std::make_unique<RockTerrain>());
    TestUnit beetle(4, 0, UnitType::WaterBeetle);
    CHECK(!beetle.placeOnBoard(rockyBoard, 1, 0));
    CHECK(beetle.placeOnBoard(rockyBoard, 0, 0));
    CHECK(!beetle.canMoveTo(1, 0));
    WorkerAnt worker(5, 0);
    CHECK(worker.placeOnBoard(rockyBoard, 1, 0));
}

static void testMovementAndActionPoints() {
    GameBoard board(7, 7);
    WorkerAnt ant(1, 0);
    CHECK(ant.placeOnBoard(board, 1, 1));
    CHECK(!ant.canMoveTo(1, 1));
    CHECK(!ant.canMoveTo(4, 4)); // Manhattan distance 6 > range 3.
    CHECK(!ant.canMoveTo(-1, 1));
    CHECK(!ant.canMoveTo(7, 1));
    CHECK(ant.canMoveTo(3, 1));
    CHECK(ant.moveTo(3, 1));
    CHECK(board.getTile(1, 1)->getUnit() == nullptr);
    CHECK(board.getTile(3, 1)->getUnit() == &ant);
    CHECK(ant.getX() == 3 && ant.getY() == 1);
    CHECK(ant.getActionPoints() == ant.getMaxActionPoints() - 1);
    CHECK(ant.moveTo(3, 3));
    CHECK(ant.getActionPoints() == 0);
    CHECK(!ant.canMoveTo(3, 4));
    CHECK(!ant.moveTo(3, 4));
    CHECK(ant.getX() == 3 && ant.getY() == 3);
    ant.resetActionPoints();
    CHECK(ant.getActionPoints() == ant.getMaxActionPoints());
    CHECK(ant.moveTo(3, 4));
}

static void testWeightedTerrainAndDefense() {
    GameBoard board(5, 3);
    board.setTerrain(1, 1, std::make_unique<RockTerrain>());
    WorkerAnt ant(1, 0);
    CHECK(ant.placeOnBoard(board, 0, 1));
    CHECK(ant.getEffectiveDefense() == ant.getBaseDefense());
    CHECK(ant.canMoveTo(1, 1)); // Rock costs 2 (range 3).
    CHECK(ant.moveTo(1, 1));
    CHECK(ant.getEffectiveDefense() == ant.getBaseDefense() + 1);
    CHECK(ant.canMoveTo(3, 1)); // Two grass fields: cost 2, within range.
}

static void testPathfindingCannotJumpObstacles() {
    GameBoard board(3, 2);
    WorkerAnt ant(1, 0);
    WorkerAnt blockerA(2, 0);
    WorkerAnt blockerB(3, 0);
    CHECK(ant.placeOnBoard(board, 0, 0));
    CHECK(blockerA.placeOnBoard(board, 1, 0));
    CHECK(blockerB.placeOnBoard(board, 1, 1));
    CHECK(!ant.canMoveTo(2, 0));
    CHECK(!ant.moveTo(2, 0));
    CHECK(board.getTile(0, 0)->getUnit() == &ant);
    blockerB.removeFromBoard();
    CHECK(!ant.canMoveTo(2, 0)); // Detour costs 4; range is only 3.
    blockerA.removeFromBoard();
    CHECK(ant.canMoveTo(2, 0));
    CHECK(ant.moveTo(2, 0));
}

static void testRockPenaltyMakesTripUnreachable() {
    GameBoard board(3, 1);
    board.setTerrain(1, 0, std::make_unique<RockTerrain>());
    board.setTerrain(2, 0, std::make_unique<RockTerrain>());
    WorkerAnt ant(1, 0);
    CHECK(ant.placeOnBoard(board, 0, 0));
    CHECK(ant.canMoveTo(1, 0));
    CHECK(!ant.canMoveTo(2, 0)); // 2+2 = 4, beyond movementRange 3.
}

static void testDamageAndDeath() {
    GameBoard board(2, 2);
    WorkerAnt ant(1, 0);
    CHECK(ant.placeOnBoard(board, 0, 0));
    ant.takeDamage(-10);
    ant.takeDamage(0);
    CHECK(ant.getCurrentHp() == ant.getMaxHp());
    ant.takeDamage(3);
    CHECK(ant.getCurrentHp() == ant.getMaxHp() - 3);
    CHECK(ant.isAlive());
    CHECK(ant.isPlaced());
    ant.takeDamage(1000000);
    CHECK(ant.getCurrentHp() == 0);
    CHECK(!ant.isAlive());
    CHECK(!ant.isPlaced());
    CHECK(board.getTile(0, 0)->getUnit() == nullptr);
    CHECK(ant.getActionPoints() == 0);
    CHECK(!ant.placeOnBoard(board, 1, 1));
    CHECK(!ant.moveTo(1, 1));
    ant.resetActionPoints();
    CHECK(ant.getActionPoints() == 0);
    ant.takeDamage(1);
    CHECK(ant.getCurrentHp() == 0);
}

static void testLifetimeAndReassignment() {
    GameBoard board(3, 3);
    {
        auto ant = std::make_unique<WorkerAnt>(1, 0);
        CHECK(ant->placeOnBoard(board, 0, 0));
        CHECK(!ant->placeOnBoard(board, 1, 0));
    }
    CHECK(board.getTile(0, 0)->getUnit() == nullptr); // Destructor cleans tile.

    auto ant = std::make_unique<WorkerAnt>(2, 0);
    {
        auto temporary = std::make_unique<GameBoard>(2, 2);
        CHECK(ant->placeOnBoard(*temporary, 1, 1));
    }
    CHECK(!ant->isPlaced());  // Board died first: no invalid dereference.
    CHECK(ant->getX() == -1);
    CHECK(!ant->moveTo(0, 0));
    CHECK(ant->placeOnBoard(board, 1, 1));
    CHECK(ant->getX() == 1 && ant->getY() == 1);
}

int main() {
    try {
        testStatsAndType();
        testInvalidStats();
        testPlacementAndOccupancy();
        testChamberAndTerrainBlocking();
        testMovementAndActionPoints();
        testWeightedTerrainAndDefense();
        testPathfindingCannotJumpObstacles();
        testRockPenaltyMakesTripUnreachable();
        testDamageAndDeath();
        testLifetimeAndReassignment();
        std::cout << "All 10 unit test groups passed\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
