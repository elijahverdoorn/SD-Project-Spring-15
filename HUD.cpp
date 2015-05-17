#include "HUD.h"

HUD::HUD()
{
	font.loadFromFile("Cantarell-Regular.otf");

	atkText.setFont(font);
	defText.setFont(font);
	hpText.setFont(font);
	moveText.setFont(font);
	rangeText.setFont(font);

	atkText.setCharacterSize(fontSize);
	defText.setCharacterSize(fontSize);
	hpText.setCharacterSize(fontSize);
	moveText.setCharacterSize(fontSize);
	rangeText.setCharacterSize(fontSize);

	sf::Texture logoTexture;
	logoTexture.loadFromFile("stolaflogo.png");
	sf::Sprite logoSprite(logoTexture);
}

HUD::~HUD()
{

}

void HUD::draw(int x, int y, int turn, sf::RenderWindow* w, Character* selectedCharacter, bool b, int actions)
{
	sf::Text turnText("", font, fontSize);
	switch (turn)//determine which team's turn it is
	{
		case 0:
		break;
		case 1:
			turnString = "Team 1";
			turnText.setColor(sf::Color::Blue);

		break;
		case 2:
			turnString = "Team 2";
			turnText.setColor(sf::Color::Red);
		break;
		default:
		break;
	}
	turnText.setString(turnString);
	turnText.setPosition(x + 10, y + 10);

	if (b)//if a character is selected, guards against nullptr exceptions
	{
		currentCharacter = selectedCharacter;
		atkString = "ATK: " + std::to_string(currentCharacter->getCurrentAtk());
		defString = "DEF: " + std::to_string(currentCharacter->getCurrentDef());
		hpString = "HP: " + std::to_string(currentCharacter->getCurrentHitPoints());
		moveString = "Moves: " + std::to_string(currentCharacter->getCurrentSpeed());
		rangeString = "Range: " + std::to_string(currentCharacter->getCurrentRange());
	}

	//set the strings and positions for the character data
	atkText.setString(atkString);
	defText.setString(defString);
	hpText.setString(hpString);
	moveText.setString(moveString);
	rangeText.setString(rangeString);
	atkText.setPosition(x + 10, y + 40);
	defText.setPosition(x + 10, y + 60);
	hpText.setPosition(x + 10, y + 80);
	moveText.setPosition(x + 10, y + 100);
	rangeText.setPosition(x + 10, y + 120);

	sf::Text actionsText("Actions Remaining: " + std::to_string(actions), font, fontSize);
	actionsText.setPosition(x + 10, y + 150);

	//draw all the text
	w->draw(turnText);
	w->draw(atkText);
	w->draw(defText);
	w->draw(hpText);
	w->draw(moveText);
	w->draw(rangeText);
	w->draw(actionsText);

	//draw the logo
	logoSprite.setPosition(x + 10, y + 300);
	w->draw(logoSprite);
}