#ifndef _TILE_
#define _TILE_

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Tile
{
protected:
	sf::Sprite *sprite;
	sf::Texture texture;
	int posX, posY;
	int width, height;
	std::string fileName;

public:
	//constructors
	Tile();//default
	Tile(sf::Texture par);//from a texture
	Tile(std::string fileName);//from a filename

	//deconstructor
	~Tile();//not really needed

	//member methods
	void draw(sf::RenderWindow *window);//function to draw the tile on the window
	sf::Sprite getSprite();//function to return the sprite object
	void setPosition(int x, int y);//set the position x and postion y variables in a single function
	void setEditorPosition(int x, int y);
	void setWidth(int par);//set the width variable
	void setHeight(int par);//set the height variable
	int getWidth();//return the width variable
	int getHeight();//return the height variable
	int getPositionX();//return the pos x variable
	int getPositionY();//return the pos y variable
	void setPositionX(int par);//set the pos x variable
	void setPositionY(int par);//set the pos y variable
	void setTexture(sf::Texture t);
	sf::Texture getTexture();
	sf::Texture* getTexturePtr();
	void setFileName(std::string file);
	std::string getFileName();
};
#endif // _TILE_
