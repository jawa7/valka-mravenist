#pragma once

#include <memory>

#include "UnitType.h"

class GameBoard;

// Base class for every ant/unit.  Unit is non-owning with respect to GameBoard:
// the board holds Tile objects, while the colony/other gameplay layer owns units.
class Unit {
public:
    Unit(int id, int ownerColonyId, int maxHp, int baseAttack,
         int baseDefense, int movementRange, int maxActionPoints);
    virtual ~Unit();

    Unit(const Unit&) = delete;
    Unit& operator=(const Unit&) = delete;
    Unit(Unit&&) = delete;
    Unit& operator=(Unit&&) = delete;

    [[nodiscard]] virtual UnitType getType() const noexcept = 0;

    [[nodiscard]] int getId() const noexcept;
    [[nodiscard]] int getOwnerColonyId() const noexcept;
    [[nodiscard]] int getCurrentHp() const noexcept;
    [[nodiscard]] int getMaxHp() const noexcept;
    [[nodiscard]] int getBaseAttack() const noexcept;
    [[nodiscard]] int getBaseDefense() const noexcept;
    [[nodiscard]] int getEffectiveDefense() const;
    [[nodiscard]] int getMovementRange() const noexcept;
    [[nodiscard]] int getActionPoints() const noexcept;
    [[nodiscard]] int getMaxActionPoints() const noexcept;
    [[nodiscard]] bool isAlive() const noexcept;
    [[nodiscard]] bool isPlaced() const noexcept;
    // -1 means the unit is not on a currently existing game board.
    [[nodiscard]] int getX() const noexcept;
    [[nodiscard]] int getY() const noexcept;

    // Spawn is free (no action points spent). Refuses occupied, impassable,
    // out-of-range positions, dead units, or units already on a board.
    [[nodiscard]] bool placeOnBoard(GameBoard& board, int x, int y);
    // Clear a unit's tile without destroying it; also called by ~Unit().
    void removeFromBoard() noexcept;

    // Movement uses four-directional Dijkstra pathfinding with the terrain's
    // movement costs. A move costs exactly one action point, and the total
    // terrain cost of the path cannot exceed movementRange. Occupied tiles
    // (units/chambers) cannot be crossed or entered.
    [[nodiscard]] virtual bool canMoveTo(int x, int y) const;
    [[nodiscard]] virtual bool moveTo(int x, int y);

    // Damage has already been calculated by the combat system. This method
    // only applies the final nonnegative amount (no double-counting defense).
    // On death the unit is removed from the board and cannot act further.
    virtual void takeDamage(int damage);
    virtual void resetActionPoints() noexcept;

private:
    [[nodiscard]] bool hasValidPlacement() const noexcept;
    [[nodiscard]] int shortestPathCostTo(int targetX, int targetY) const;

    const int m_id;
    const int m_ownerColonyId;
    int m_currentHp;
    const int m_maxHp;
    const int m_baseAttack;
    const int m_baseDefense;
    const int m_movementRange;
    int m_actionPoints;
    const int m_maxActionPoints;

    GameBoard* m_board = nullptr;                 // never dereference if token expired
    std::weak_ptr<void> m_boardLifetime;
    int m_x = -1;
    int m_y = -1;
};
