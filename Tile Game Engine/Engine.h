#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <SFML/Graphics.hpp>

class Engine
{
private:
	// sfml render window
	sf::RenderWindow *window;

public:
	//constructor
	Engine();

	//destructor
	~Engine();

	//gameloop
	int mainLoop();
};

#endif // _ENGINE_H_