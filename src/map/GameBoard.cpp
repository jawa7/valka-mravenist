#include "GameBoard.h"

#include <array>
#include <stdexcept>
#include <utility>
#include "GrassTerrain.h"

GameBoard::GameBoard(int width, int height)
    : m_width(width), m_height(height) {
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Board dimensions must be positive");
    }
    m_tiles.resize(height);
    for (int y = 0; y < height; ++y) {
        m_tiles[y].reserve(width);
        for (int x = 0; x < width; ++x) {
            m_tiles[y].push_back(std::make_unique<Tile>(x, y, std::make_unique<GrassTerrain>()));
        }
    }
}

int GameBoard::getWidth() const {
    return m_width;
}

int GameBoard::getHeight() const {
    return m_height;
}

int GameBoard::getTileCount() const {
    return m_width * m_height;
}

bool GameBoard::isValidPosition(int x, int y) const {
    return x >= 0 && x < m_width && y >= 0 && y < m_height;
}

Tile* GameBoard::getTile(int x, int y) {
    if (!isValidPosition(x, y)) {
        throw std::out_of_range("Position is outside the board");
    }
    return m_tiles[y][x].get();
}

const Tile* GameBoard::getTile(int x, int y) const {
    if (!isValidPosition(x, y)) {
        throw std::out_of_range("Position is outside the board");
    }
    return m_tiles[y][x].get();
}

Tile* GameBoard::getTileAt(int index) {
    if (index < 0 || index >= getTileCount()) {
        throw std::out_of_range("Tile index is outside the board");
    }
    return getTile(index % m_width, index / m_width);
}

std::vector<Tile*> GameBoard::getNeighbors(int x, int y) {
    static const std::array<std::pair<int, int>, 4> directions{{
        {0, -1}, {1, 0}, {0, 1}, {-1, 0}
    }};

    if (!isValidPosition(x, y)) {
        throw std::out_of_range("Position is outside the board");
    }

    std::vector<Tile*> neighbors;
    for (const auto& [dx, dy] : directions) {
        if (isValidPosition(x + dx, y + dy)) {
            neighbors.push_back(getTile(x + dx, y + dy));
        }
    }
    return neighbors;
}

void GameBoard::setTerrain(int x, int y, std::unique_ptr<Terrain> terrain) {
    getTile(x, y)->setTerrain(std::move(terrain));
}
