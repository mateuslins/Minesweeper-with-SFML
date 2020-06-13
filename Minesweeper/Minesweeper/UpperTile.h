#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>

// This class represent the tiles that will hide the ones with the numbers and bombs

class UpperTile
{
public:
	UpperTile();
	~UpperTile();

	void adjustPosition(int i, int j, int mapSize, float topDistance, float rigthDistance);
	void drawTile(sf::RenderWindow &window);
	float getSize();
	void removeTile(int &safeTiles);
	bool getIsRemoved();
	void putFlag(int &flagsQuant);
	bool getHasFlag();

private:
	sf::RectangleShape tile;
	sf::Text text;
	sf::Font font;
	float size = 30.f;
	bool isRemoved = false;
	bool hasFlag = false;
};

