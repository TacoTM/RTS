#include "Game.h"

Game::Game()
{
	map.sizeOptions = 1;
}

void Game::start(sf::RenderWindow & window)
{

	map.generateMap(window);


	map.createLandMass();
	camera.setCenter(map.mapSizeX / 2, map.mapSizeY / 2);
	camera.setSize(2500, 5000);
	gameLogic(window);

}

void Game::drawObjects(sf::RenderWindow & window)
{
	map.redrawTiles(window);
}

void Game::eventProcessing(sf::RenderWindow & window, sf::Time &deltaTime)
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		}

	}
}

void Game::gameLogic(sf::RenderWindow & window)
{
	while (window.isOpen())
	{
		//Any resets
		window.setView(camera);
		sf::Time deltaTime = clock.restart();

		eventProcessing(window, deltaTime);
		cameraUpdates(window);

		camera.move(camVelocity.x*deltaTime.asSeconds()*cameraSpeed, camVelocity.y*deltaTime.asSeconds()*cameraSpeed);
		camVelocity = sf::Vector2f(0, 0);


		window.clear(sf::Color::White);
		drawObjects(window);
		window.display();
	}

}

void Game::cameraUpdates(sf::RenderWindow & window)
{
	//Make sure the camera is in map bounds
	//Make sure we only recieve input if the window is active.
	if (window.hasFocus())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && ((window.getView().getCenter().y + window.getView().getSize().y / 2) < (map.mapSizeY - buffer)))
		{
			camVelocity = sf::Vector2f(camVelocity.x, 1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && ((window.getView().getCenter().y - window.getView().getSize().y / 2) > (0 + buffer)))
		{
			camVelocity = sf::Vector2f(camVelocity.x, -1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && ((window.getView().getCenter().x - window.getView().getSize().x / 2) > (0 + buffer)))
		{
			camVelocity = sf::Vector2f(-1, camVelocity.y);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && ((window.getView().getCenter().x + window.getView().getSize().x / 2) < (map.mapSizeX - buffer)))
		{
			camVelocity = sf::Vector2f(1, camVelocity.y);
		}
	}
}


