#include <SFML/Graphics.hpp>
#include "Engine.h"
int main()
{
	Engine engine;
	engine.mainLoop();
	engine.~Engine();
}