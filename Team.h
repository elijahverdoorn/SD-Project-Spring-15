#ifndef _TEAM_
#define _TEAM_

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "Character.h"
#include "CharacterArray.h"


class Team
{
	int teamID; //the teamID
	bool turn;
	CharacterArray group; //The character array held by the team
	int actions;//the number of actions a team has
	int members;//number of characters on a team(from members in the array)
public:
	//constructors
	Team();//Default
	Team(CharacterArray set); //create team from character array

	//destructor
	~Team();

	//member methods
	int getTeamID();
	void setTeamID(int par);
	bool isTurn();
	void setTurn(bool par); //decides who's turn it is
	int getActions();
	void resetActions();
	void loseAction();
	int win(sf::RenderWindow* gameWindow, int screenfile);




	//opeartors
};

#endif // _TEAM_