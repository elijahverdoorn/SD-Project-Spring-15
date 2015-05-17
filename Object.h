#ifndef _OBJECT_
#define _OBJECT_

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Tile.h"

class Object: public Tile
{
	bool passable;//can characters be here?
	int moveCost;//how much it costs to enter the tile

public:
	//constructors
	Object();
	Object(sf::Texture texture);
	Object(std::string fileName);
	Object(sf::Texture texture, bool pass, int cost);
	Object(std::string fileName, bool pass, int cost);
	//destructor
	~Object();

	//member methods
	void setPassable(bool par);//set the passable variable
	bool isPassable();//return passable
	void setMoveCost(int par);//set the move cost
	int getMoveCost();//return the move cost
	void setTexture(sf::Texture t);//set the texture of the object
	sf::Texture getTexture();//return the texture of the object
	sf::Texture* getTexturePtr();//return a pointer to the texture of the object
};
#endif //_OBJECT_
