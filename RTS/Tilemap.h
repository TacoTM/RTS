#pragma once
#include "Tile.h"
#include <stdlib.h>
#include <ctime>
class Map
{
public:
	Map();

	void generateMap(sf::RenderWindow &wnd);
	void configureTile(Tile &newTile, int tileSeed);
	void redrawTiles(sf::RenderWindow &window);
	void createLandMass();

	int findTileAtCoords(float x, float y);

	vector<Tile> tiles;

	int sizeOptions = 1; //1 for small, 2 for medium, 3 for large
	int numberLandMasses = 6; //How many landmasses to generate?
	int mapSizeX;
	int mapSizeY;
private:

	int landSize = 2500;
	const float tileSize = 100;
	float nextTileY = 0;
	float nextTileX = 0;
	int generationCounter = 0;


	enum mapSize
	{
		SMALL, // 200x100
		MEDIUM, // 400x300
		LARGE // 800x700
	};

	mapSize size;
};
