#include <iostream>
#include "Engine.h"
#include "Tile.h"

//constructor
Engine::Engine()
{
	window = new sf::RenderWindow (sf::VideoMode(800, 600), "SFML window");
}

//destructor
Engine::~Engine()
{

}

//gameloop
int Engine::mainLoop()
{
	// Load a sprite to display
	sf::Texture texture;
	if (!texture.loadFromFile("testsprite.png"))
		return EXIT_FAILURE;
	Tile tile("testsprite.png");
	sf::Sprite sprite(texture);
	sf::Sprite sprite2(texture);
	sprite.setPosition(30, 0);
	sprite2.setPosition(15, 0);
	// Start the game loop
	while (window->isOpen())
	{
		// Process events
		sf::Event event;
		while (window->pollEvent(event))
		{
			// Close window : exit
			if (event.type == sf::Event::Closed)
				window->close();
		}
		// Clear screen
		window->clear();
		// Draw the sprite
		window->draw(tile.getSprite());
		window->draw(sprite);
		window->draw(sprite2);
		// Update the window
		window->display();
	}
	return EXIT_SUCCESS;
}