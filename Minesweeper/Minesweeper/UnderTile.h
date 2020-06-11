#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>

class UnderTile
{
public:
	UnderTile();
	~UnderTile();

	void adjustPosition(int i, int j, float topDistance, float rigthDistance);
	void drawTile(sf::RenderWindow &window);
	void plantBomb();
	int getType();
	float getSize();
	void loadFont();
	void changeText();
	void addOnType();

private:
	sf::RectangleShape tile;
	sf::Font font;
	sf::Text text;
	//std::stringstream ss;
	float size = 30.f;
	int type = 0;
};

