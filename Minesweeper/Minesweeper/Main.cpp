#include <iostream>
#include <ctime>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "UnderTile.h"
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

	//Init mouse position
	sf::Vector2i mousePosWindow;
	float tileSize = underTileMap[0][0].getSize();

	//Init bombs
	int bombsQuant = 30;
	initBombs(bombsQuant, underTileMap, mapSize);
	

	//Init near bombs counter
	nearBombsCounter(underTileMap, mapSize);


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
				if (event.key.code == sf::Mouse::Left) {

					if (x >= 0 && x < mapSize && y >= 0 && y < mapSize) {

						if (underTileMap[x][y].getType() == 9)
							std::cout << "Game Over" << std::endl;
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

		//Render grid
		for (int i = 0; i < mapSize; i++) {
			for (int j = 0; j < mapSize; j++) {

				underTileMap[i][j].drawTile(window);
			}
		}

		//Done drawing
		window.display();
	}

	return 0;
}