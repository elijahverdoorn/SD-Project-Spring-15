#include <iostream>
#include "Team.h"
#include <SFML/Graphics.hpp>
#include <string>

//constructors
Team::Team()//default
{
	teamID = 0;
	turn = true;
	actions = 3;

}
Team::Team(CharacterArray set)
{
	teamID = 0;
	turn = true;
	actions = 3;
	
}

//deconstructor
Team::~Team()//needed?
{

}

//member methods
int Team::getTeamID()//return team ID tag
{
	return teamID;
}

void Team::setTeamID(int par)//change ID tag
{
	teamID = par;
}


bool Team::isTurn()
{
	return turn;
}

void Team::setTurn(bool par) //Is it this teams turn?
{
	turn = par;
}

int Team::getActions()
{
	return actions;
}

void Team::resetActions()
{
	actions = 3;
}

void Team::loseAction()
{
	actions--;
}

int Team::win(sf::RenderWindow* gameWindow, int screenfile) 
{
	sf::RenderWindow window (sf::VideoMode(800, 600), "End Screen", sf::Style::Close);
    sf::Texture splashImage;
    if(screenfile == 1)
    {
 		splashImage.loadFromFile("BlueTeamWins.png");
    }
    if(screenfile == 2)
    {
    	splashImage.loadFromFile("RedTeamWins.png");	
    }
    sf::Sprite logoSprite(splashImage);
    logoSprite.setPosition(0,0);
	while (window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				gameWindow->close();
            }
			if (event.type == sf::Event::KeyPressed)
            {
                // Escape key : exit
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                	gameWindow->close();
            }
		}
		window.clear();
		window.draw(logoSprite);
		window.display();
	}
}

//operators
//the [] operator