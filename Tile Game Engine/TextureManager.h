#ifndef _TEXTUREMANAGER_
#define __TEXTUREMANAGER_
#include <vector>
#include <SFML\Graphics.hpp>

class TextureManager
{
	//hold a list of all our images, using vector to avoid dealing with non-dynamic arrays
	std::vector<sf::Texture> textureList;

public:
	//constructors
	TextureManager();
	//destructor
	~TextureManager();

	//add an image to the list
	void addTexture(sf::Texture &texture);
	// return one of the images
	sf::Texture& getTexture(int par);
};
#endif //_TEXTUREMANAGER_