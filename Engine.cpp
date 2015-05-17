#include "Engine.h"

//constructor
Engine::Engine()//default
{
	windowWidth = 700;
	windowHeight = 500;
	window = new sf::RenderWindow (sf::VideoMode(windowWidth, windowHeight), "SFML window");
}

Engine::Engine(int w, int h, std::string x)//standard
{
	windowWidth = w + 200; // so that there is room for the HUD
	windowHeight = h;
	window = new sf::RenderWindow (sf::VideoMode(windowWidth, windowHeight), "test");
}

//destructor
Engine::~Engine()//not needed
{

}

//member methods
int Engine::mainLoop(std::string fileName)//function to run the gameloop
{
	HUD hud;
	std::ifstream file (fileName); // open the file
	int numRows, numCols;
	file >> numRows;
	file >> numCols;
	int numObjs;
	file >> numObjs;
	int numChars;
	file >> numChars;


	Map map(numRows, numCols);
	CharacterArray charArrRedTeam;
	CharacterArray charArrBlueTeam;

	// play music
	std::string musicFile;
	file >> musicFile;
	sf::Music music1;
	if (!music1.openFromFile(musicFile))
	{
		// std::cout << "failed to load music file" << std::endl;
		return -1;
	}
	music1.play();
	music1.setLoop(true);

	//set up sounds
	// std::cout << "getting sounds" << std::endl;
	std::string walkSoundFileName, attackSoundFileName, dieSoundFileName, winSoundFileName, changeTeamSoundFileName;
	file >> walkSoundFileName;
	file >> attackSoundFileName;
	file >> dieSoundFileName;
	file >> winSoundFileName;
	file >> changeTeamSoundFileName;
	sf::SoundBuffer walkSoundBuffer, attackSoundBuffer, dieSoundBuffer, winSoundBuffer, changeTeamSoundBuffer;
	if (!walkSoundBuffer.loadFromFile(walkSoundFileName))
	{
		// std::cout << "failed to load music file" << std::endl;
		return -1;
	}
	if (!attackSoundBuffer.loadFromFile(attackSoundFileName))
	{
		// std::cout << "failed to load music file" << std::endl;
		return -1;
	}
	if (!dieSoundBuffer.loadFromFile(dieSoundFileName))
	{
		// std::cout << "failed to load music file" << std::endl;
		return -1;
	}
	if (!winSoundBuffer.loadFromFile(winSoundFileName))
	{
		// std::cout << "failed to load music file" << std::endl;
		return -1;
	}
	if (!changeTeamSoundBuffer.loadFromFile(changeTeamSoundFileName))
	{
		// std::cout << "failed to load music file" << std::endl;
		return -1;
	}
	sf::Sound walkSound, attackSound, dieSound, winSound, changeTeamSound;
	walkSound.setBuffer(walkSoundBuffer);
	attackSound.setBuffer(attackSoundBuffer);
	dieSound.setBuffer(dieSoundBuffer);
	winSound.setBuffer(winSoundBuffer);
	changeTeamSound.setBuffer(changeTeamSoundBuffer);

	Team blueTeam(charArrBlueTeam);
	Team redTeam(charArrRedTeam);

	for (int i = 0; i < map.getNumTiles(); ++i) // map built from tile texture filenames
	{
		std::string textureFile;
		file >> textureFile;
		Tile *tempTile = new Tile (textureFile);
		map.changeTile(i, *tempTile);
	}

	Object *blank = new Object ("blanktile.png"); // if its not a pointer, then the object will die after this method is called and there will be no way to use it
	blank->setPassable(true);
	blank->setMoveCost(1);
	map.fillObject(*blank); // fill the map with transparent objects

	for (int i = 0; i < numObjs; ++i)
	{
		std::string textureFile; // set up all the parts of the non-transparent objects
		int posX, posY, moveCost, passableInt;
		file >> textureFile;
		file >> posX;
		file >> posY;
		file >> passableInt;
		file >> moveCost;
		bool passable = true;
		if (passableInt == 0)
		{
			passable = false;
		}
		Object *obj = new Object(textureFile, passable, moveCost);
		int arrayPos;
		arrayPos = (posY * map.getNumColumns()) + (posX);
		map.changeObject(arrayPos, *obj); // change the map to contain that object
	}

	for (int i = 0; i < numChars; ++i) // get all the characters and put them in the correct teams
	{
		int teamNumber, posX, posY, speed, hp, atk, def, range;
		std::string textureFile, name;
		file >> teamNumber;
		file >> textureFile;
		file >> name;
		file >> posX;
		file >> posY;
		file >> speed;
		file >> hp;
		file >> atk;
		file >> def;
		file >> range;
		Character *tempChar = new Character(textureFile, name);
		tempChar->setGridPosition(posX, posY);
		tempChar->setMaxSpeed(speed);
		tempChar->setMaxHitPoints(hp);
		tempChar->setMaxAtk(atk);
		tempChar->setMaxDef(def);
		tempChar->setMaxRange(range);
		if (teamNumber == 1)
		{
			charArrBlueTeam.addCharacter(tempChar);
			//blueTeam.initialMembers(charArrBlueTeam);
			//everytime a member is added to the array, it reinitializes the head count
		}
		if (teamNumber == 2)
		{
			charArrRedTeam.addCharacter(tempChar);
			//redTeam.initialMembers(charArrRedTeam)
		}
	}

	Cursor blueCursor("blueCursor.png");
	blueCursor.setPosition(3,3);
	Cursor redCursor("redCursor.png");
	redCursor.setPosition(3,3);

	blueTeam.setTurn(false);
	// Start the game loop

	// std::cout << "starting loop" << std::endl;
	//starting the main game loop

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
				// Close window : exit
			if (event.type == sf::Event::Closed)
			{
				window->close();			
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Up)
				{
					if (blueTeam.isTurn())
					{
						blueCursor.move(1,1,windowWidth,windowHeight);
					}else{
						redCursor.move(1,1,windowWidth,windowHeight);
					}
				}
				if (event.key.code == sf::Keyboard::Right)
				{
					if (blueTeam.isTurn())
					{
						blueCursor.move(1,4,windowWidth,windowHeight);
					}else{
						redCursor.move(1,4,windowWidth,windowHeight);
					}
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					if (blueTeam.isTurn())
					{
						blueCursor.move(1,2,windowWidth,windowHeight);
					}else{
						redCursor.move(1,2,windowWidth,windowHeight);
					}
				}
				if (event.key.code == sf::Keyboard::Left)
				{
					if (blueTeam.isTurn())
					{
						blueCursor.move(1,3,windowWidth,windowHeight);
					}else{
						redCursor.move(1,3,windowWidth,windowHeight);
					}
				}
				if (event.key.code == sf::Keyboard::Return)//if the enter key is pressed
				{
					if (blueTeam.isTurn())
					{
						blueCursor.getCharacter(charArrBlueTeam);
						// std::cout<<"Character Selected:" << blueCursor.getCharacter(charArrBlueTeam)->getName()<<std::endl;
					}else{
						redCursor.getCharacter(charArrRedTeam);
						// std::cout<<"Character Selected:" << redCursor.getCharacter(charArrRedTeam)->getName()<<std::endl;
					}
				}

				//Move functions
				if (event.key.code == sf::Keyboard::Num1)//movement
				{
					if (blueTeam.isTurn())
					{
						if (blueCursor.isCharacterSelected())
						{
							if (blueCursor.isMoving())
							{
								blueCursor.moveCharacter(charArrBlueTeam, charArrRedTeam, map);
								walkSound.play();
								// std::cout<<"actions left: " << blueTeam.getActions() << std::endl;
							}else{
								if (blueTeam.getActions() > 0)
								{
									blueTeam.loseAction();
									blueCursor.moveCharacter(charArrRedTeam, charArrBlueTeam, map);
									walkSound.play();
									// std::cout<<"actions left: "<< redTeam.getActions() << std::endl;
								}
							}
						}else{
							std::cout<< "can't move, no character selected"<<std::endl;						
						}
					}

					if (redTeam.isTurn())
					{
						if (redCursor.isCharacterSelected())
						{
							if (redCursor.isMoving())
							{
								redCursor.moveCharacter(charArrRedTeam, charArrBlueTeam, map);
								walkSound.play();
								// std::cout<<"actions left: " << redTeam.getActions() << std::endl;
							}else{
								if (redTeam.getActions() > 0)
								{
									redTeam.loseAction();
									walkSound.play();
									redCursor.moveCharacter(charArrRedTeam, charArrBlueTeam, map);
									// std::cout<<"actions left: "<< redTeam.getActions() << std::endl;
								}
							}
						}else{
							std::cout<<"can't move, no character selected"<<std::endl;						
						}
					}	
				}

				//attack functions
				if (event.key.code == sf::Keyboard::Num2)//attack
				{
					if (blueTeam.isTurn() && blueTeam.getActions() > 0)
					{
						if (blueCursor.isCharacterSelected())
						{
							if (blueCursor.attackCharacter(charArrRedTeam, map))
							{
								attackSound.play();
								blueTeam.loseAction();
							}
						}
					}
					if (redTeam.isTurn() && redTeam.getActions() > 0)
					{
						if (redCursor.isCharacterSelected())
						{
							if (redCursor.attackCharacter(charArrBlueTeam, map))
							{
								attackSound.play();
								redTeam.loseAction();
							}
						}
					}
				}
				if (event.key.code == sf::Keyboard::T)
				{
					if (blueTeam.isTurn())
					{
						blueTeam.setTurn(false);
						redTeam.setTurn(true);
						changeTeamSound.play();
						blueTeam.resetActions();
					}else{
						blueTeam.setTurn(true);
						redTeam.setTurn(false);
						changeTeamSound.play();
						redTeam.resetActions();
					}
					// std::cout << "changing" << std::endl;
				}		
				if (event.key.code == sf::Keyboard::Escape)
				{
					window->close();			
				}
			}
		}

		window->clear();

		//implement win condition here
		if (!charArrRedTeam.haveLiveCharacters())
		{
			//blue wins
			winSound.play();
			blueTeam.win(window, 1);
		}
		if(!charArrBlueTeam.haveLiveCharacters())
		{
			//red wins
			winSound.play();
			redTeam.win(window, 2);
		}

		//draw the things
		map.draw(window);//draw the map'
		charArrRedTeam.draw(window);
		charArrBlueTeam.draw(window);//draw the characters

		//get the character data to send to the hud, and draw the hud
		Character* selectedCharacter;
		
		if (redTeam.isTurn())
		{
			if (redCursor.isCharacterSelected())
			{
				selectedCharacter = charArrRedTeam.getSelected();
			}
			hud.draw(windowWidth - 200, 0, 2, window, selectedCharacter, redCursor.isCharacterSelected(), redTeam.getActions());//draw the HUD on top of it all
		}
		if (blueTeam.isTurn())
		{
			if (blueCursor.isCharacterSelected())
			{
				selectedCharacter = charArrBlueTeam.getSelected();
			}
			hud.draw(windowWidth - 200, 0, 1, window, selectedCharacter, blueCursor.isCharacterSelected(), blueTeam.getActions());//draw the HUD on top of it all
		}

		// draw the cursor based on whose turn it is
		if (blueTeam.isTurn())
		{
			blueCursor.draw(window);
		}
		if (redTeam.isTurn())
		{
			redCursor.draw(window);
		}
		window->display();
	}
	return EXIT_SUCCESS;
}
