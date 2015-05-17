#include <iostream>
#include <string>
#include <cmath>
#include "Cursor.h"

//Constructors
Cursor::Cursor()
{
	characterSelected = false;
}

Cursor::Cursor(sf::Texture par)
{
	texture = par;
	sprite = new sf::Sprite(texture);
	width = texture.getSize().x;
	height = texture.getSize().y;
	posY = 0;
	posX = 0;
	characterSelected = false;
}

Cursor::Cursor(std::string fileName)
{
	texture.loadFromFile(fileName);
	sprite = new sf::Sprite(texture);
	width = texture.getSize().x;
	height = texture.getSize().y;
	posY = 0;
	posX = 0;
	characterSelected = false;
}

//deconstructor
Cursor::~Cursor()
{
 
}

//member methods
void Cursor::move(int par, int dir, int windowsizeX, int windowsizeY)
{
	switch (dir)
	{
		case 1:
			posY -= par * 50;
			gridPosY -= par;
			if (posY <= 0)
			{
				posY = 0;
			}
			if (posY >= windowsizeY - 50)
			{
				posY = windowsizeY - 50;
			}
		sprite->setPosition(posX,posY);
			break;
		case 2:
			posY += par * 50;
			gridPosY += par;
			if (posY <= 0)
			{
				posY = 0;
			}
			if (posY >= windowsizeY - 50)
			{
				posY = windowsizeY - 50;
			}
			sprite->setPosition(posX,posY);
			break;
		case 3:
			posX -= par * 50;
			gridPosX -= par;
			if (posX <= 0)
			{
				posX = 0;
			}
			if (posX >= windowsizeX - 250)
			{
				posX = windowsizeX - 250;
			}
			sprite->setPosition(posX,posY);
			break;
		case 4:
			posX += par * 50;
			gridPosX += par;
			if (posX <= 0)
			{
				posX = 0;
			}
			if (posX >= windowsizeX - 250)
			{
				posX = windowsizeX - 250;
			}
			sprite->setPosition(posX,posY);
			break;
		default:
			break;
	}
}

void Cursor::setPosition(int x, int y)
{
	posX = x * 50;
	posY = y * 50;
	gridPosX = x;
	gridPosY = y;
	sprite->setPosition(posX, posY);
}

void Cursor::draw(sf::RenderWindow *window)
{
	window->draw(*sprite);
}

Character* Cursor::getCharacter(CharacterArray arr)
{
	moving = false;
	character = arr.checkPosition(posX,posY);

	if (character != NULL)
	{
		character->setSelected(true);
		characterSelected = true;
		character->setCurrentSpeed(character->getMaxSpeed());
		return character;
	}else{
		std::cout << "Cursor::getCharacter() returning NULL." << std::endl;
		characterSelected = false;
		return NULL;
	}
}

void Cursor::moveCharacter(CharacterArray arr, CharacterArray enemyArr, Map mapArr)
{
	moving = true;
	if (character != NULL)//is there a character?
	{
		if ((arr.checkPosition(posX,posY) == NULL) && (enemyArr.checkPosition(posX,posY) == NULL) && mapArr.checkPosition(posX,posY))//is there another object of a character in the way?
		{
			if (((std::abs(character->getPositionX() - posX) == 50) && ((std::abs(character->getPositionY() - posY == 0)))) || (((std::abs(character->getPositionY() - posY) == 50)) && ((std::abs(character->getPositionX() - posX) == 0))))//check distance
			{
				character->movePixelPosition(posX, posY, mapArr.getMoveCost(posX,posY));//move the character
				// std::cout << "movecost: " << mapArr.getMoveCost(posX,posY) << std::endl;
				// character->setSelected(false);//deselect it
			}else{
				std::cout << "Too far, move only one square at a time" << std::endl;
			}
		}else{
			std::cout << "Cursor::moveCharacter() hit another character or an impassable object" << std::endl;
		}
		// character = NULL;//deselect all characters
		// characterSelected = false;//inform the cursor that there is no character selected
	}
	// character = NULL;//deselect all characters
}

bool Cursor::attackCharacter(CharacterArray arr, Map mapArr)
{
	moving = false;
	Character* attackTarget;
	bool returner;
	if (character != NULL)
	{
		Character* attackTarget = arr.checkPosition(posX,posY);
		if (attackTarget != NULL)
		{
			//do range checking
			int distX = std::abs(character->getPositionX() - attackTarget->getPositionX());
			int distY = std::abs(character->getPositionY() - attackTarget->getPositionY());
			int distTotal = std::floor((std::sqrt(std::pow(distX, 2) + std::pow(distY, 2))) / 50);
			if (character->getCurrentRange() >= distTotal)
			{
				attackTarget->takeDamage(character->getCurrentAtk() - attackTarget->getCurrentDef());
				returner = true;
				// std::cout << "target's remaining HP: " << attackTarget->getCurrentHitPoints() << std::endl;
				if (attackTarget->getCurrentHitPoints() <= 0)
				{
					// std::cout << attackTarget->getName() << " death" << std::endl;
					attackTarget->die();
					// arr.deleteCharacter(*attackTarget); // not sure why this doesn't work, so we just teleport them to -1,-1 (off the grid)				
				}
			}else{
				std::cout << "out of range" << std::endl;
				returner = false;
			}
		}else{
			returner = false;
		}
	}else{
		returner = false;
	}
	return returner;
}


void Cursor::setMoving(bool par)
{
	moving = par;
}

bool Cursor::isMoving()
{
	return moving;
}


bool Cursor::isCharacterSelected()
{
	return characterSelected;
}

void Cursor::setTexture(std::string fileName)
{
	texture.loadFromFile(fileName);
	sprite = new sf::Sprite(texture);
}
//operators