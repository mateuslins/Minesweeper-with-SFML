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

	// Init window
	const int width = 800;
	const int heigth = 600;
	sf::RenderWindow window(sf::VideoMode(width, heigth), "Minesweeper", sf::Style::Close | sf::Style::Titlebar);

	// Init resources
	sf::Texture texture;
	texture.loadFromFile("sand.jpg");
	sf::Sprite sprite;
	sprite.setTexture(texture);

	// Init grid
	int mapSize;

	UnderTile aux;
	float topDistance = 0;
	float rightDistance = 0;

	std::vector<std::vector<UnderTile>> underTileMap; //Vector of vectors = 2D

	std::vector<std::vector<UpperTile>> upperTileMap; //Vector of vectors = 2D

	// Init mouse position
	sf::Vector2i mousePosWindow;
	float tileSize = aux.getSize();

	// Init bombs
	int bombsQuant;
	int flagsQuant;

	// Init game states
	bool isGameOver = false;
	bool winCondition = false;
	bool gameStarted = false;
	bool isFirstMove = true;

	int dangerousTiles = 0;
	int safeTiles = 0;

	// Init texts on screen
	sf::Font font;
	font.loadFromFile("Arial.ttf");

	sf::Text gameOverText;
	initGameOverText(gameOverText, font, window);

	sf::Text youWinText;
	initYouWinText(youWinText, font, window);

	sf::Text flagsQuantText;
	initGeneralText(flagsQuantText, font, window, sf::Color::White, 10, 10, 16);

	sf::Text tilesRemainText;
	initGeneralText(tilesRemainText, font, window, sf::Color::White, 10, 31, 16);

	sf::Text welcomeText;
	welcomeText.setString("MINESWEEPER");
	initMenuText(welcomeText, font, window, sf::Color::Cyan, 100, 48);

	sf::Text autorText;
	autorText.setString("by Mateus Lins");
	initMenuText(autorText, font, window, sf::Color::White, 160, 16);

	sf::Text selectText;
	selectText.setString("SELECT DIFFICULTY");
	initMenuText(selectText, font, window, sf::Color::Red, 250, 30);

	sf::Text easyText;
	easyText.setString("1 - Easy");
	initMenuText(easyText, font, window, sf::Color::Red, 300, 30);

	sf::Text mediumText;
	mediumText.setString("2 - Medium");
	initMenuText(mediumText, font, window, sf::Color::Red, 350, 30);

	sf::Text hardText;
	hardText.setString("3 - Hard");
	initMenuText(hardText, font, window, sf::Color::Red, 400, 30);

	sf::Text leftClickText;
	leftClickText.setString("Left Click: Remove tile");
	initMenuText(leftClickText, font, window, sf::Color::White, 550, 16);

	sf::Text rightClickText;
	rightClickText.setString("Right Click: Put/Remove flag");
	initMenuText(rightClickText, font, window, sf::Color::White, 570, 18);


	// INIT GAME LOOP
	while (window.isOpen()) {

		// Update mouse position
		mousePosWindow = sf::Mouse::getPosition(window);
		int x = (mousePosWindow.x / tileSize) - (topDistance / tileSize);
		int y = (mousePosWindow.y / tileSize) - (rightDistance / tileSize);

		// Events
		sf::Event event;

		while (window.pollEvent(event)) {

			// Close window
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;

			// Mouse click
			case sf::Event::MouseButtonPressed:
				if (!isGameOver && !winCondition && gameStarted) {

					if (event.key.code == sf::Mouse::Left) {

						if (x >= 0 && x < mapSize && y >= 0 && y < mapSize) {

							// If is first move,
							// display the bombs and start the game logic
							if (isFirstMove) {

								underTileMap[x][y].setType(10);

								initBombs(bombsQuant, underTileMap, mapSize, x, y);

								nearBombsCounter(underTileMap, mapSize);

								upperTileMap[x][y].removeTile(safeTiles);

								showAdjacents(underTileMap, upperTileMap, x, y, mapSize, safeTiles);

								isFirstMove = false;
							}

							else {

								upperTileMap[x][y].removeTile(safeTiles);

								if (underTileMap[x][y].getType() == 0) 
									showAdjacents(underTileMap, upperTileMap, x, y, mapSize, safeTiles);
								

								else if (underTileMap[x][y].getType() == 9 && upperTileMap[x][y].getHasFlag() == false) 
									isGameOver = true;
								
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

			// Key press (to choose the difficulty)
			case sf::Event::KeyPressed:
				if (!gameStarted) {

					switch (event.key.code) {
					case (sf::Keyboard::Num1):

						initGame(mapSize, topDistance, rightDistance, window, aux, underTileMap, upperTileMap, bombsQuant, flagsQuant, dangerousTiles, safeTiles, 1);
						gameStarted = true;
						break;

					case (sf::Keyboard::Num2):

						initGame(mapSize, topDistance, rightDistance, window, aux, underTileMap, upperTileMap, bombsQuant, flagsQuant, dangerousTiles, safeTiles, 2);
						gameStarted = true;
						break;

					case (sf::Keyboard::Num3):

						initGame(mapSize, topDistance, rightDistance, window, aux, underTileMap, upperTileMap, bombsQuant, flagsQuant, dangerousTiles, safeTiles, 3);
						gameStarted = true;
						break;

					default:
						break;
					}
				}

			default:
				break;
			}
		}


		// Render
		window.clear();

		// Render background
		window.draw(sprite);

		// Render under grid
		if (gameStarted) {
			for (int i = 0; i < mapSize; i++) {
				for (int j = 0; j < mapSize; j++) {

					underTileMap[i][j].drawTile(window);
				}
			}
		}

		// Render upper grid
		if (gameStarted) {
			for (int i = 0; i < mapSize; i++) {
				for (int j = 0; j < mapSize; j++) {

					upperTileMap[i][j].drawTile(window);
				}
			}
		}

		// Render general text
		if (gameStarted) {
			std::stringstream ss1;
			ss1 << "Flags: " << std::to_string(flagsQuant);
			flagsQuantText.setString(ss1.str());
			window.draw(flagsQuantText);

			std::stringstream ss2;
			ss2 << "Safe tiles left: " << std::to_string(safeTiles);
			tilesRemainText.setString(ss2.str());
			window.draw(tilesRemainText);

			window.draw(leftClickText);

			window.draw(rightClickText);
		}
		// Render menu text
		else {

			window.draw(welcomeText);

			window.draw(autorText);

			window.draw(selectText);

			window.draw(easyText);

			window.draw(mediumText);

			window.draw(hardText);
		}

		//Render game over text
		if (isGameOver)
			window.draw(gameOverText);

		//Render win text
		if (safeTiles == 0 && gameStarted) {
			winCondition = true;
			window.draw(youWinText);
		}

		//Done drawing
		window.display();
	}

	return 0;
};