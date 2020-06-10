#include <iostream>
#include <SFML/Graphics.hpp>
#include "UnderTile.h"


int main() {

	//Init window
	const int width = 800;
	const int heigth = 600;
	sf::RenderWindow window(sf::VideoMode(width, heigth), "Minesweeper", sf::Style::Close | sf::Style::Titlebar);

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