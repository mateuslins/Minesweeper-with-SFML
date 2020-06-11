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
}


UpperTile::~UpperTile()
{
}

void UpperTile::adjustPosition(int i, int j, float topDistance, float rigthDistance)
{
	tile.setPosition(i * size + topDistance, j * size + rigthDistance);
}

void UpperTile::drawTile(sf::RenderWindow & window)
{
	if (isRemoved == false)
		window.draw(tile);
}

float UpperTile::getSize()
{
	return size;
}

void UpperTile::removeTile()
{
	isRemoved = true;
}

bool UpperTile::getIsRemoved()
{
	return isRemoved;
}