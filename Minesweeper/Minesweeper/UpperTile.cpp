#include "UpperTile.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>



UpperTile::UpperTile()
{
	tile.setSize(sf::Vector2f(size, size));
	tile.setFillColor(sf::Color(220, 220, 220)); //gainsboro (light grey)
	tile.setOutlineThickness(1.f);
	tile.setOutlineColor(sf::Color(128, 128, 128)); //html gray (dark grey)

	text.setCharacterSize(size);
	text.setFillColor(sf::Color::Black);
	text.setString("F");
}


UpperTile::~UpperTile()
{
}

// Set positions on grid
void UpperTile::adjustPosition(int i, int j, int mapSize, float topDistance, float rigthDistance)
{
	tile.setPosition(i * size + topDistance, j * size + rigthDistance);
	text.setPosition(i * size + topDistance, j * size + rigthDistance);
}

// Draw tile and flag
void UpperTile::drawTile(sf::RenderWindow & window)
{
	if (!isRemoved) {

		window.draw(tile);
		if (hasFlag) {

			window.draw(text);
		}
	}
}

float UpperTile::getSize()
{
	return size;
}

// Stop drawing tile
void UpperTile::removeTile(int & safeTiles)
{
	if (!hasFlag && !isRemoved) {
		isRemoved = true;
		safeTiles--;
	}
}

bool UpperTile::getIsRemoved()
{
	return isRemoved;
}

//Put or remove flag on tile
void UpperTile::putFlag(int &flagsQuant)
{
	if (!isRemoved) {
		if (!hasFlag) {
			if (flagsQuant > 0) {
				font.loadFromFile("Arial.ttf");
				text.setFont(font);
				hasFlag = true;
				flagsQuant--;
			}
		}
		else {
			hasFlag = false;
			flagsQuant++;
		}
	}
}

bool UpperTile::getHasFlag()
{
	return hasFlag;
}
