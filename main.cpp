#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Engine.h"

int displayTitleScreen()
{
	sf::RenderWindow window (sf::VideoMode(500, 500), "Splash Screen", sf::Style::None);
    sf::Texture splashImage;
    if(!splashImage.loadFromFile("gamelogo.png"))
        return EXIT_FAILURE;
    sf::Sprite logoSprite(splashImage);
    logoSprite.setPosition(0,0);
	sf::Clock elapsedClock;
	while (window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
            {
                // Escape key : exit
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
		}

		sf::Time elapsed = elapsedClock.getElapsedTime();
		if (elapsed.asSeconds() >= 3)
		{
			window.close();
		}
		window.clear();
		window.draw(logoSprite);
		window.display();
	}
}


std::string getUserFile()
{
	sf::RenderWindow window (sf::VideoMode(400, 100), "Game Setup");
	sf::Font font;
    if (!font.loadFromFile("Cantarell-Regular.otf"))
        return NULL;
    std::string userInput;
	sf::Text userText(userInput, font, 20);
	sf::Text prompt("Please enter the name of your game file:", font, 20);
	userText.setPosition(30, 50);
	prompt.setPosition(20, 20);
	while (window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
            {
                // Escape key : exit
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                //the enter key also, that is the key that the user is used to pressing to input a string
                if (event.key.code == sf::Keyboard::Return)
                	window.close();
            }
            if (event.type == sf::Event::TextEntered)
            {

            		if (event.text.unicode < 128)
					{
						if (event.text.unicode == 8)//handle backspace
						{
							if (userInput.size() > 0)
							{
								userInput.pop_back();
							}
						}else{
							userInput += static_cast<char>(event.text.unicode);
						}
						userText.setString(userInput);
            	}
            }
		}

		window.clear();
		window.draw(userText);
		window.draw(prompt);
		window.display();
	}
	return userInput;
}

int main()
{
	displayTitleScreen();
	std::string userFile = getUserFile();
//	userFile = "/Data/GameFiles";
//		userFile += ;
	std::ifstream file (userFile); // open the file
	int tileDimensionsX, tileDimensionsY;
	file >> tileDimensionsX;
	file >> tileDimensionsY;
	int windowX = tileDimensionsX * 50;
	int windowY = tileDimensionsY * 50;
	Engine engine(windowX, windowY, "name");
	engine.mainLoop(userFile);
	engine.~Engine();
}
