#include <iostream>
#include <string>
#include "Character.h"
#include "Team.h"
#include "SoundArray.h"

//Constructors
Character::Character()
{
	selected = false;
}

Character::Character(sf::Texture par, std::string namePar)
{
	texture = par;
	sprite = new sf::Sprite(texture);
	width = texture.getSize().x;
	height = texture.getSize().y;
	name = namePar;

	maxSpeed = 5;
	maxHitPoints = 2;
	maxAtkPower = 2;
	maxDefPower = 1; 
	maxRange = 1;
	currentSpeed = maxSpeed;
	currentHitPoints = maxHitPoints;
	currentAtkPower = maxAtkPower;
	currentDefPower = maxDefPower;
	currentRange = maxRange;
	selected = false;
}

Character::Character(std::string fileName, std::string namePar)
{
	texture.loadFromFile(fileName);
	sprite = new sf::Sprite(texture);
	width = texture.getSize().x;
	height = texture.getSize().y;
	name = namePar;

	maxSpeed = 5;
	maxHitPoints = 2;
	maxAtkPower = 2;
	maxDefPower = 1; 
	maxRange = 1;
	currentSpeed = maxSpeed;
	currentHitPoints = maxHitPoints;
	currentAtkPower = maxAtkPower;
	currentDefPower = maxDefPower;
	currentRange = maxRange;
	selected = false;
}

//deconstructor
Character::~Character()
{
	// delete sprite;
}

//member methods
void Character::move(int par, int dir)
{
	switch (dir)
	{
		case 1:
			posY -= par * 50;
			sprite->setPosition(posX,posY);
			break;
		case 2:
			posY += par * 50;
			sprite->setPosition(posX,posY);
			break;
		case 3:
			posX -= par * 50;
			sprite->setPosition(posX,posY);
			break;
		case 4:
			posX += par * 50;
			sprite->setPosition(posX,posY);
			break;
		default:
			break;
	}
}

void Character::setTexture(sf::Texture par)
{
	texture = par;
}

void Character::setGridPosition(int x, int y)
{
	posX = x * 50;
	posY = y * 50;
	sprite->setPosition(posX, posY);
}

void Character::setEditorPosition(int x, int y)
{
  posX = x;
  posY = y;
}

void Character::setPixelPosition(int x, int y)
{
	posX = x;
	posY = y;
	sprite->setPosition(posX, posY);
}

void Character::movePixelPosition(int x, int y, int cost)
{
	if (currentSpeed > 0)
	{
		posX = x;
		posY = y;
		sprite->setPosition(posX, posY);
		currentSpeed = currentSpeed - cost;
	}
}

void Character::moveGridPosition(int x, int y, int cost)
{
	if (currentSpeed > 0)
	{
		posX = x * 50;
		posY = y * 50;
		sprite->setPosition(posX, posY);
		currentSpeed = currentSpeed - cost;
	}
}

void Character::draw(sf::RenderWindow *window)
{
	window->draw(*sprite);
}

bool Character::isSelected()
{
	return selected;
}

void Character::setSelected(bool par)
{
	selected = par;
}

std::string Character::getName()
{
	return name;
}

void Character::setName(std::string s)
{
  name = s;
}

int Character::getPositionX()
{
	return posX;
}

int Character::getPositionY()
{
	return posY;
}

sf::Texture Character::getTexture()
{
  return texture;
}

sf::Texture* Character::getTexturePtr()
{
  return &texture;
}
void Character::setTeamID(int par)
{
	teamID = par;
}

int Character::getTeamID()
{
	return teamID;
}

int Character::getCurrentSpeed()
{
	return currentSpeed;
}

void Character::setCurrentSpeed(int par)
{
	currentSpeed = par;
}

int Character::getCurrentHitPoints()
{
	return currentHitPoints;
}

void Character::takeDamage(int par)
{
	currentHitPoints -= par;
}

void Character::setCurrentHitPoints(int par)
{
	currentHitPoints = par;
}

int Character::getCurrentAtk()
{
	return currentAtkPower;
}

int Character::getCurrentDef()
{
	return currentDefPower;
}

int Character::getCurrentRange()
{
	return currentRange;
}

void Character::setMaxSpeed(int par)
{
	maxSpeed = par;
	currentSpeed = par;
}

int Character::getMaxSpeed()
{
	return maxSpeed;
}

void Character::die()
{
	currentHitPoints = 0;
	setGridPosition(-10,-10);
	alive = false;
}
void Character::setMaxHitPoints(int par)
{
	maxHitPoints = par;
	currentHitPoints = par;
}

int Character::getMaxHitPoints()
{
	return maxHitPoints;
}

int Character::getMaxAtk()
{
	return maxAtkPower;
}

void Character::setMaxAtk(int par)
{
	maxAtkPower = par;
}

int Character::getMaxDef()
{
	return maxDefPower;
}

void Character::setMaxDef(int par)
{
	maxDefPower = par;
}

int Character::getMaxRange()
{
	return maxRange;
}

void Character::setMaxRange(int par)
{
	maxRange = par;
}

std::string Character::getFileName()
{
  return fileName;
}

void Character::setFileName(std::string file)
{
  fileName = file;
}

bool Character::isAlive()
{
	return alive;
}
//operators
