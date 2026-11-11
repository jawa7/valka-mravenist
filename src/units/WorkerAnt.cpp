#include "WorkerAnt.h"

WorkerAnt::WorkerAnt(int id, int ownerColonyId)
    : Unit(id, ownerColonyId, DefaultMaxHp, DefaultAttack,
           DefaultDefense, DefaultMovementRange, DefaultActionPoints) {}

UnitType WorkerAnt::getType() const noexcept {
    return UnitType::Worker;
}
