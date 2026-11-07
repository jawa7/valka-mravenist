#pragma once

#include <memory>
#include <vector>
#include "Tile.h"

class GameBoard {
private:
    int m_width;
    int m_height;
    std::vector<std::vector<std::unique_ptr<Tile>>> m_tiles;

public:
    GameBoard(int width, int height);

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
