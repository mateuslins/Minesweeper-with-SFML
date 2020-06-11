#include <iostream>
#include <ctime>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "UnderTile.h"
#include "UpperTile.h"
#include "Functions.h"

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

void initUpperGrid(std::vector<std::vector<UpperTile>>& upperTileMap, int mapSize, float topDistance, float rightDistance)
{
	upperTileMap.resize(mapSize, std::vector<UpperTile>()); // Resizing to (mapSize) vectors of UpperTiles (making the lines)

	for (int i = 0; i < mapSize; i++) {

		upperTileMap[i].resize(mapSize, UpperTile()); // Resizing to (mapSize) UpperTiles per vector (making the column)
		for (int j = 0; j < mapSize; j++) {

			upperTileMap[i][j].adjustPosition(i, j, topDistance, rightDistance);
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

void showAdjacents(std::vector<std::vector<UnderTile>>& underTileMap, std::vector<std::vector<UpperTile>>& upperTileMap, int i, int j, int mapSize)
{
	if (i - 1 >= 0 && j - 1 >= 0) {
		if (upperTileMap[i - 1][j - 1].getIsRemoved() == false) {
			upperTileMap[i - 1][j - 1].removeTile();
			if (underTileMap[i - 1][j - 1].getType() == 0)
				showAdjacents(underTileMap, upperTileMap, i - 1, j - 1, mapSize);
		}
	}

	if (j - 1 >= 0) {
		if (upperTileMap[i][j - 1].getIsRemoved() == false) {
			upperTileMap[i][j - 1].removeTile();
			if (underTileMap[i][j - 1].getType() == 0)
				showAdjacents(underTileMap, upperTileMap, i, j - 1, mapSize);
		}
	}

	if (i + 1 <= mapSize - 1 && j - 1 >= 0) {
		if (upperTileMap[i + 1][j - 1].getIsRemoved() == false) {
			upperTileMap[i + 1][j - 1].removeTile();
			if (underTileMap[i + 1][j - 1].getType() == 0)
				showAdjacents(underTileMap, upperTileMap, i + 1, j - 1, mapSize);
		}
	}

	if (i - 1 >= 0) {
		if (upperTileMap[i - 1][j].getIsRemoved() == false) {
			upperTileMap[i - 1][j].removeTile();
			if (underTileMap[i - 1][j].getType() == 0)
				showAdjacents(underTileMap, upperTileMap, i - 1, j, mapSize);
		}
	}

	if (i + 1 <= mapSize - 1) {
		if (upperTileMap[i + 1][j].getIsRemoved() == false) {
			upperTileMap[i + 1][j].removeTile();
			if (underTileMap[i + 1][j].getType() == 0)
				showAdjacents(underTileMap, upperTileMap, i + 1, j, mapSize);
		}
	}

	if (i - 1 >= 0 && j + 1 <= mapSize - 1) {
		if (upperTileMap[i - 1][j + 1].getIsRemoved() == false) {
			upperTileMap[i - 1][j + 1].removeTile();
			if (underTileMap[i - 1][j + 1].getType() == 0)
				showAdjacents(underTileMap, upperTileMap, i - 1, j + 1, mapSize);
		}
	}

	if (j + 1 <= mapSize - 1) {
		if (upperTileMap[i][j + 1].getIsRemoved() == false) {
			upperTileMap[i][j + 1].removeTile();
			if (underTileMap[i][j + 1].getType() == 0)
				showAdjacents(underTileMap, upperTileMap, i, j + 1, mapSize);
		}
	}

	if (i + 1 <= mapSize - 1 && j + 1 <= mapSize - 1) {
		if (upperTileMap[i + 1][j + 1].getIsRemoved() == false) {
			upperTileMap[i + 1][j + 1].removeTile();
			if (underTileMap[i + 1][j + 1].getType() == 0)
				showAdjacents(underTileMap, upperTileMap, i + 1, j + 1, mapSize);
		}
	}
}
