#ifndef _CHARACTERARRAY_
#define _CHARACTERARRAY_

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>

class CharacterArray
{
	int numCharacters; //int to hold number of characters
	std::vector<Character*> characterVector;//array to hold all the characters
public:
	//constructors
	CharacterArray();//default

	//deconstructor
	~CharacterArray();//needed?

	//member methods
	int getNumCharacters();//return the num characters
	Character* getCharacter(int par); //return the character at position par in array
	void draw(sf::RenderWindow *window); // draw the array of characters
	void addCharacter(Character* par);//add a character to the end of the array
	void deleteAll();//clear the array
	void deleteCharacter(int par);//delete a character at position par
	void deleteCharacter(Character par);//delete the character "par" from the array
	Character* checkPosition(int x, int y);//check if there is a character at position x,y and return a pointer to that character if so
	Character* getSelected();
	bool haveLiveCharacters();
	//operators
	//the [] operator
};
#endif // _CHARACTERARRAY_ 