#include <iostream>
#include <ctime>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "UnderTile.h"
#include "UpperTile.h"
#include "Functions.h"



int main() {

	srand((unsigned)time(0));

	//Init window
	const int width = 800;
	const int heigth = 600;
	sf::RenderWindow window(sf::VideoMode(width, heigth), "Minesweeper", sf::Style::Close | sf::Style::Titlebar);

	//Init resources
	sf::Texture texture;
	texture.loadFromFile("sand.jpg");
	sf::Sprite sprite;
	sprite.setTexture(texture);

	//Init grid
	const int mapSize = 12;
	float topDistance = window.getSize().x / 5.f;
	float rightDistance = window.getSize().y / 5.f;

	std::vector<std::vector<UnderTile>> underTileMap; //Vector of vectors = 2D
	
	initGrid(underTileMap, mapSize, topDistance, rightDistance);

	std::vector<std::vector<UpperTile>> upperTileMap; //Vector of vectors = 2D

	initUpperGrid(upperTileMap, mapSize, topDistance, rightDistance);

	//Init mouse position
	sf::Vector2i mousePosWindow;
	float tileSize = underTileMap[0][0].getSize();

	//Init bombs
	int bombsQuant = 30;
	int flagsQuant = bombsQuant;

	//Init texts on screen
	sf::Font font;
	font.loadFromFile("Arial.ttf");

	sf::Text gameOverText;
	initGameOverText(gameOverText, font, window);

	sf::Text youWinText;
	initYouWinText(youWinText, font, window);

	//Init game states
	bool isGameOver = false;
	bool isFirstMove = true;


	while (window.isOpen()) {

		//Update mouse position
		mousePosWindow = sf::Mouse::getPosition(window);
		int x = (mousePosWindow.x / tileSize) - (topDistance / tileSize);
		int y = (mousePosWindow.y / tileSize) - (rightDistance / tileSize);

		//Events
		sf::Event event;

		while (window.pollEvent(event)) {

			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseButtonPressed:
				if (!isGameOver) {

					if (event.key.code == sf::Mouse::Left) {

						if (x >= 0 && x < mapSize && y >= 0 && y < mapSize) {

							if (isFirstMove) {

								underTileMap[x][y].setType(10);

								initBombs(bombsQuant, underTileMap, mapSize, x, y);

								nearBombsCounter(underTileMap, mapSize);

								upperTileMap[x][y].removeTile();

								showAdjacents(underTileMap, upperTileMap, x, y, mapSize);

								isFirstMove = false;
							}
							else {

								upperTileMap[x][y].removeTile();

								if (underTileMap[x][y].getType() == 0) {
									std::cout << "Atingiu um 0" << std::endl;
									showAdjacents(underTileMap, upperTileMap, x, y, mapSize);
								}

								else if (underTileMap[x][y].getType() == 9 && upperTileMap[x][y].getHasFlag() == false) {
									std::cout << "Game Over" << std::endl;
									isGameOver = true;
								}
							}
						}
					}

					if (event.key.code == sf::Mouse::Right) {

						if (x >= 0 && x < mapSize && y >= 0 && y < mapSize) {
							upperTileMap[x][y].putFlag(flagsQuant);
						}
					}
				}
				break;

			default:
				break;
			}
		}

		//Render
		window.clear();

		//Render background
		window.draw(sprite);

		//Render under grid
		for (int i = 0; i < mapSize; i++) {
			for (int j = 0; j < mapSize; j++) {

				underTileMap[i][j].drawTile(window);
			}
		}

		//Render upper grid
		for (int i = 0; i < mapSize; i++) {
			for (int j = 0; j < mapSize; j++) {

				upperTileMap[i][j].drawTile(window);
			}
		}

		//Render game over text
		if (isGameOver)
			window.draw(gameOverText);

		//Done drawing
		window.display();
	}

	return 0;
}