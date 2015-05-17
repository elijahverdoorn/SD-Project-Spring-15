#include <iostream>
#include "Character.h"
#include "CharacterArray.h"

//constructors
CharacterArray::CharacterArray()//default
{
	numCharacters = characterVector.size();
}

//deconstructor
CharacterArray::~CharacterArray()//needed?
{

}

//member methods
int CharacterArray::getNumCharacters()//return the num tiles
{
	return characterVector.size();
}

Character* CharacterArray::getCharacter(int par)
{
	return characterVector[par];
}

void CharacterArray::draw(sf::RenderWindow *window)
{
	for (int i = 0; i < characterVector.size(); ++i)
	{
		characterVector[i]->draw(window);
		// std::cout << "drew a character named " << characterVector[i]->getName() << std::endl;
	}
}

void CharacterArray::addCharacter(Character* par)
{
	characterVector.push_back(par);
}

void CharacterArray::deleteAll()
{
	characterVector.clear();
}

void CharacterArray::deleteCharacter(int par)
{
	characterVector.erase(characterVector.begin() + par);
}

void CharacterArray::deleteCharacter(Character par)
{
	for (int i = 0; i < characterVector.size(); ++i)
	{
		if (characterVector[i]->getName() == par.getName())
		{
			characterVector.erase(characterVector.begin() + i);
		}
	}
}

Character* CharacterArray::checkPosition(int x, int y)
{
	for (int i = 0; i < characterVector.size(); ++i)
	{
		if((characterVector[i]->getPositionX() == x) && (characterVector[i]->getPositionY() == y))
		{
			return characterVector[i];
		}
	}
	
//	std::cout << "CharacterArray::checkPosition() returning NULL" << std::endl;
	return NULL;
}

Character* CharacterArray::getSelected()
{
	for (int i = 0; i < characterVector.size(); ++i)
	{
		if (characterVector[i]->isSelected())
		{
			return characterVector[i];
		}
	}
}

bool CharacterArray::haveLiveCharacters()
{
	for (int i = 0; i < characterVector.size(); ++i)
	{
		if (characterVector[i]->isAlive())
		{
			return true;
		}
	}
	return false;
}

//operators
//the [] operator