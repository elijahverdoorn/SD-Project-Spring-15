#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "Tile.h"
#include "Map.h"
#include "Character.h"
#include "Cursor.h"
#include "CharacterArray.h"
#include "SoundArray.h"
#include "Object.h"
#include "HUD.h"
#include "Team.h"

class Engine
{
private:
	// sfml render window
	int windowWidth, windowHeight;//the height and width in px
	sf::RenderWindow *window;// the window object
	std::string windowName;//the name of the window

public:
	//constructor
	Engine();//default
	Engine(int w, int h, std::string x);//standard


	//destructor
	~Engine();//not needed

	//member methods
	int mainLoop(std::string fileName);//function to run the gameloop
};

#endif // _ENGINE_H_