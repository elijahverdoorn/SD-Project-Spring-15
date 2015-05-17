#ifndef _HUD_
#define _HUD_

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

class HUD
{
private:
	// sfml render window
	sf::RenderWindow *window;// the window object
	sf::Font font;
	int fontSize = 20;
	
	std::string turnString;
	std::string atkString = "ATK: ", defString = "DEF: ", hpString = "HP: ", moveString = "Moves: ", rangeString = "Range: ";

	sf::Text turnText;

	sf::Text atkText;
	sf::Text defText;
	sf::Text hpText;
	sf::Text moveText;
	sf::Text rangeText;

	sf::Text actionsText;

	Character* currentCharacter;
	bool hasCharacter = false;

	sf::Texture logoTexture;
	sf::Sprite logoSprite;


public:
	//constructor
	HUD();//default

	//destructor
	~HUD();//not needed

	//member methods
	void draw(int x, int y, int turn, sf::RenderWindow* w, Character* selectedCharacter, bool b, int actions);
};

#endif // _HUD_