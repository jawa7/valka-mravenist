#include "Unit.h"

#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <stdexcept>
#include <tuple>
#include <vector>

#include "GameBoard.h"
#include "Tile.h"

Unit::Unit(int id, int ownerColonyId, int maxHp, int baseAttack,
           int baseDefense, int movementRange, int maxActionPoints)
    : m_id(id), m_ownerColonyId(ownerColonyId),
      m_currentHp(maxHp), m_maxHp(maxHp), m_baseAttack(baseAttack),
      m_baseDefense(baseDefense), m_movementRange(movementRange),
      m_actionPoints(maxActionPoints), m_maxActionPoints(maxActionPoints) {
    if (id < 0 || ownerColonyId < 0 || maxHp <= 0 || baseAttack < 0 ||
        baseDefense < 0 || movementRange < 0 || maxActionPoints < 0) {
        throw std::invalid_argument("Invalid unit identifier or statistics");
    }
}

Unit::~Unit() {
    removeFromBoard();
}

int Unit::getId() const noexcept { return m_id; }
int Unit::getOwnerColonyId() const noexcept { return m_ownerColonyId; }
int Unit::getCurrentHp() const noexcept { return m_currentHp; }
int Unit::getMaxHp() const noexcept { return m_maxHp; }
int Unit::getBaseAttack() const noexcept { return m_baseAttack; }
int Unit::getBaseDefense() const noexcept { return m_baseDefense; }
int Unit::getMovementRange() const noexcept { return m_movementRange; }
int Unit::getActionPoints() const noexcept { return m_actionPoints; }
int Unit::getMaxActionPoints() const noexcept { return m_maxActionPoints; }
bool Unit::isAlive() const noexcept { return m_currentHp > 0; }

bool Unit::hasValidPlacement() const noexcept {
    // Short-circuit before touching GameBoard*, which can already be dangling.
    return m_board != nullptr && !m_boardLifetime.expired() &&
           m_board->isValidPosition(m_x, m_y) &&
           m_board->getTile(m_x, m_y)->getUnit() == this;
}

bool Unit::isPlaced() const noexcept { return hasValidPlacement(); }
int Unit::getX() const noexcept { return isPlaced() ? m_x : -1; }
int Unit::getY() const noexcept { return isPlaced() ? m_y : -1; }

int Unit::getEffectiveDefense() const {
    if (!isPlaced()) {
        return m_baseDefense;
    }
    return m_baseDefense + m_board->getTile(m_x, m_y)->getTerrain().getDefenseBonus();
}

bool Unit::placeOnBoard(GameBoard& board, int x, int y) {
    if (!isAlive() || isPlaced() || !board.isValidPosition(x, y)) {
        return false;
    }
    Tile* target = board.getTile(x, y);
    if (target->isOccupied() ||
        !target->getTerrain().isPassableFor(getType())) {
        return false;
    }
    if (!target->placeUnit(this)) {
        return false;
    }

    m_board = &board;
    m_boardLifetime = board.getLifetimeToken();
    m_x = x;
    m_y = y;
    return true;
}

void Unit::removeFromBoard() noexcept {
    if (hasValidPlacement()) {
        m_board->getTile(m_x, m_y)->removeUnit();
    }
    m_board = nullptr;
    m_boardLifetime.reset();
    m_x = -1;
    m_y = -1;
}

int Unit::shortestPathCostTo(int targetX, int targetY) const {
    if (!hasValidPlacement() || !m_board->isValidPosition(targetX, targetY) ||
        (targetX == m_x && targetY == m_y)) {
        return -1;
    }

    const Tile* target = m_board->getTile(targetX, targetY);
    if (target->isOccupied() || !target->getTerrain().isPassableFor(getType())) {
        return -1;
    }

    using Node = std::tuple<int, int, int>; // cost, x, y
    std::priority_queue<Node, std::vector<Node>, std::greater<>> queue;
    const int width = m_board->getWidth();
    const auto index = [width](int x, int y) -> std::size_t {
        return static_cast<std::size_t>(y) * static_cast<std::size_t>(width) +
               static_cast<std::size_t>(x);
    };

    const std::size_t fieldCount =
        static_cast<std::size_t>(width) * static_cast<std::size_t>(m_board->getHeight());
    std::vector<int> costs(fieldCount, std::numeric_limits<int>::max());
    costs[index(m_x, m_y)] = 0;
    queue.emplace(0, m_x, m_y);

    while (!queue.empty()) {
        auto [cost, x, y] = queue.top();
        queue.pop();
        if (cost != costs[index(x, y)]) {
            continue;
        }
        if (x == targetX && y == targetY) {
            return cost;
        }

        for (Tile* next : m_board->getNeighbors(x, y)) {
            if (next->isOccupied() || !next->getTerrain().isPassableFor(getType())) {
                continue;
            }
            const int step = next->getTerrain().getMovementCost();
            // Treat malformed negative costs as impassable, and avoid overflow.
            if (step < 0 || step > m_movementRange - cost) {
                continue;
            }
            const int nextCost = cost + step;
            const std::size_t nextIndex = index(next->getX(), next->getY());
            if (nextCost < costs[nextIndex]) {
                costs[nextIndex] = nextCost;
                queue.emplace(nextCost, next->getX(), next->getY());
            }
        }
    }
    return -1;
}

bool Unit::canMoveTo(int x, int y) const {
    return isAlive() && m_actionPoints > 0 && shortestPathCostTo(x, y) >= 0;
}

bool Unit::moveTo(int x, int y) {
    if (!canMoveTo(x, y)) {
        return false;
    }

    Tile* source = m_board->getTile(m_x, m_y);
    Tile* destination = m_board->getTile(x, y);
    // Place first, so no state is lost if placement were unexpectedly rejected.
    if (!destination->placeUnit(this)) {
        return false;
    }
    if (source->removeUnit() != this) {
        // This should be impossible in single-threaded gameplay, but rollback.
        destination->removeUnit();
        return false;
    }
    m_x = x;
    m_y = y;
    --m_actionPoints;
    return true;
}

void Unit::takeDamage(int damage) {
    if (damage <= 0 || !isAlive()) {
        return;
    }
    m_currentHp -= std::min(damage, m_currentHp);
    if (!isAlive()) {
        m_actionPoints = 0;
        removeFromBoard();
    }
}

void Unit::resetActionPoints() noexcept {
    m_actionPoints = isAlive() ? m_maxActionPoints : 0;
}
