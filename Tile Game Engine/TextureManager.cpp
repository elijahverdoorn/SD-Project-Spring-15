#include "TextureManager.h"
#include <vector>
#include <SFML\Graphics.hpp>

//constructors
TextureManager::TextureManager()
{

}
//destructor
TextureManager::~TextureManager()
{

}

//add an image to the list
void TextureManager::addTexture(sf::Texture &texture)
{
	// push the entire array back, then add the image parameter to it
	textureList.push_back(texture);
}
// return one of the images
sf::Texture& TextureManager::getTexture(int par)
{
	//return the image at the parameter
	return textureList[par];
}