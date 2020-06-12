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

	void adjustPosition(int i, int j, int mapSize, float topDistance, float rigthDistance);
	void drawTile(sf::RenderWindow &window);
	void plantBomb();
	int getType();
	void setType(int t);
	float getSize();
	void loadFont();
	void changeText();
	void addOnType();
	bool getIsNearFirst();
	void setIsNearFirstTrue();

private:
	sf::RectangleShape tile;
	sf::Font font;
	sf::Text text;
	float size = 30.f;
	bool isNearFirst = false;

	int type = 0;
	// 0-8: bombs counter
	// 9: bomb
	// 10: first move
};

