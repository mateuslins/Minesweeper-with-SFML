#include "UnderTile.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>



UnderTile::UnderTile()
{
	tile.setSize(sf::Vector2f(size, size));
	tile.setFillColor(sf::Color::White);
	tile.setOutlineThickness(1.f);
	tile.setOutlineColor(sf::Color::Black);
}


UnderTile::~UnderTile()
{
}

void UnderTile::adjustPosition(int i, int j, float topDistance, float rigthDistance)
{
	tile.setPosition(i * size + topDistance, j * size + rigthDistance);
}

void UnderTile::drawTile(sf::RenderWindow &window)
{
	window.draw(tile);
}
