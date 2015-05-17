#ifndef _CHARACTER_
#define _CHARACTER_

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Character
{
	sf::Sprite *sprite;//the character's sprite
	sf::Texture texture;//the character's texture

	int posX, posY;//the characters pixel position x, y
	int gridLocation;//the character's location on the grid (unused)
	int width, height;//the texture's width and height
	bool selected;//true if this character is selected, false if not
	std::string name;//the character's name, must be unique

	int maxSpeed;//the character's movespeed
	int teamID;//the team that this character belongs to
	int maxHitPoints, maxAtkPower, maxDefPower; //the character's HP, attack power, and defense power
	int maxRange; // the character's range
	int maxActions; //the characters max actions

	//the character's current values
	int currentSpeed;
	int currentHitPoints, currentAtkPower, currentDefPower;
	int currentRange;
	std::string fileName;

	bool alive = true;

public:
	//Constructors
	Character();//default
	Character(sf::Texture texture, std::string namePar);//from a texture
	Character(std::string fileName, std::string namePar);//from a filename
	
	//deconstructor
	~Character();

	//member methods
	void move(int par, int dir);//move a character 
	void setGridPosition(int x, int y);//set the position of a character based on the 50x50 grid
	void setEditorPosition(int x, int y);
	void setPixelPosition(int x, int y);//set the position of a character based on the pixel position
	void draw(sf::RenderWindow *window); //draw the character on the window
	bool isSelected();//check if the character is selected
	void setSelected(bool par);//se the selected variable
	std::string getName();//return the name variable
	sf::Texture getTexture();//return the texture object
	sf::Texture* getTexturePtr();//return a pointer to the texture
	void setTexture(sf::Texture par);//set the texture object

	void movePixelPosition(int x, int y, int cost);//move to the position (x,y) in pixels, subtracting a move
	void moveGridPosition(int x, int y, int cost);//move to the grid position (x,y), subtracting a move
	int getPositionX();
	int getPositionY();
	int getTeamID();
	void setTeamID(int par);
	int getCurrentSpeed();
	void setCurrentSpeed(int par);
	void setName(std::string s);
	int getCurrentHitPoints();
	int getCurrentAtk();
	int getCurrentDef();
	void takeDamage(int par);
	int getCurrentRange();
	void setCurrentHitPoints(int par);
	void setMaxSpeed(int par);
	int getMaxSpeed();
	void die();
	void setMaxHitPoints(int par);
	int getMaxHitPoints();
	void setMaxAtk(int par);
	int getMaxAtk();
	void setMaxDef(int par);
	int getMaxDef();
	void setMaxRange(int par);
	int getMaxRange();
	void setFileName(std::string file);
	std::string getFileName();
	bool isAlive();

	//operators
};
#endif //_CHARACTER_
