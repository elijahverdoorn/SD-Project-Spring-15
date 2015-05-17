#include "Tile.h"

//constructors
Tile::Tile()//default
{

}

Tile::Tile(sf::Texture par)//from a texture
{
	texture = par;
	sprite = new sf::Sprite(texture);
	width = texture.getSize().x;
	height = texture.getSize().y;
}

Tile::Tile(std::string fileName)//from a filename
{
	texture.loadFromFile(fileName);
	sprite = new sf::Sprite(texture);
}

//deconstructor
Tile::~Tile()//not really needed
{

}

//member methods
void Tile::draw(sf::RenderWindow *window)//function to draw the tile on the window
{
	window->draw(*sprite);
}

sf::Sprite Tile::getSprite()//function to return the sprite object
{
	return *sprite;
}

void Tile::setPosition(int x, int y)
{
	posX = x;
	posY = y;
	sprite->setPosition(posX, posY);
}

void Tile::setEditorPosition(int x, int y)
{
  posX = x;
  posY = y;
}

void Tile::setWidth(int par)
{
	width = par;
}

void Tile::setHeight(int par)
{
	height = par;
}

int Tile::getWidth()
{
	return width;
}

int Tile::getHeight()
{
	return height;
}

int Tile::getPositionX()
{
	return posX;
}

int Tile::getPositionY()
{
	return posY;
}

void Tile::setPositionX(int par)
{
	posX = par;
}

void Tile::setPositionY(int par)
{
	posY = par;
}

void Tile::setTexture(sf::Texture t)
{
  texture = t;
}

sf::Texture Tile::getTexture()
{
  return texture;
}

sf::Texture* Tile::getTexturePtr()
{
  return &texture;
}

void Tile::setFileName(std::string file)
{
  fileName = file;
}

std::string Tile::getFileName()
{
  return fileName;
}
