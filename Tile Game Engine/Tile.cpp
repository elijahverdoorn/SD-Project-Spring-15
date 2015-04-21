#include <iostream>
#include <string>
#include "Tile.h"

Tile::Tile(sf::Texture par)
{
	texture = par;
	sprite = new sf::Sprite(texture);
}

Tile::Tile(std::string fileName)
{
	std::cout << "found texture at: " << fileName << std::endl;
	texture.loadFromFile(fileName);
	sprite = new sf::Sprite(texture);
}

Tile::~Tile()
{

}
void Tile::draw(sf::RenderWindow *window)
{
	window->draw(*sprite);
}
sf::Sprite Tile::getSprite()
{
	return *sprite;
}