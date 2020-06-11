#include <iostream>
#include <ctime>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "UnderTile.h"

void initGrid(std::vector<std::vector<UnderTile>> &underTileMap, int mapSize, float topDistance, float rightDistance) {
	underTileMap.resize(mapSize, std::vector<UnderTile>()); //Resizing to (mapSize) vectors of UnderTiles (making a line)

	for (int i = 0; i < mapSize; i++) {

		underTileMap[i].resize(mapSize, UnderTile()); //Resizing to (mapSize) UnderTiles per vector (making column)
		for (int j = 0; j < mapSize; j++) {

			underTileMap[i][j].adjustPosition(i, j, topDistance, rightDistance);
			underTileMap[i][j].loadFont();
		}
	}
}

void initBombs(int &bombsQuant, std::vector<std::vector<UnderTile>> &underTileMap, int mapSize) {
	while (bombsQuant > 0) {

		int i = rand() % mapSize;
		int j = rand() % mapSize;

		if (underTileMap[i][j].getType() != 9) {

			underTileMap[i][j].plantBomb();
			bombsQuant--;
		}
	}
}

void nearBombsCounter(std::vector<std::vector<UnderTile>> &underTileMap, int mapSize) {
	for (int i = 0; i < mapSize; i++) {
		for (int j = 0; j < mapSize; j++) {

			if (underTileMap[i][j].getType() != 9) {

				if (i - 1 >= 0 && j - 1 >= 0) {
					if (underTileMap[i - 1][j - 1].getType() == 9)
						underTileMap[i][j].addOnType();
				}

				if (j - 1 >= 0) {
					if (underTileMap[i][j - 1].getType() == 9)
						underTileMap[i][j].addOnType();
				}

				if (i + 1 <= mapSize - 1 && j - 1 >= 0) {
					if (underTileMap[i + 1][j - 1].getType() == 9)
						underTileMap[i][j].addOnType();
				}

				if (i - 1 >= 0) {
					if (underTileMap[i - 1][j].getType() == 9)
						underTileMap[i][j].addOnType();
				}

				if (i + 1 <= mapSize - 1) {
					if (underTileMap[i + 1][j].getType() == 9)
						underTileMap[i][j].addOnType();
				}

				if (i - 1 >= 0 && j + 1 <= mapSize - 1) {
					if (underTileMap[i - 1][j + 1].getType() == 9)
						underTileMap[i][j].addOnType();
				}

				if (j + 1 <= mapSize - 1) {
					if (underTileMap[i][j + 1].getType() == 9)
						underTileMap[i][j].addOnType();
				}

				if (i + 1 <= mapSize - 1 && j + 1 <= mapSize - 1) {
					if (underTileMap[i + 1][j + 1].getType() == 9)
						underTileMap[i][j].addOnType();
				}
			}
		}
	}
}