#pragma once

#include "Unit.h"

// First playable ant caste. These are provisional balancing defaults because
// the assignment does not specify numerical values; adjust here when agreed.
class WorkerAnt final : public Unit {
public:
    static constexpr int DefaultMaxHp = 10;
    static constexpr int DefaultAttack = 2;
    static constexpr int DefaultDefense = 1;
    static constexpr int DefaultMovementRange = 3;
    static constexpr int DefaultActionPoints = 2;

    WorkerAnt(int id, int ownerColonyId);

    [[nodiscard]] UnitType getType() const noexcept override;
};
