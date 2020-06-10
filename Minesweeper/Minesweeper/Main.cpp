#include <iostream>
#include <ctime>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "UnderTile.h"


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

	std::vector<std::vector<UnderTile>> underTileMap; //Vector of vectors = 2D
	underTileMap.resize(mapSize, std::vector<UnderTile>()); //Resizing to (mapSize) vectors of UnderTiles (making a line)

	float topDistance = window.getSize().x / 5.f;
	float rigthDistance = window.getSize().y / 5.f;

	for (int i = 0; i < mapSize; i++) {

		underTileMap[i].resize(mapSize, UnderTile()); //Resizing to (mapSize) UnderTiles per vector (making column)
		for (int j = 0; j < mapSize; j++) {

			underTileMap[i][j].adjustPosition(i, j, topDistance, rigthDistance);
			underTileMap[i][j].loadFont();
			//underTileMap[i][j].changeText();
		}
	}

	//Init bombs
	int bombsQuant = 30;
	while (bombsQuant > 0) {

		int i = rand() % mapSize;
		int j = rand() % mapSize;

		if (underTileMap[i][j].getType() != 9) {

			underTileMap[i][j].plantBomb();
			bombsQuant--;
		}
	}


	while (window.isOpen()) {

		sf::Event event;

		while (window.pollEvent(event)) {

			switch (event.type) {
			case sf::Event::Closed:
				window.close();
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