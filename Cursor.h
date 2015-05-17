#ifndef _CURSOR_
#define _CURSOR_

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Character.h"
#include "Tile.h"
#include "CharacterArray.h"
#include "Object.h"
#include "Map.h"
#include "Team.h"

class Cursor
{
	sf::Sprite *sprite; // the cursor sprite
	sf::Texture texture; // the cursor texture
	int posX, posY; // the position of the cursor
	int gridPosX, gridPosY;//the grid position of the cursor
	int gridLocation; // the location on the grid (not used)
	int width, height; // the width and the height of the cursor
	Character *character; // a pointer to the character selected by the cursor
	Tile *tile; // a pointer to the tile under the character
	bool characterSelected;//is there a character selected?

	bool moving = false;// is the selected chararcter moving?

public:
	//Constructors
	Cursor(); // default
	Cursor(sf::Texture texture); // create from a texture
	Cursor(std::string fileName); // create from a filname
	
	//deconstructor
	~Cursor(); // not needed

	//member methods
	void move(int par, int dir, int windowsizeX, int windowsizeY); // move the cursor
	void setPosition(int x, int y); // set the cursor's position
	void draw(sf::RenderWindow *window); // draw the cursor
	void moveCharacter(CharacterArray arr, CharacterArray enemyArr, Map mapArr);//move the character pointed to by character to the current position of the cursor
	bool isCharacterSelected();//return the value of characterSelected
	
	Character* getCharacter(CharacterArray arr); // get the character under the cursor
	Tile getTile(); // get the tile under the cursor
	void setTexture(std::string fileName);//set the texture of the cursor

	bool attackCharacter(CharacterArray arr, Map mapArr);//the currently selected character attacks the charcter that the cursor is over


	void setMoving(bool par);
	bool isMoving();
	//operators
};
#endif //_CURSOR_