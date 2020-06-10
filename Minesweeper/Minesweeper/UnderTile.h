#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class UnderTile
{
public:
	UnderTile();
	~UnderTile();

	void adjustPosition(int i, int j, float topDistance, float rigthDistance);
	void drawTile(sf::RenderWindow &window);

private:
	sf::RectangleShape tile;
	float size = 20.f;
	int type = 0;
};

