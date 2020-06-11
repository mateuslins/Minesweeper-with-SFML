#pragma once

void initGrid(std::vector<std::vector<UnderTile>> &underTileMap, int mapSize, float topDistance, float rightDistance);
void initBombs(int &bombsQuant, std::vector<std::vector<UnderTile>> &underTileMap, int mapSize);
void nearBombsCounter(std::vector<std::vector<UnderTile>> &underTileMap, int mapSize);