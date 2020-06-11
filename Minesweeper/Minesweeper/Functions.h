#pragma once

void initGrid(std::vector<std::vector<UnderTile>> &underTileMap, int mapSize, float topDistance, float rightDistance);
void initUpperGrid(std::vector<std::vector<UpperTile>> &upperTileMap, int mapSize, float topDistance, float rightDistance);
void initBombs(int &bombsQuant, std::vector<std::vector<UnderTile>> &underTileMap, int mapSize);
void nearBombsCounter(std::vector<std::vector<UnderTile>> &underTileMap, int mapSize);
void showAdjacents(std::vector<std::vector<UnderTile>> &underTileMap, std::vector<std::vector<UpperTile>> &upperTileMap, int i, int j, int mapSize);