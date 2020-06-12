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

			underTileMap[i][j].adjustPosition(i, j, mapSize, topDistance, rightDistance);
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

			upperTileMap[i][j].adjustPosition(i, j, mapSize, topDistance, rightDistance);
		}
	}
}

void initBombs(int &bombsQuant, std::vector<std::vector<UnderTile>> &underTileMap, int mapSize, int x, int y) {

	if (x - 1 >= 0 && y - 1 >= 0) {
		underTileMap[x - 1][y - 1].setIsNearFirstTrue();
	}

	if (y - 1 >= 0) {
		underTileMap[x][y - 1].setIsNearFirstTrue();
	}

	if (x + 1 <= mapSize - 1 && y - 1 >= 0) {
		underTileMap[x + 1][y - 1].setIsNearFirstTrue();
	}

	if (x - 1 >= 0) {
		underTileMap[x - 1][y].setIsNearFirstTrue();
	}

	if (x + 1 <= mapSize - 1) {
		underTileMap[x + 1][y].setIsNearFirstTrue();
	}

	if (x - 1 >= 0 && y + 1 <= mapSize - 1) {
		underTileMap[x - 1][y + 1].setIsNearFirstTrue();
	}

	if (y + 1 <= mapSize - 1) {
		underTileMap[x][y + 1].setIsNearFirstTrue();
	}

	if (x + 1 <= mapSize - 1 && x + 1 <= mapSize - 1) {
		underTileMap[x + 1][y + 1].setIsNearFirstTrue();
	}

	while (bombsQuant > 0) {

		int i = rand() % mapSize;
		int j = rand() % mapSize;

		if (underTileMap[i][j].getType() != 9 && underTileMap[i][j].getType() != 10 && underTileMap[i][j].getIsNearFirst() == false) {

			underTileMap[i][j].plantBomb();
			bombsQuant--;
		}
	}
}

void nearBombsCounter(std::vector<std::vector<UnderTile>> &underTileMap, int mapSize) {
	for (int i = 0; i < mapSize; i++) {
		for (int j = 0; j < mapSize; j++) {

			if (underTileMap[i][j].getType() != 9 && underTileMap[i][j].getType() != 10) {

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

void showAdjacents(std::vector<std::vector<UnderTile>>& underTileMap, std::vector<std::vector<UpperTile>>& upperTileMap, int i, int j, int mapSize, int& safeTiles)
{
	if (i - 1 >= 0 && j - 1 >= 0) {
		if (upperTileMap[i - 1][j - 1].getIsRemoved() == false) {
			upperTileMap[i - 1][j - 1].removeTile(safeTiles);
			if (underTileMap[i - 1][j - 1].getType() == 0)
				showAdjacents(underTileMap, upperTileMap, i - 1, j - 1, mapSize, safeTiles);
		}
	}

	if (j - 1 >= 0) {
		if (upperTileMap[i][j - 1].getIsRemoved() == false) {
			upperTileMap[i][j - 1].removeTile(safeTiles);
			if (underTileMap[i][j - 1].getType() == 0)
				showAdjacents(underTileMap, upperTileMap, i, j - 1, mapSize, safeTiles);
		}
	}

	if (i + 1 <= mapSize - 1 && j - 1 >= 0) {
		if (upperTileMap[i + 1][j - 1].getIsRemoved() == false) {
			upperTileMap[i + 1][j - 1].removeTile(safeTiles);
			if (underTileMap[i + 1][j - 1].getType() == 0)
				showAdjacents(underTileMap, upperTileMap, i + 1, j - 1, mapSize, safeTiles);
		}
	}

	if (i - 1 >= 0) {
		if (upperTileMap[i - 1][j].getIsRemoved() == false) {
			upperTileMap[i - 1][j].removeTile(safeTiles);
			if (underTileMap[i - 1][j].getType() == 0)
				showAdjacents(underTileMap, upperTileMap, i - 1, j, mapSize, safeTiles);
		}
	}

	if (i + 1 <= mapSize - 1) {
		if (upperTileMap[i + 1][j].getIsRemoved() == false) {
			upperTileMap[i + 1][j].removeTile(safeTiles);
			if (underTileMap[i + 1][j].getType() == 0)
				showAdjacents(underTileMap, upperTileMap, i + 1, j, mapSize, safeTiles);
		}
	}

	if (i - 1 >= 0 && j + 1 <= mapSize - 1) {
		if (upperTileMap[i - 1][j + 1].getIsRemoved() == false) {
			upperTileMap[i - 1][j + 1].removeTile(safeTiles);
			if (underTileMap[i - 1][j + 1].getType() == 0)
				showAdjacents(underTileMap, upperTileMap, i - 1, j + 1, mapSize, safeTiles);
		}
	}

	if (j + 1 <= mapSize - 1) {
		if (upperTileMap[i][j + 1].getIsRemoved() == false) {
			upperTileMap[i][j + 1].removeTile(safeTiles);
			if (underTileMap[i][j + 1].getType() == 0)
				showAdjacents(underTileMap, upperTileMap, i, j + 1, mapSize, safeTiles);
		}
	}

	if (i + 1 <= mapSize - 1 && j + 1 <= mapSize - 1) {
		if (upperTileMap[i + 1][j + 1].getIsRemoved() == false) {
			upperTileMap[i + 1][j + 1].removeTile(safeTiles);
			if (underTileMap[i + 1][j + 1].getType() == 0)
				showAdjacents(underTileMap, upperTileMap, i + 1, j + 1, mapSize, safeTiles);
		}
	}
}

void initGameOverText(sf::Text & gameOverText, sf::Font & font, sf::RenderWindow & window)
{
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(48.f);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setOutlineColor(sf::Color::Black);
	gameOverText.setOutlineThickness(1.f);
	gameOverText.setString("GAME OVER");
	gameOverText.setPosition(
		(window.getSize().x / 2.f) - (gameOverText.getGlobalBounds().width / 2.f),
		(window.getSize().y / 2.f) - (gameOverText.getGlobalBounds().height / 2.f));
}

void initYouWinText(sf::Text & youWinText, sf::Font & font, sf::RenderWindow & window)
{
	youWinText.setFont(font);
	youWinText.setCharacterSize(48.f);
	youWinText.setFillColor(sf::Color::Green);
	youWinText.setOutlineColor(sf::Color::Black);
	youWinText.setOutlineThickness(1.f);
	youWinText.setString("YOU WIN");
	youWinText.setPosition(
		(window.getSize().x / 2.f) - (youWinText.getGlobalBounds().width / 2.f),
		(window.getSize().y / 2.f) - (youWinText.getGlobalBounds().height / 2.f)
	);
}

void initGeneralText(sf::Text & generalText, sf::Font & font, sf::RenderWindow & window, int posX, int posY, int size)
{
	generalText.setFont(font);
	generalText.setCharacterSize(size);
	generalText.setFillColor(sf::Color::White);
	generalText.setOutlineColor(sf::Color::Black);
	generalText.setOutlineThickness(1.f);
	//generalText.setString(text);
	generalText.setPosition(posX, posY);
}
