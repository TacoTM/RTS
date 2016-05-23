#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <iostream>

using namespace std;
class Tile : public sf::RectangleShape
{
public:
	Tile();

	enum Type
	{
		GRASS,
		SAND,
		WATER
	};

	void setTexture(sf::Texture &texture); //No use for this atm, as fill colors are used for now
	void setTileType(int type); // 1 - Grass, 2 - Sand, 3 - Water

	Type getTileType();

private:
	const float tileSize = 100;
	Type tileType;

};