#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>

class UpperTile
{
public:
	UpperTile();
	~UpperTile();

	void adjustPosition(int i, int j, float topDistance, float rigthDistance);
	void drawTile(sf::RenderWindow &window);
	float getSize();
	void removeTile();
	bool getIsRemoved();

private:
	sf::RectangleShape tile;
	float size = 30.f;
	bool isRemoved = false;
};

