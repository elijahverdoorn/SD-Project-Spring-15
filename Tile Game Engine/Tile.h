#ifndef _TILE_
#define _TILE_

#include <SFML/Graphics.hpp>
#include <string>

enum class TileType {VOID};

class Tile
{
private:
	sf::Sprite *sprite;
	sf::Texture texture;
	TileType tiletype;
	int varient;
	bool passable;

public:
	Tile();
	Tile(sf::Texture texture);
	Tile(std::string fileName);
	~Tile();

	void draw(sf::RenderWindow *window);
	sf::Sprite getSprite();
};

#endif // _TILE_