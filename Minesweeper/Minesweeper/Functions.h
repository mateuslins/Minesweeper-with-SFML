#pragma once

void initGame(
	int &mapSize, float &topDistance, float &rightDistance,
	sf::RenderWindow &window, UnderTile aux,
	std::vector<std::vector<UnderTile>> &underTileMap, 
	std::vector<std::vector<UpperTile>> &upperTileMap, 
	int &bombsQuant, int &flagsQuant, int &dangerousTiles, int &safeTiles, int level);

void initGrid(std::vector<std::vector<UnderTile>> &underTileMap, int mapSize, float topDistance, float rightDistance);

void initUpperGrid(std::vector<std::vector<UpperTile>> &upperTileMap, int mapSize, float topDistance, float rightDistance);

void initBombs(int &bombsQuant, std::vector<std::vector<UnderTile>> &underTileMap, int mapSize, int x, int y);

void nearBombsCounter(std::vector<std::vector<UnderTile>> &underTileMap, int mapSize);

void showAdjacents(std::vector<std::vector<UnderTile>> &underTileMap, std::vector<std::vector<UpperTile>> &upperTileMap, int i, int j, int mapSize, int &safeTiles);

void initGameOverText(sf::Text &gameOverText, sf::Font &font, sf::RenderWindow &window);

void initYouWinText(sf::Text &youWinText, sf::Font &font, sf::RenderWindow &window);

void initGeneralText(sf::Text &generalText, sf::Font &font, sf::RenderWindow &window, sf::Color color, int posX, int posY, int size);

void initMenuText(sf::Text &menuText, sf::Font &font, sf::RenderWindow &window, sf::Color color, int posY, int size);