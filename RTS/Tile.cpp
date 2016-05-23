#include "Tile.h"

Tile::Tile()
{
	this->setSize(sf::Vector2f(100, 100));
}


void Tile::setTexture(sf::Texture & texture)
{

}

void Tile::setTileType(int type)
{
	switch (type)
	{
	case 1:
		tileType = Type::GRASS;
		this->setFillColor(sf::Color(1, 142, 14));
		break;
	case 2:
		tileType = Type::SAND;
		this->setFillColor(sf::Color(237, 201, 175));
		break;
	case 3:
		tileType = Type::WATER;
		this->setFillColor(sf::Color(25, 118, 210));
		break;
	default:
		tileType = Type::WATER;
		this->setFillColor(sf::Color(25, 118, 210));
		break;
	}
}

Tile::Type Tile::getTileType()
{
	return Tile::tileType;
}



