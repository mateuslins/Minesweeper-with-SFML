#include "UnderTile.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>



UnderTile::UnderTile()
{
	tile.setSize(sf::Vector2f(size, size));
	tile.setFillColor(sf::Color::White);
	tile.setOutlineThickness(1.f);
	tile.setOutlineColor(sf::Color::Black);

	text.setCharacterSize(size);
	text.setFillColor(sf::Color::Black);
	text.setString(" ");
}


UnderTile::~UnderTile()
{
}

void UnderTile::adjustPosition(int i, int j, int mapSize, float topDistance, float rigthDistance)
{
	tile.setPosition(i * size + topDistance, j * size + rigthDistance);
	text.setPosition(i * size + topDistance, j * size + rigthDistance);
}

void UnderTile::drawTile(sf::RenderWindow &window)
{
	window.draw(tile);
	window.draw(text);
}

void UnderTile::plantBomb()
{
	type = 9;
	changeText();
}

int UnderTile::getType()
{
	return type;
}

void UnderTile::setType(int t)
{
	type = t;
	changeText();
}

float UnderTile::getSize()
{
	return size;
}

void UnderTile::loadFont()
{
	font.loadFromFile("Arial.ttf");
	text.setFont(font);
}

void UnderTile::changeText()
{
	switch (type) {
	case 0:
		text.setString(" ");
		break;
	case 9:
		text.setString("B");
		break;
	case 10:
		text.setString(" ");
		break;
	default:
		text.setString(std::to_string(type));
		break;
	}
}

void UnderTile::addOnType()
{
	type++;
	changeText();
}

bool UnderTile::getIsNearFirst()
{
	return isNearFirst;
}

void UnderTile::setIsNearFirstTrue()
{
	isNearFirst = true;
}
