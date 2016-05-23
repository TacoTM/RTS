#include <SFML/Graphics.hpp>
#include "Game.h"
#include <ctime>
int main()
{

	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Naval RTS prototype", sf::Style::Default, settings);
	Game game;

	//Set the max framerate of the application to 60
	game.start(window);


	return 0;
}
