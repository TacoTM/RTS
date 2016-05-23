#pragma once
#include <SFML\Window.hpp>
#include "Tilemap.h"

class Game
{
public:
	Game();
	void start(sf::RenderWindow &window);
	void drawObjects(sf::RenderWindow &window);
	void eventProcessing(sf::RenderWindow & window, sf::Time &deltaTime);
	void gameLogic(sf::RenderWindow & window);
	void cameraUpdates(sf::RenderWindow & window);

private:
	sf::Clock clock;

	sf::View camera;
	sf::Vector2f camVelocity;

	Map map;

	int buffer = 200;
	float lastTime = 0;
	float cameraSpeed = 800;
};
