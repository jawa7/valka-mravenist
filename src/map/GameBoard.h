#pragma once

#include <memory>
#include <vector>
#include "Tile.h"

class GameBoard {
private:
    int m_width;
    int m_height;
    std::vector<std::vector<std::unique_ptr<Tile>>> m_tiles;
    // Destroyed before m_tiles: units can detect a destroyed board safely.
    std::shared_ptr<void> m_lifetimeToken = std::make_shared<int>(0);

public:
    GameBoard(int width, int height);
    GameBoard(const GameBoard&) = delete;
    GameBoard& operator=(const GameBoard&) = delete;
    GameBoard(GameBoard&&) = delete;
    GameBoard& operator=(GameBoard&&) = delete;

    // Non-owning lifetime guard for units referencing tiles on this board.
    [[nodiscard]] std::weak_ptr<void> getLifetimeToken() const noexcept;

    int getWidth() const;
    int getHeight() const;
    int getTileCount() const;

    bool isValidPosition(int x, int y) const;

    Tile* getTile(int x, int y);
    const Tile* getTile(int x, int y) const;
    Tile* getTileAt(int index);

    std::vector<Tile*> getNeighbors(int x, int y);

    void setTerrain(int x, int y, std::unique_ptr<Terrain> terrain);
};
