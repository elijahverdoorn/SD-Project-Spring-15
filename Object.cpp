#include <iostream>
#include <string>
#include "Object.h"
#include "Tile.h"
//constructors
Object::Object()
{

}

Object::Object(sf::Texture par) : Tile(par)
{
	passable = true;
	moveCost = 1;
}

Object::Object(std::string fileName) : Tile(fileName)
{
	passable = true;
	moveCost = 1;
}

Object::Object(sf::Texture texture, bool pass, int cost) : Tile(texture)
{
	passable = pass;
	moveCost = cost;
}

Object::Object(std::string fileName, bool pass, int cost) : Tile(fileName)
{
	passable = pass;
	moveCost = cost;
}

//destructor
Object::~Object()
{

}

//member methods
void Object::setPassable(bool par)
{
	passable = par;
}

bool Object::isPassable()
{
	return passable;
}

void Object::setMoveCost(int par)
{
	moveCost = par;
}

int Object::getMoveCost()
{
	return moveCost;
}

void Object::setTexture(sf::Texture t)
{
  texture = t;
}

sf::Texture Object::getTexture()
{
  return texture;
}

sf::Texture* Object::getTexturePtr()
{
  return &texture;
}
