#include <iostream>

#include "GameBoard.h"
#include "TestMapFactory.h"
#include "WorkerAnt.h"

int main() {
    auto board = TestMapFactory::create();
    WorkerAnt ant(1, 0);

    if (!ant.placeOnBoard(*board, 1, 1)) {
        std::cerr << "Cannot place WorkerAnt onto the board\n";
        return 1;
    }
    std::cout << "WorkerAnt " << ant.getId() << " at ("
              << ant.getX() << ", " << ant.getY() << ")\n";
    std::cout << "Movement to (2, 1): "
              << (ant.moveTo(2, 1) ? "OK" : "BLOCKED") << "\n";
    std::cout << "Position: (" << ant.getX() << ", " << ant.getY()
              << "), remaining AP: " << ant.getActionPoints() << "\n";
    return 0;
}
