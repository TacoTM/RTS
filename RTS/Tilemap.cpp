#include "Tilemap.h"

Map::Map()
{
	if (sizeOptions == 1)
		size = SMALL;
	else if (sizeOptions == 2)
		size = MEDIUM;
	else if (sizeOptions == 3)
		size = LARGE;
	else
		size = MEDIUM;
}

void Map::generateMap(sf::RenderWindow &wnd)
{
	srand(time(NULL));
	/*
	The way this works is that generally every tile will be water at the start,
	then points will be randomly chosen as centers for landmasses.
	Land is then "grown" outward from the center to a max radius.
	*/
	if (size == SMALL) //200x100
	{
		mapSizeX = 20000;
		mapSizeY = 10000;
		for (int i = 0; i < 99; ++i)
		{
			Tile newRowTile;
			newRowTile.setTileType(3); //Set to water
			newRowTile.setPosition(0, nextTileY);
			tiles.push_back(newRowTile);
			for (int j = 0; j < 200; ++j)
			{
				Tile newColTile;
				newColTile.setTileType(3);
				newColTile.setPosition(nextTileX, nextTileY);
				nextTileX += tileSize;
				tiles.push_back(newColTile);
			}
			nextTileY += tileSize;
			nextTileX = tileSize;
		}
	}
}

void Map::configureTile(Tile & newTile, int tileSeed)
{

}

void Map::redrawTiles(sf::RenderWindow &window)
{
	//Frustrum culling
	float startX = 100 * floor(((window.getView().getCenter().x - window.getView().getSize().x / 2) + 50) / 100);
	float startY = 100 * floor(((window.getView().getCenter().y - window.getView().getSize().y / 2) + 50) / 100);

	float endX = 100 * floor(((window.getView().getCenter().x + window.getView().getSize().x / 2) + 50) / 100);
	float endY = 100 * floor(((window.getView().getCenter().y + window.getView().getSize().y / 2) + 50) / 100);

	int beginTile = findTileAtCoords(startX, startY);
	int endTile = findTileAtCoords(endX, endY);

	for (int i = beginTile; i <= endTile; ++i)
	{
		if (tiles[i].getPosition().x >= startX
			&& tiles[i].getPosition().x <= endX
			&& tiles[i].getPosition().y >= startY
			&& tiles[i].getPosition().y <= endY)
			window.draw(tiles[i]);
	}
}

void Map::createLandMass()
{
	//Grass generation

	int centerTile = (tiles.size() / 2);
	int adjacentTile = ((tiles.size() / 2) + 1);
	do
	{
		generationCounter++;
		int seed = rand() % 5;
		if (centerTile < tiles.size() && adjacentTile < tiles.size() && (centerTile + 1) < tiles.size() && (centerTile - 1) < tiles.size())
		{
			switch (seed)
			{
			case 1: //Right
				adjacentTile = centerTile + 1;
				tiles[adjacentTile].setTileType(1);
				centerTile = adjacentTile;
				break;
			case 2: //Left
				adjacentTile = centerTile - 1;
				tiles[adjacentTile].setTileType(1);
				centerTile = adjacentTile;
				break;
			case 3: //Up
				adjacentTile = findTileAtCoords(tiles[centerTile].getPosition().x, tiles[centerTile].getPosition().y - tileSize);
				if (adjacentTile < tiles.size())
				{
					tiles[adjacentTile].setTileType(1);
					centerTile = adjacentTile;
				}
				break;
			case 4: //Down
				adjacentTile = findTileAtCoords(tiles[centerTile].getPosition().x, tiles[centerTile].getPosition().y + tileSize);
				if (adjacentTile < tiles.size())
				{
					tiles[adjacentTile].setTileType(1);
					centerTile = adjacentTile;
				}
				break;
			}
		}
	} while (generationCounter <= landSize);


	//Sand generation
	for (int j = 0; j < tiles.size(); ++j)
	{
		if (tiles[j].getTileType() == Tile::GRASS)
		{
			if (j + 1 < tiles.size() || j - 1 < tiles.size())
			{
				int upTile = findTileAtCoords(tiles[j].getPosition().x, tiles[j].getPosition().y - tileSize);
				int downTile = findTileAtCoords(tiles[j].getPosition().x, tiles[j].getPosition().y + tileSize);
				if (tiles[j + 1].getTileType() == Tile::WATER)
				{
					tiles[j + 1].setTileType(2);
				}
				else if (tiles[j - 1].getTileType() == Tile::WATER)
				{
					tiles[j - 1].setTileType(2);
				}
				if (upTile < tiles.size() && downTile < tiles.size())
				{
					if (tiles[upTile].getTileType() == Tile::WATER)
					{
						tiles[upTile].setTileType(2);
					}
					if (tiles[downTile].getTileType() == Tile::WATER)
					{
						tiles[downTile].setTileType(2);
					}
				}
			}
		}
	}
}

int Map::findTileAtCoords(float x, float y)
{
	for (int i = 0; i < tiles.size(); ++i)
	{
		if (tiles[i].getPosition().x == x && tiles[i].getPosition().y == y)
		{
			return i;
		}
	}
}



