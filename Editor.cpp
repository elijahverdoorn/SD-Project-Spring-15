#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <math.h>
#include "Tile.h"
#include "Object.h"
#include "Character.h"
#include "Button.h"
using namespace std;

//Convert a number to a string, used for map size
namespace stringConvert
{
  template <typename T> std::string toString(const T& n)
  {
    std::ostringstream stm;
    stm << n;
    return stm.str();
  }
}

sf::RenderWindow window(sf::VideoMode(1600, 800), "Editor");
sf::Font font;
ofstream dataFile;
//cursorX and cursorY are the position of the blue cursor box; inBoxX and inBoxY are the positions of the cursor on the array of boxes (0 to gridSize), maxPosX and maxPosY is the total pixel size of the grid
int cursorX = -1, cursorY = -1, inBoxX = 0, inBoxY = 0, maxPosX, maxPosY, boxSize;
//Change grid size here, boxSize will autoupdate; nothing over 100x100, or it will break
int gridSizeX = 30, gridSizeY = 25;
//Here's the data for the map; 3 types of "tiles", 3 arrays, 100x100, since 100x100 is max map size.
Tile layer1[100][100];
Object layer2[100][100];
Character layer3[100][100];
int layer1data[100][100];
int layer2data[100][100];
int layer3data[100][100];

sf::Texture blankTexture;
//Set the current properties for each type
sf::Texture currentTexture1;
//Objects
int objects;
sf::Texture currentTexture2;
std::string currentTextureName2;
int currentPassable = 1;
int currentMoveCost = 0;
//Characters
int characters;
int characterID;
sf::Texture currentTexture3;
std::string currentTextureName3;
int currentTeam = 1;
string currentName;
int currentSpeed = 1;
int currentHP = 10;
int currentATK = 5;
int currentDEF = 5;
int currentRange = 1;

int currentTextureNum1 = 0;
int currentTextureNum2 = 0;
int currentTextureNum3 = 0;

//Each Texture has a user-defined name, so we need sf::Text as well as the string. Maximum should be set at 40 types of tiles, objects, and characters.
sf::Texture tileTextures[40];
string tileName[40];

sf::Texture objectTextures[40];
string objectName[40];
//Object definition (tree, base, city, etc.)texts3[0]
int objectDefine[40];
string objDefName[40];
Object objectDefs[40];
//Object Type is used again for characters, so no need to create duplicates
int objectType[40];
string typeName[40];

sf::Texture charTextures[40];
string charName[40];
//Character definition (troop, mech, tank, recon, etc.)
int charDefine[40];
string charDefName[40];
Character characterDefs[40];

//Music
sf::Music music[10];
string musicName[10];

//Sounds
sf::SoundBuffer soundBuffers[5];
sf::Sound sounds[5];
sf::Text soundText[5];
string soundName[5];

//Use this for the background music for each team
int music1 = 0, music2 = 0;

void reDraw(int tab)
{
  blankTexture.loadFromFile("white.png");
  if (gridSizeX > 100)
    {
      gridSizeX = 100;
    }
  if (gridSizeY > 100)
    {
      gridSizeY = 100;
    }
  if (gridSizeX < 2)
    {
      gridSizeX = 2;
    }
  if (gridSizeY < 2)
    {
      gridSizeY = 2;
    }
  //Whichever is bigger, the box needs to scale down so it isn't off the screen
  if (gridSizeX > gridSizeY)
    {
      boxSize = 800/gridSizeX;
    }
  else
    {
      boxSize = 800/gridSizeY;
    }
  //Set pixel dimensions of the grid
  maxPosX = gridSizeX*boxSize;
  maxPosY = gridSizeY*boxSize;
  //Set where the limits of the cursor are (where it can't go)
  if (cursorX < 800)
    {
      cursorX = 800;
    }
  if (cursorY < 1)
    {
      cursorY = 1;
    }
  if (cursorX > 800 + maxPosX - boxSize)
    {
      cursorX = 800 + maxPosX - boxSize;
    }
  if (cursorY > maxPosY - boxSize)
    {
      cursorY = maxPosY - boxSize;
    }
  //Set what array box the cursor is in (for example, [2,5])
  inBoxX = ceil((cursorX/boxSize)-(800/boxSize));
  inBoxY = ceil(cursorY/boxSize);
  //Create text for the tabs, as well as their properties
  sf::Text tabs[4];
  for (int a = 0; a < 4; a++)
    {
      tabs[a].setFont(font);
      tabs[a].setCharacterSize(15);
    }
  tabs[0].setString("Tile");
  tabs[1].setString("Object");
  tabs[2].setString("Character");
  tabs[3].setString("Audio");
  tabs[0].setPosition(40,6);
  tabs[1].setPosition(130,6);
  tabs[2].setPosition(215,6);
  tabs[3].setPosition(330,6);

  //Create the cursor - blue box
  sf::RectangleShape cursor(sf::Vector2f(boxSize - 2,boxSize - 2));
  cursor.setOutlineThickness(2);
  cursor.setOutlineColor(sf::Color(0,0,255));
  cursor.setFillColor(sf::Color(255,255,255,0));
  cursor.setPosition(cursorX,cursorY);

  //Create boxes for each of the tabs on the left menu area
  sf::RectangleShape tabbox[4];
  for (int a = 0; a < 4; a++)
    {
      tabbox[a].setSize(sf::Vector2f(96, 26));
      tabbox[a].setOutlineThickness(2);
      tabbox[a].setOutlineColor(sf::Color(130,96,72));
      if (tab == a + 1)
	{
	  tabbox[a].setFillColor(sf::Color(82,75,66));
	}
      else
	{
	  tabbox[a].setFillColor(sf::Color(164,150,132));
	}
      tabbox[a].setPosition((100*a) + 2,2);
    }

  //Create the brown shaded area under the tabs, as well as the outline
  sf::RectangleShape tabarea(sf::Vector2f(796, 796));
  tabarea.setOutlineThickness(2);
  tabarea.setOutlineColor(sf::Color(130,96,72));
  tabarea.setFillColor(sf::Color(164,150,132));
  tabarea.setPosition(2,2);

  //Create the grid area, basically a 800x800 box with outlines
  sf::RectangleShape gridarea(sf::Vector2f(798, 798));
  gridarea.setOutlineThickness(1);
  gridarea.setOutlineColor(sf::Color(0,0,0));
  gridarea.setFillColor(sf::Color(255,255,255));
  gridarea.setPosition(801,1);

  //Create the Save button for writing to a file
  Button saveButton(420,20,46,26);
  sf::Text saveText;
  saveText.setFont(font);
  saveText.setCharacterSize(15);
  saveText.setString("Save");
  saveText.setPosition(425,25);

  //Create the grid using a 2D array of boxes
  sf::RectangleShape grid[gridSizeY][gridSizeX];
  for (int x = 0; x < gridSizeY; x++)
    {
      for (int y = 0; y < gridSizeX; y++)
	{
	  grid[x][y].setSize(sf::Vector2f(boxSize,boxSize));
	  grid[x][y].setTexture(&blankTexture);
	  if (layer1data[y][x] > 0)//If there's a tile, draw it
	    {
	      grid[x][y].setTexture(layer1[y][x].getTexturePtr());
	    }
	  if (layer2data[y][x] > 0)//If there's an object, draw it
	    {
	      grid[x][y].setTexture(layer2[y][x].getTexturePtr());
	    }
	  if (layer3data[y][x] > 0)//If there's a character, draw it
	    {
	      grid[x][y].setTexture(layer3[y][x].getTexturePtr());
	    }
	  grid[x][y].setPosition(800 + (y*boxSize), x*boxSize);
	  //Make sure it doesn't push into the left menu area
	  if (maxPosX < 0)
	    {
	      maxPosX = 0;
	    }
	  if (maxPosY < 0)
	    {
	      maxPosY = 0;
	    }
	}
    }
  window.clear();
  window.draw(tabarea);
  window.draw(gridarea);
  saveButton.draw(&window);
  window.draw(saveText);
  for (int x = 0; x < gridSizeY; x++)
    {
      for (int y = 0; y < gridSizeX; y++)
	{
	  window.draw(grid[x][y]);
	}
    }
  for (int a = 0; a < 4; a++)
    {
      window.draw(tabbox[a]);
      window.draw(tabs[a]);
    }
  //Now for the tabs


  //For Tab1, or Tile tab:
  sf::Text texts1[5];
  //text for the current texture
  sf::Text textureOn1;
  for (int a = 0; a < 5; a++)
    {
      texts1[a].setFont(font);
      texts1[a].setCharacterSize(15);
    }
  textureOn1.setFont(font);
  texts1[0].setString("Map Size");
  texts1[1].setString("x");
  texts1[2].setString(stringConvert::toString(gridSizeX));
  texts1[3].setString(stringConvert::toString(gridSizeY));
  texts1[4].setString("Texture Select");
  textureOn1.setString(tileName[currentTextureNum1]);
  textureOn1.setCharacterSize(15);
  texts1[0].setPosition(66,40);
  texts1[1].setPosition(92,67);
  texts1[2].setPosition(50,70);
  texts1[3].setPosition(110,70);
  texts1[4].setPosition(48,110);
  textureOn1.setPosition(500,175);
  //Create and list the Textures, as well as the boxes they're in
  int loopVar1 = 0;
  //While the texture in [loopVar] has a name, which means there is one, or if all 40 textures exist
  Button* tileTextureBox;
  tileTextureBox = new Button[40];
  sf::Text tileTextureBoxText[40];
  while (loopVar1 < 40)
    {
      tileTextureBoxText[loopVar1].setFont(font);
      tileTextureBoxText[loopVar1].setString(tileName[loopVar1]);
      tileTextureBoxText[loopVar1].setCharacterSize(15);
      //Set its texture based on the number of the texture
      if (tileName[loopVar1] != "")
	{
	  tileTextures[loopVar1].loadFromFile("Data/Tiles/" + tileName[loopVar1] + ".png");
	}
      //Create its button
      if (loopVar1 < 20)
	{
	  tileTextureBox[loopVar1].createButton(48,135 + loopVar1*30,96,26);
	  tileTextureBoxText[loopVar1].setPosition(53,140 + loopVar1*30);
	}
      else
	{
	  tileTextureBox[loopVar1].createButton(148,135 + (loopVar1-20)*30,96,26);
	  tileTextureBoxText[loopVar1].setPosition(153,140 + (loopVar1-20)*30);
	}
      //Next button
      loopVar1++;
    }
  //Box for X grid size value
  Button inputSizeX(47,67,36,26);
  //Box for Y grid size value
  Button inputSizeY(107,67,36,26);
  //Box for showing the current texture
  sf::RectangleShape theTexture(sf::Vector2f(96,96));
  theTexture.setOutlineThickness(2);
  theTexture.setOutlineColor(sf::Color(130,96,72));
  theTexture.setTexture(&currentTexture1);
  theTexture.setPosition(398,135);

  //For Tab2, or Object tab:
  sf::Text texts2[4];
  //text for the current texture
  sf::Text textureOn2;
  for (int a = 0; a < 4; a++)
    {
      texts2[a].setFont(font);
      texts2[a].setCharacterSize(15);
    }
  textureOn2.setFont(font);
  texts2[0].setString("Texture Select");
  texts2[1].setString("Move Cost");
  texts2[2].setString("Passable?");
  texts2[3].setString("Defined Objects");
  textureOn2.setString(currentTextureName2);
  textureOn2.setCharacterSize(15);
  texts2[0].setPosition(8,110);
  texts2[1].setPosition(650,250);
  texts2[2].setPosition(650,300);
  texts2[3].setPosition(448,110);
  textureOn2.setPosition(650,110);
  //Create and list the Textures, as well as the boxes they're in
  int loopVar2 = 0;
  //While the texture in [loopVar] has a name, which means there is one, or if all 40 textures exist
  Button* objectTextureBox;
  objectTextureBox = new Button[40];
  sf::Text objectTextureBoxText[40];
  while (loopVar2 < 40)
    {
      //Set its texture based on the number of the texture
      if (objectName[loopVar2] != "")
	{
	  objectTextures[loopVar2].loadFromFile("Data/Objects/" + objectName[loopVar2] + ".png");
	}
      objectTextureBoxText[loopVar2].setFont(font);
      objectTextureBoxText[loopVar2].setString(objectName[loopVar2]);
      objectTextureBoxText[loopVar2].setCharacterSize(15);
      //Create its button
      if (loopVar2 < 20)
	{
	  objectTextureBox[loopVar2].createButton(8,135 + loopVar2*30,96,26);
	  objectTextureBoxText[loopVar2].setPosition(13, 140 + loopVar2*30);
	}
      else
	{
	  objectTextureBox[loopVar2].createButton(108,135 + (loopVar2-20)*30,96,26);
	  objectTextureBoxText[loopVar2].setPosition(113, 140 + (loopVar2-20)*30);
	}
      //Next button
      loopVar2++;
    }

  //Create and list the defined objects
  int loopVar2c = 0;
  Button* objectDefineBox;
  objectDefineBox = new Button[40];
  sf::Text objectDefineText[40];
  while (loopVar2c < 40)
    {
      objectDefineText[loopVar2c].setFont(font);
      objectDefineText[loopVar2c].setString(objDefName[loopVar2c]);
      objectDefineText[loopVar2c].setCharacterSize(15);
      //Create its button
      if (loopVar2c < 20)
	{
	  objectDefineBox[loopVar2c].createButton(448,135 + loopVar2c*30,96,26);
	  objectDefineText[loopVar2c].setPosition(453, 140 + loopVar2c*30);
	}
      else
	{
	  objectDefineBox[loopVar2c].createButton(548,135 + (loopVar2c-20)*30,96,26);
	  objectDefineText[loopVar2c].setPosition(553, 140 + (loopVar2c-20)*30);
	}
      //Next button
      loopVar2c++;
    }
  //Box for showing the current texture
  sf::RectangleShape theTexture2(sf::Vector2f(96,96));
  theTexture2.setOutlineThickness(2);
  theTexture2.setOutlineColor(sf::Color(130,96,72));
  theTexture2.setTexture(&currentTexture2);
  theTexture2.setPosition(648,135);
  //Buttons for the object data
  Button moveCostButton(750,250,36,26);
  Button passableButton(750,300,26,26);
  sf::Text buttonTexts2[2];
  buttonTexts2[0].setFont(font);
  buttonTexts2[0].setString(stringConvert::toString(currentMoveCost));
  buttonTexts2[0].setCharacterSize(15);
  buttonTexts2[0].setPosition(755,255);
  buttonTexts2[1].setFont(font);
  if (currentPassable == 0)
    {
      buttonTexts2[1].setString("F");
    }
  else
    {
      buttonTexts2[1].setString("T");
    }
  buttonTexts2[1].setCharacterSize(15);
  buttonTexts2[1].setPosition(755,305);

  //For Tab3, or Character tab:
  sf::Text texts3[10];
  //text for the current texture
  sf::Text textureOn3;
  for (int a = 0; a < 10; a++)
    {
      texts3[a].setFont(font);
      texts3[a].setCharacterSize(15);
    }
  textureOn3.setFont(font);
  texts3[1].setString("Texture Select");
  texts3[3].setString("Team");
  texts3[4].setString("Defined Characters");
  texts3[5].setString("Speed");
  texts3[6].setString("HP");
  texts3[7].setString("ATK");
  texts3[8].setString("DEF");
  texts3[9].setString("Range");
  textureOn3.setString(currentTextureName3);
  textureOn3.setCharacterSize(15);
  texts3[1].setPosition(8,110);
  texts3[3].setPosition(650,250);
  texts3[4].setPosition(448,110);
  for (int a = 5; a < 10; a++)
    {
      texts3[a].setPosition(650,300 + ((a-5) * 50));
    }
  textureOn3.setPosition(650,110);
  //Create and list the Textures, as well as the boxes they're in
  int loopVar3 = 0;
  //While the texture in [loopVar] has a name, which means there is one, or if all 40 textures exist
  Button* charTextureBox;
  charTextureBox = new Button[40];
  sf::Text charTextureText[40];
  while (loopVar3 < 40)
    {
      //Set its texture based on the number of the texture
      if (charName[loopVar3] != "")
	{
	  charTextures[loopVar3].loadFromFile("Data/Characters/" + charName[loopVar3] + ".png");
	}
      charTextureText[loopVar3].setFont(font);
      charTextureText[loopVar3].setString(charName[loopVar3]);
      charTextureText[loopVar3].setCharacterSize(15);
      //Create its button
      if (loopVar3 < 20)
	{
	  charTextureBox[loopVar3].createButton(8,135 + loopVar3*30,96,26);
	  charTextureText[loopVar3].setPosition(13,140 + loopVar3*30);
	}
      else
	{
	  charTextureBox[loopVar3].createButton(108,135 + (loopVar3-20)*30,96,26);
	  charTextureText[loopVar3].setPosition(113,140 + (loopVar3-20)*30);
	}
      //Next button
      loopVar3++;
    }

  //Create and list the defined characters
  int loopVar3c = 0;
  Button* characterDefineBox;
  characterDefineBox = new Button[40];
  sf::Text characterDefineText[40];
  while (loopVar3c < 40)
    {
      characterDefineText[loopVar3c].setFont(font);
      characterDefineText[loopVar3c].setString(charDefName[loopVar3c]);
      characterDefineText[loopVar3c].setCharacterSize(15);
      //Create its button
      if (loopVar3c < 20)
	{
	  characterDefineBox[loopVar3c].createButton(448,135 + loopVar3c*30,96,26);
	  characterDefineText[loopVar3c].setPosition(453, 140 + loopVar3c*30);
	}
      else
	{
	  characterDefineBox[loopVar3c].createButton(548,135 + (loopVar3c-20)*30,96,26);
	  characterDefineText[loopVar3c].setPosition(553, 140 + (loopVar3c-20)*30);
	}
      //Next button
      loopVar3c++;
    }

  //Box for showing the current texture
  sf::RectangleShape theTexture3(sf::Vector2f(96,96));
  theTexture3.setOutlineThickness(2);
  theTexture3.setOutlineColor(sf::Color(130,96,72));
  theTexture3.setTexture(&currentTexture3);
  theTexture3.setPosition(648,135);
  //The input boxes for character data
  Button teamButton(750,250,26,26);
  Button speedButton(750,300,26,26);
  Button hpButton(750,350,36,26);
  Button atkButton(750,400,36,26);
  Button defButton(750,450,36,26);
  Button rangeButton(750,500,26,26);
  sf::Text buttonTexts3[6];
  for (int a = 0; a < 6; a++)
    {
      buttonTexts3[a].setFont(font);
      buttonTexts3[a].setCharacterSize(15);
    }
  buttonTexts3[0].setString(stringConvert::toString(currentTeam));
  buttonTexts3[0].setPosition(755,255);
  buttonTexts3[1].setString(stringConvert::toString(currentSpeed));
  buttonTexts3[1].setPosition(755,305);
  buttonTexts3[2].setString(stringConvert::toString(currentHP));
  buttonTexts3[2].setPosition(755,355);
  buttonTexts3[3].setString(stringConvert::toString(currentATK));
  buttonTexts3[3].setPosition(755,405);
  buttonTexts3[4].setString(stringConvert::toString(currentDEF));
  buttonTexts3[4].setPosition(755,455);
  buttonTexts3[5].setString(stringConvert::toString(currentRange));
  buttonTexts3[5].setPosition(755,505);


  //For Tab4, or Audio tab:
  sf::Text tab4text[7];
  sf::Text musicTeam1;//, musicTeam2;
  //Need text arrays for each team
  sf::Text musicText1[10];//, musicText2[10];
  for (int a = 0; a < 7; a++)
    {
      tab4text[a].setFont(font);
      tab4text[a].setCharacterSize(15);
    }
  for (int a = 0; a < 5; a++)
    {
      soundText[a].setFont(font);
      soundText[a].setCharacterSize(15);
      soundText[a].setString(soundName[a]);
    }
  musicTeam1.setFont(font);
  //musicTeam2.setFont(font);
  tab4text[0].setString("Background Music Team 1:");
  //tab4text[1].setString("Background Music Team 2:");
  tab4text[2].setString("Walking Sound:");
  tab4text[3].setString("Attacking Sound:");
  tab4text[4].setString("Dying Sound:");
  tab4text[5].setString("Winning Game Sound:");
  tab4text[6].setString("Changing Team Sound:");
  musicTeam1.setString(musicName[music1]);
  //musicTeam2.setString(musicName[music2]);
  musicTeam1.setCharacterSize(15);
  //musicTeam2.setCharacterSize(15);
  tab4text[0].setPosition(28,60);
  //tab4text[1].setPosition(28,380);
  for (int a = 2; a < 7; a++)
    {
      tab4text[a].setPosition(500,75 + (a-2)*100);
      soundText[a-2].setPosition(505,105 + (a-2)*100);
      soundText[a-2].setString(soundName[a-2]);
    }
  musicTeam1.setPosition(210,60);
  //musicTeam2.setPosition(210,380);
  //Create and list the music, as well as the boxes they're in
  int loopVar4 = 0;
  //Create buttons for each music on each team
  Button* musicBox1;
  //Button* musicBox2;
  musicBox1 = new Button[10];
  //musicBox2 = new Button[10];
  //Loop for each team background music
  while (loopVar4 < 10)
    {
      //Create sound based on number in array
      if (musicName[loopVar4] != "")
	{
	  music[loopVar4].openFromFile("Data/Music/" + musicName[loopVar4] + ".ogg");
	}
      musicText1[loopVar4].setFont(font);
      musicText1[loopVar4].setString(musicName[loopVar4]);
      musicText1[loopVar4].setCharacterSize(15);
      musicText1[loopVar4].setPosition(50,85 + loopVar4 * 30);
      musicBox1[loopVar4].createButton(48,80 + loopVar4*30,96,26);
      //Next music
      loopVar4++;
    }
  /*loopVar4 = 0;
  while (loopVar4 < 10)

    {
      //Boxes for background music team 2
      musicText2[loopVar4].setFont(font);
      musicText2[loopVar4].setString(musicName[loopVar4]);
      musicText2[loopVar4].setCharacterSize(15);
      musicText2[loopVar4].setPosition(50,405 + loopVar4 * 30);
      musicBox2[loopVar4].createButton(48,400 + loopVar4*30,96,26);
      //Next music
      loopVar4++;
      }*/
  Button * soundButtons;
  soundButtons = new Button[5];
  for (int a = 0; a < 5; a++)
    {
      soundButtons[a].createButton(500, 100 + (a*100), 96, 26);
    }
  sf::Text playTexts[7];
  Button * playButtons;
  playButtons = new Button[7];
  for (int a = 0; a < 7; a++)
    {
      playTexts[a].setString("Play");
      playTexts[a].setFont(font);
      playTexts[a].setCharacterSize(15);
    }
  playButtons[0].createButton(228,88,36,26);
  playTexts[0].setPosition(233,93);
  //playButtons[1].createButton(228,408,36,26);
  //playTexts[1].setPosition(233,413);
  for (int a = 2; a < 7; a++)
    {
      playButtons[a].createButton(638,98 + (a-2)*100,36,26);
      playTexts[a].setPosition(643,103 + (a-2)*100);
    }

  //Now draw based on which tab you're in
  if (tab == 1)
    {
      inputSizeX.draw(&window);
      inputSizeY.draw(&window);
      for (int a = 0; a < 5; a++)
	{
	  window.draw(texts1[a]);
	}
      //Only print the textures that exist, and their boxes
      for (int a = 0; a < loopVar1; a++)
	{
	  tileTextureBox[a].draw(&window);
	  window.draw(tileTextureBoxText[a]);
	}
      window.draw(theTexture);
      window.draw(textureOn1);
    }

  if (tab == 2)
    {
      for (int a = 0; a < 4; a++)
	{
	  window.draw(texts2[a]);
	}
      //Only print the textures that exist, and their boxes
      for (int a = 0; a < loopVar2; a++)
	{
	  objectTextureBox[a].draw(&window);
	  window.draw(objectTextureBoxText[a]);
	}
      //Same with defined objects
      for (int a = 0; a < loopVar2c; a++)
	{
	  objectDefineBox[a].draw(&window);
	  window.draw(objectDefineText[a]);
	}
      window.draw(theTexture2);
      window.draw(textureOn2);
      moveCostButton.draw(&window);
      passableButton.draw(&window);
      window.draw(buttonTexts2[0]);
      window.draw(buttonTexts2[1]);
    }

  if (tab == 3)
    {
      for (int a = 0; a < 10; a++)
	{
	  window.draw(texts3[a]);
	}
      //Only print the textures that exist, and their boxes
      for (int a = 0; a < loopVar3; a++)
	{
	  charTextureBox[a].draw(&window);
	  window.draw(charTextureText[a]);
	}
      //Defined characters
      for (int a = 0; a < loopVar3c; a++)
	{
	  characterDefineBox[a].draw(&window);
	  window.draw(characterDefineText[a]);
	}
      window.draw(theTexture3);
      window.draw(textureOn3);
      teamButton.draw(&window);
      speedButton.draw(&window);
      hpButton.draw(&window);
      atkButton.draw(&window);
      defButton.draw(&window);
      rangeButton.draw(&window);
      for (int a = 0; a < 6; a++)
	{
	  window.draw(buttonTexts3[a]);
	}
    }
  
  if (tab == 4)
    {
      window.draw(musicTeam1);
      //window.draw(musicTeam2);
      for (int a = 0; a < 5; a++)
	{
	  soundButtons[a].draw(&window);
	  window.draw(soundText[a]);
	}
      window.draw(tab4text[0]);
	  playButtons[0].draw(&window);
	  window.draw(playTexts[0]);
      for (int a = 2; a < 7; a++)
	{
	  window.draw(tab4text[a]);
	  playButtons[a].draw(&window);
	  window.draw(playTexts[a]);
	}
      //Only print the music that exists, and their boxes
      for (int a = 0; a < loopVar4; a++)
	{
	  musicBox1[a].draw(&window);
	  //musicBox2[a].draw(&window);
	  window.draw(musicText1[a]);
	  //window.draw(musicText2[a]);
	}
    }
  window.draw(cursor);
  window.display();
}

void onLoad()
{
  for (int x = 0; x < 100; x++)
    {
      for (int y = 0; y < 100; y++)
	{
	  layer1data[x][y] = 0;
	  layer2data[x][y] = 0;
	  layer3data[x][y] = 0;
	}
    }
  //Set all text to blank, so loops can stop when it is blank
  for (int a = 0; a < 40; a++)
    {
      tileName[a] = "";
      objectName[a] = "";
      objDefName[a] = "";
      typeName[a] = "";
      charName[a] = "";
      charDefName[a] = "";
    }
}









int main()
{
  int currentTab = 1;
  bool musicOn[2];
  bool soundOn[5];
  for (int a = 0; a < 2; a++)
    {
      musicOn[a] = false;
    }
  for (int a = 0; a < 5; a++)
    {
      soundOn[a] = false;
    }
  int currentMouseX;
  int currentMouseY;
  //Start with tab 1, all reDraw functions have the (X), where X is the tab
  //1 is Tile, 2 is Object, 3 is Char, 4 is Audio
  font.loadFromFile("Cantarell-Regular.otf");
  onLoad();
  std::string userInput1[40], userInput2[40], userInput3[40], userDefs2[40], userDefs3[40], userMusic[10], userSound[5];
  int inputTimer = 10000;
  int buttonTimer = 10000;
  reDraw(currentTab);
  while (window.isOpen())
    {
      inputTimer--;
      buttonTimer--;
      sf::Event event;
      while (window.pollEvent(event))
        {
	  if (event.type == sf::Event::Closed)
	    window.close();
        }
      if (event.type == sf::Event::TextEntered)
	{
	  //tab1 Tile Textures
	  for (int a = 0; a < 20; a++)
	    {
	      if (currentMouseX >= 50 && currentMouseX < 150 && currentMouseY > 135 + (a*30) && currentMouseY < 165 + (a*30) && currentTab == 1)
		{
		  if (event.text.unicode < 128 && inputTimer < 0)
		    {
		      inputTimer = 10000;
		      if (event.text.unicode == 8)
			{
			  if (userInput1[a].size() > 0)
			    {
			      userInput1[a] = userInput1[a].substr(0, userInput1[a].size()-1);
			    }
			}
		      else
			{
			  userInput1[a] += static_cast<char>(event.text.unicode);
			}
		      tileName[a] = userInput1[a];
		      reDraw(currentTab);
		    }
		}
	    }
	  for (int a = 20; a < 40; a++)
	    {
	      if (currentMouseX >= 150 && currentMouseX < 250 && currentMouseY > 135 + ((a-20)*30) && currentMouseY < 165 + ((a-20)*30) && currentTab == 1)
		{
		  if (event.text.unicode < 128 && inputTimer < 0)
		    {
		      inputTimer = 10000;
		      if (event.text.unicode == 8)
			{
			  if (userInput1[a].size() > 0)
			    {
			      userInput1[a] = userInput1[a].substr(0, userInput1[a].size()-1);
			    }
			}
		      else
			{
			  userInput1[a] += static_cast<char>(event.text.unicode);
			}
		      tileName[a] = userInput1[a];
		      reDraw(currentTab);
		    }
		}
	    }
	  //tab2 Object Textures
	  for (int a = 0; a < 20; a++)
	    {
	      if (currentMouseX >= 8 && currentMouseX < 108 && currentMouseY > 135 + (a*30) && currentMouseY < 165 + (a*30) && currentTab == 2)
		{
		  if (event.text.unicode < 128 && inputTimer < 0)
		    {
		      inputTimer = 10000;
		      if (event.text.unicode == 8)
			{
			  if (userInput2[a].size() > 0)
			    {
			      userInput2[a] = userInput2[a].substr(0, userInput2[a].size()-1);
			    }
			}
		      else
			{
			  userInput2[a] += static_cast<char>(event.text.unicode);
			}
		      objectName[a] = userInput2[a];
		      reDraw(currentTab);
		    }
		}
	    }
	  for (int a = 20; a < 40; a++)
	    {
	      if (currentMouseX >= 108 && currentMouseX < 208 && currentMouseY > 135 + ((a-20)*30) && currentMouseY < 165 + ((a-20)*30) && currentTab == 2)
		{
		  if (event.text.unicode < 128 && inputTimer < 0)
		    {
		      inputTimer = 10000;
		      if (event.text.unicode == 8)
			{
			  if (userInput2[a].size() > 0)
			    {
			      userInput2[a] = userInput2[a].substr(0, userInput2[a].size()-1);
			    }
			}
		      else
			{
			  userInput2[a] += static_cast<char>(event.text.unicode);
			}
		      objectName[a] = userInput2[a];
		      reDraw(currentTab);
		    }
		}
	    }
	  //tab2 Object Definitions
	  for (int a = 0; a < 20; a++)
	    {
	      if (currentMouseX >= 448 && currentMouseX < 548 && currentMouseY > 135 + (a*30) && currentMouseY < 165 + (a*30) && currentTab == 2)
		{
		  if (event.text.unicode < 128 && inputTimer < 0)
		    {
		      inputTimer = 10000;
		      if (event.text.unicode == 8)
			{
			  if (userDefs2[a].size() > 0)
			    {
			      userDefs2[a] = userDefs2[a].substr(0, userDefs2[a].size()-1);
			    }
			}
		      else
			{
			  userDefs2[a] += static_cast<char>(event.text.unicode);
			}
		      objDefName[a] = userDefs2[a];
		      reDraw(currentTab);
		    }
		}
	    }
	  for (int a = 20; a < 40; a++)
	    {
	      if (currentMouseX >= 548 && currentMouseX < 648 && currentMouseY > 135 + ((a-20)*30) && currentMouseY < 165 + ((a-20)*30) && currentTab == 2)
		{
		  if (event.text.unicode < 128 && inputTimer < 0)
		    {
		      inputTimer = 10000;
		      if (event.text.unicode == 8)
			{
			  if (userDefs2[a].size() > 0)
			    {
			      userDefs2[a] = userDefs2[a].substr(0, userDefs2[a].size()-1);
			    }
			}
		      else
			{
			  userDefs2[a] += static_cast<char>(event.text.unicode);
			}
		      objDefName[a] = userDefs2[a];
		      reDraw(currentTab);
		    }
		}
	    }
	  //tab3 Character Textures
	  for (int a = 0; a < 20; a++)
	    {
	      if (currentMouseX >= 8 && currentMouseX < 108 && currentMouseY > 135 + (a*30) && currentMouseY < 165 + (a*30) && currentTab == 3)
		{
		  if (event.text.unicode < 128 && inputTimer < 0)
		    {
		      inputTimer = 10000;
		      if (event.text.unicode == 8)
			{
			  if (userInput3[a].size() > 0)
			    {
			      userInput3[a] = userInput3[a].substr(0, userInput3[a].size()-1);
			    }
			}
		      else
			{
			  userInput3[a] += static_cast<char>(event.text.unicode);
			}
		      charName[a] = userInput3[a];
		      reDraw(currentTab);
		    }
		}
	    }
	  for (int a = 20; a < 40; a++)
	    {
	      if (currentMouseX >= 108 && currentMouseX < 208 && currentMouseY > 135 + ((a-20)*30) && currentMouseY < 165 + ((a-20)*30) && currentTab == 3)
		{
		  if (event.text.unicode < 128 && inputTimer < 0)
		    {
		      inputTimer = 10000;
		      if (event.text.unicode == 8)
			{
			  if (userInput3[a].size() > 0)
			    {
			      userInput3[a] = userInput3[a].substr(0, userInput3[a].size()-1);
			    }
			}
		      else
			{
			  userInput3[a] += static_cast<char>(event.text.unicode);
			}
		      charName[a] = userInput3[a];
		      reDraw(currentTab);
		    }
		}
	    }
	  //tab3 Object Definitions
	  for (int a = 0; a < 20; a++)
	    {
	      if (currentMouseX >= 448 && currentMouseX < 548 && currentMouseY > 135 + (a*30) && currentMouseY < 165 + (a*30) && currentTab == 3)
		{
		  if (event.text.unicode < 128 && inputTimer < 0)
		    {
		      inputTimer = 10000;
		      if (event.text.unicode == 8)
			{
			  if (userDefs3[a].size() > 0)
			    {
			      userDefs3[a] = userDefs3[a].substr(0, userDefs3[a].size()-1);
			    }
			}
		      else
			{
			  userDefs3[a] += static_cast<char>(event.text.unicode);
			}
		      charDefName[a] = userDefs3[a];
		      reDraw(currentTab);
		    }
		}
	    }
	  for (int a = 20; a < 40; a++)
	    {
	      if (currentMouseX >= 548 && currentMouseX < 648 && currentMouseY > 135 + ((a-20)*30) && currentMouseY < 165 + ((a-20)*30) && currentTab == 3)
		{
		  if (event.text.unicode < 128 && inputTimer < 0)
		    {
		      inputTimer = 10000;
		      if (event.text.unicode == 8)
			{
			  if (userDefs3[a].size() > 0)
			    {
			      userDefs3[a] = userDefs3[a].substr(0, userDefs3[a].size()-1);
			    }
			}
		      else
			{
			  userDefs3[a] += static_cast<char>(event.text.unicode);
			}
		      charDefName[a] = userDefs3[a];
		      reDraw(currentTab);
		    }
		}
	    }
	  //Music/Audio, tab 4
	  for (int a = 0; a < 10; a++)
	    {
	      if (currentMouseX >= 50 && currentMouseX < 150 && currentMouseY > 80 + (a*30) && currentMouseY < 110 + (a*30) && currentTab == 4)
		{
		  if (event.text.unicode < 128 && inputTimer < 0)
		    {
		      inputTimer = 10000;
		      if (event.text.unicode == 8)
			{
			  if (userMusic[a].size() > 0)
			    {
			      userMusic[a] = userMusic[a].substr(0, userMusic[a].size()-1);
			    }
			}
		      else
			{
			  userMusic[a] += static_cast<char>(event.text.unicode);
			}
		      musicName[a] = userMusic[a];
		      reDraw(currentTab);
		    }
		}
	    }
	  for (int a = 0; a < 5; a++)
	    {
	      if (currentMouseX >= 500 && currentMouseX < 600 && currentMouseY > 100 + (a*100) && currentMouseY < 130 + (a*100) && currentTab == 4)
		{
		  if (event.text.unicode < 128 && inputTimer < 0)
		    {
		      inputTimer = 10000;
		      if (event.text.unicode == 8)
			{
			  if (userSound[a].size() > 0)
			    {
			      userSound[a] = userSound[a].substr(0, userSound[a].size()-1);
			    }
			}
		      else
			{
			  userSound[a] += static_cast<char>(event.text.unicode);
			}
		      soundName[a] = userSound[a];
		      reDraw(currentTab);
		    }
		}
	    }
	  
	}
      if (event.type == sf::Event::MouseMoved)
	{
	  //Mathematical formula for moving the cursor boxSize units
	  if (event.mouseMove.x > 800)
	    {
	      reDraw(currentTab);
	    }
	  cursorY = ceil((event.mouseMove.y)/boxSize)*boxSize;
	  cursorX = ceil((event.mouseMove.x - (800%boxSize))/boxSize)*boxSize + (800%boxSize);
	  currentMouseX = event.mouseMove.x;
	  currentMouseY = event.mouseMove.y;
	}
      if (event.type == sf::Event::MouseButtonPressed)
	{
	  if (event.mouseButton.button == sf::Mouse::Left)
	    {
	      //Saving the data
	      if (event.mouseButton.x >= 420 && event.mouseButton.x < 470 && event.mouseButton.y > 20 && event.mouseButton.y < 50 && buttonTimer < 0)
		{
		  buttonTimer = 10000;
		  dataFile.open("Data/Game Files/data.txt", std::ofstream::out | std::ofstream::trunc);
		  dataFile << gridSizeY << "\n";
		  dataFile << gridSizeX << "\n";
		  dataFile << objects << "\n";
		  dataFile << characters << "\n";
		  dataFile << "Data/Music/" << musicName[music1] << ".ogg" << "\n";
		  for (int a = 0; a < 5; a++)
		  {
		    dataFile << "Data/Sounds/" << soundName[a] << ".wav" << "\n"; 
		  }
		  for (int x = 0; x <= gridSizeX; x++)
		    {
		      for (int y = 0; y <= gridSizeY; y++)
			{
			  if (layer1data[y][x] > 0)
			    {
			      dataFile << layer1[y][x].getFileName() << "\n";
			    }
			}
		    }
		  for (int x = 0; x <= gridSizeX; x++)
		    {
		      for (int y = 0; y <= gridSizeY; y++)
			{
			  if (layer2data[y][x] > 0)
			    {
			      dataFile << layer2[y][x].getFileName() << " " << layer2[y][x].getPositionX() << " " << layer2[y][x].getPositionY() << " " << layer2[y][x].isPassable() << " " << layer2[y][x].getMoveCost() << "\n";
			    }
			}
		    }
		  for (int x = 0; x <= gridSizeX; x++)
		    {
		      for (int y = 0; y <= gridSizeY; y++)
			{
			  if (layer3data[y][x] > 0)
			    {
			      dataFile << layer3[y][x].getTeamID() << " " << layer3[y][x].getFileName() << " " << layer3[y][x].getName() << " " << layer3[y][x].getPositionX() << " " << layer3[y][x].getPositionY() << " " << layer3[y][x].getMaxSpeed() << " " << layer3[y][x].getMaxHitPoints() << " " << layer3[y][x].getMaxAtk() << " " << layer3[y][x].getMaxDef() << " " << layer3[y][x].getMaxRange() << "\n";
			    }
			}
		    }
		  dataFile.close();
		}
	      //The buttons for changing the texture, tab 1
	      for (int a = 0; a < 20; a++)
		{
		  if (event.mouseButton.x >= 50 && event.mouseButton.x < 150 && event.mouseButton.y > 135 + (a*30) && event.mouseButton.y < 165 + (a*30) && currentTab == 1 && buttonTimer < 0)
		    {
		      buttonTimer = 10000;
		      if (tileName[a] != "")
			{
			  currentTexture1 = tileTextures[a];
			  currentTextureNum1 = a;
			  reDraw(currentTab);
			}
		    }
		}
	      for (int a = 20; a < 40; a++)
		{
		  if (event.mouseButton.x >= 150 && event.mouseButton.x < 250 && event.mouseButton.y > 135 + ((a-20)*30) && event.mouseButton.y < 165 + ((a-20)*30) && currentTab == 1 && buttonTimer < 0)
		    {
		      buttonTimer = 10000;
		      if (tileName[a] != "")
			{
			  currentTexture1 = tileTextures[a];
			  currentTextureNum1 = a;
			  reDraw(currentTab);
			}
		    }
		}

	      //The buttons for changing the texture, tab 2
	      for (int a = 0; a < 20; a++)
		{
		  if (event.mouseButton.x >= 8 && event.mouseButton.x < 108 && event.mouseButton.y > 135 + (a*30) && event.mouseButton.y < 165 + (a*30) && currentTab == 2 && buttonTimer < 0)
		    {
		      buttonTimer = 10000;
		      if (objectName[a] != "")
			{
			  currentTexture2 = objectTextures[a];
			  currentTextureName2 = objectName[a];
			  reDraw(currentTab);
			}
		    }
		}
	      for (int a = 20; a < 40; a++)
		{
		  if (event.mouseButton.x >= 108 && event.mouseButton.x < 208 && event.mouseButton.y > 135 + ((a-20)*30) && event.mouseButton.y < 165 + ((a-20)*30) && currentTab == 2 && buttonTimer < 0)
		    {
		      buttonTimer = 10000;
		      if (objectName[a] != "")
			{
			  currentTexture2 = objectTextures[a];
			  currentTextureName2 = objectName[a];
			  reDraw(currentTab);
			}
		    }
		}

	      //The buttons for changing the definitions, tab 2
	      for (int a = 0; a < 20; a++)
		{
		  if (event.mouseButton.x >= 448 && event.mouseButton.x < 548 && event.mouseButton.y > 135 + (a*30) && event.mouseButton.y < 165 + (a*30) && currentTab == 2 && buttonTimer < 0)
		    {
		      buttonTimer = 10000;
		      if (objDefName[a] != "")
			{
			  currentTexture2 = objectDefs[a].getTexture();
			  currentPassable = objectDefs[a].isPassable();
			  currentMoveCost = objectDefs[a].getMoveCost();
			  currentTextureName2 = objectDefs[a].getFileName();
			  reDraw(currentTab);
			}
		    }
		}
	      for (int a = 20; a < 40; a++)
		{
		  if (event.mouseButton.x >= 548 && event.mouseButton.x < 648 && event.mouseButton.y > 135 + ((a-20)*30) && event.mouseButton.y < 165 + ((a-20)*30) && currentTab == 2 && buttonTimer < 0)
		    {
		      buttonTimer = 10000;
		      if (objDefName[a] != "")
			{
			  currentTexture2 = objectDefs[a].getTexture();
			  currentPassable = objectDefs[a].isPassable();
			  currentMoveCost = objectDefs[a].getMoveCost();
			  currentTextureName2 = objectDefs[a].getFileName();
			  reDraw(currentTab);
			}
		    }
		}

	      //The buttons for changing the texture, tab 3
	      for (int a = 0; a < 20; a++)
		{
		  if (event.mouseButton.x >= 8 && event.mouseButton.x < 108 && event.mouseButton.y > 135 + (a*30) && event.mouseButton.y < 165 + (a*30) && currentTab == 3 && buttonTimer < 0)
		    {
		      buttonTimer = 10000;
		      if (charName[a] != "")
			{
			  currentTexture3 = charTextures[a];
			  currentTextureName3 = charName[a];
			  reDraw(currentTab);
			}
		    }
		}
	      for (int a = 20; a < 40; a++)
		{
		  if (event.mouseButton.x >= 108 && event.mouseButton.x < 208 && event.mouseButton.y > 135 + ((a-20)*30) && event.mouseButton.y < 165 + ((a-20)*30) && currentTab == 3 && buttonTimer < 0)
		    {
		      buttonTimer = 10000;
		      if (charName[a] != "")
			{
			  currentTexture3 = charTextures[a];
			  currentTextureName3 = charName[a];
			  reDraw(currentTab);
			}
		    }
		}

	      //The buttons for changing the definitions, tab 3
	      for (int a = 0; a < 20; a++)
		{
		  if (event.mouseButton.x >= 448 && event.mouseButton.x < 548 && event.mouseButton.y > 135 + (a*30) && event.mouseButton.y < 165 + (a*30) && currentTab == 3 && buttonTimer < 0)
		    {
		      buttonTimer = 10000;
		      if (charDefName[a] != "")
			{
			  currentTexture3 = characterDefs[a].getTexture();
			  currentTeam = characterDefs[a].getTeamID();
			  currentName = characterDefs[a].getName();
			  currentSpeed = characterDefs[a].getMaxSpeed();
			  currentHP = characterDefs[a].getMaxHitPoints();
			  currentATK = characterDefs[a].getMaxAtk();
			  currentDEF = characterDefs[a].getMaxDef();
			  currentRange = characterDefs[a].getMaxRange();
			  currentTextureName3 = characterDefs[a].getFileName();
			  reDraw(currentTab);
			}
		    }
		}
	      for (int a = 20; a < 40; a++)
		{
		  if (event.mouseButton.x >= 548 && event.mouseButton.x < 648 && event.mouseButton.y > 135 + ((a-20)*30) && event.mouseButton.y < 165 + ((a-20)*30) && currentTab == 3 && buttonTimer < 0)
		    {
		      buttonTimer = 10000;
		      if (charDefName[a] != "")
			{
			  currentTexture3 = characterDefs[a].getTexture();
			  currentTeam = characterDefs[a].getTeamID();
			  currentName = characterDefs[a].getName();
			  currentSpeed = characterDefs[a].getMaxSpeed();
			  currentHP = characterDefs[a].getMaxHitPoints();
			  currentATK = characterDefs[a].getMaxAtk();
			  currentDEF = characterDefs[a].getMaxDef();
			  currentRange = characterDefs[a].getMaxRange();
			  currentTextureName3 = characterDefs[a].getFileName();
			  reDraw(currentTab);
			}
		    }
		}

	      //The buttons for changing music for team 1, tab 4
	      for (int a = 0; a < 10; a++)
		{
		  if (event.mouseButton.x >= 50 && event.mouseButton.x < 150 && event.mouseButton.y > 80 + (a*30) && event.mouseButton.y < 110 + (a*30) && currentTab == 4 && buttonTimer < 0)
		    {
		      buttonTimer = 10000;
		      if (musicName[a] != "")
			{
			  music1 = a;
			  reDraw(currentTab);
			}
		    }
		}

	      /*//The buttons for changing music for team 2, tab 4
	      for (int a = 0; a < 10; a++)
		{
		  if (event.mouseButton.x >= 50 && event.mouseButton.x < 150 && event.mouseButton.y > 400 + (a*30) && event.mouseButton.y < 430 + (a*30) && currentTab == 4 && buttonTimer < 0)
		    {
		      buttonTimer = 10000;
		      if (musicName[a] != "")
			{
			  music2 = a;
			  reDraw(currentTab);
			}
		    }
		    }*/
	      //Play music for team 1
	      if (event.mouseButton.x >= 230 && event.mouseButton.x <= 270 && event.mouseButton.y >= 90 && event.mouseButton.y <= 120 && buttonTimer < 0)
		{
		  buttonTimer = 30000;
		  if (musicOn[0] == false)
		    {
		      music[music1].play();
		      musicOn[0] = true;
		    }
		  else
		    {
		      music[music1].stop();
		      musicOn[0] = false;
		    }
		}
	      //Play music for team 2
	      if (event.mouseButton.x >= 230 && event.mouseButton.x <= 270 && event.mouseButton.y >= 410 && event.mouseButton.y <= 440 && buttonTimer < 0)
		{
		  buttonTimer = 30000;
		  if (musicOn[1] == false)
		    {
		      music[music2].play();
		      musicOn[1] = true;
		    }
		  else
		    {
		      music[music2].stop();
		      musicOn[1] = false;
		    }
		}
	      //Play sounds
	      for (int a = 0; a < 5; a++)
		{
		  if (event.mouseButton.x >= 640 && event.mouseButton.x <= 670 && event.mouseButton.y >= 100 + (a*100) && event.mouseButton.y <= 140 + (a*100) && buttonTimer < 0)
		    {
		      buttonTimer = 30000;
		      //Create the sounds, if they exist
		      for (int b = 0; b < 5; b++)
			{
			  if (soundName[b] != "")
			    {
			      soundBuffers[b].loadFromFile("Data/Sounds/" + soundName[b] + ".wav");
			      sounds[b].setBuffer(soundBuffers[b]);
			      sounds[b].setVolume(100);
			    }
			}
		      sounds[a].play();
		    }
		}

	      //If mouse X and Y position is inside the tab X and Y positions
	      if (event.mouseButton.x >= 1 && event.mouseButton.x < 102 && event.mouseButton.y > 1 && event.mouseButton.y < 30)
		{
		  //Set tab 1 on, re-draw based on new tab selection
		  reDraw(1);
		  currentTab = 1;
		}
	      else if (event.mouseButton.x >= 102 && event.mouseButton.x < 202 && event.mouseButton.y >= 1 && event.mouseButton.y < 30)
		{
		  //Set tab 2 on, re-draw based on new tab selection
		  reDraw(2);
		  currentTab = 2;
		}
	      else if (event.mouseButton.x >= 202 && event.mouseButton.x < 302 && event.mouseButton.y >= 1 && event.mouseButton.y < 30)
		{
		  //ETC
		  reDraw(3);
		  currentTab = 3;
		}
	      else if (event.mouseButton.x >= 302 && event.mouseButton.x < 402 && event.mouseButton.y >= 1 && event.mouseButton.y < 30)
		{
		  //ETC
		  reDraw(4);
		  currentTab = 4;
		}
	      //If the mouse is clicked in the grid X size input, increase X map size
	      else if (event.mouseButton.x >= 45 && event.mouseButton.x <= 85 && event.mouseButton.y >= 65 && event.mouseButton.y <= 95 && currentTab == 1 && buttonTimer < 0)
		{
		  buttonTimer = 10000;
		  gridSizeX++;
		  reDraw(currentTab);
		}
	      //Same for the Y map size
	      else if (event.mouseButton.x >= 105 && event.mouseButton.x <= 145 && event.mouseButton.y >= 65 && event.mouseButton.y <= 95 && currentTab == 1 && buttonTimer < 0)
		{
		  buttonTimer = 10000;
		  gridSizeY++;
		  reDraw(currentTab);
		}
	      //Move Cost
	      else if (event.mouseButton.x >= 750 && event.mouseButton.x <= 790 && event.mouseButton.y >= 250 && event.mouseButton.y <= 280 && currentTab == 2 && buttonTimer < 0)
		{
		  buttonTimer = 10000;
		  currentMoveCost++;
		  reDraw(currentTab);
		}
	      //Passable
	      else if (event.mouseButton.x >= 750 && event.mouseButton.x <= 780 && event.mouseButton.y >= 300 && event.mouseButton.y <= 330 && currentTab == 2 && buttonTimer < 0)
		{
		  buttonTimer = 10000;
		  if (currentPassable < 1)
		    {
		      currentPassable++;
		      reDraw(currentTab);
		    }
		}
	      //Team
	      else if (event.mouseButton.x >= 750 && event.mouseButton.x <= 780 && event.mouseButton.y >= 250 && event.mouseButton.y <= 280 && currentTab == 3 && buttonTimer < 0)
		{
		  buttonTimer = 10000;
		  if (currentTeam < 2)
		    {
		      currentTeam++;
		      reDraw(currentTab);
		    }
		}
	      //Speed
	      else if (event.mouseButton.x >= 750 && event.mouseButton.x <= 780 && event.mouseButton.y >= 300 && event.mouseButton.y <= 330 && currentTab == 3 && buttonTimer < 0)
		{
		  buttonTimer = 10000;
		  currentSpeed++;
		  reDraw(currentTab);
		}
	      //HP
	      else if (event.mouseButton.x >= 750 && event.mouseButton.x <= 790 && event.mouseButton.y >= 350 && event.mouseButton.y <= 380 && currentTab == 3 && buttonTimer < 0)
		{
		  buttonTimer = 10000;
		  currentHP++;
		  reDraw(currentTab);
		}
	      //ATK
	      else if (event.mouseButton.x >= 750 && event.mouseButton.x <= 790 && event.mouseButton.y >= 400 && event.mouseButton.y <= 430 && currentTab == 3 && buttonTimer < 0)
		{
		  buttonTimer = 10000;
		  currentATK++;
		  reDraw(currentTab);
		}
	      //DEF
	      else if (event.mouseButton.x >= 750 && event.mouseButton.x <= 790 && event.mouseButton.y >= 450 && event.mouseButton.y <= 480 && currentTab == 3 && buttonTimer < 0)
		{
		  buttonTimer = 10000;
		  currentDEF++;
		  reDraw(currentTab);
		}
	      //Range
	      else if (event.mouseButton.x >= 750 && event.mouseButton.x <= 780 && event.mouseButton.y >= 500 && event.mouseButton.y <= 530 && currentTab == 3 && buttonTimer < 0)
		{
		  buttonTimer = 10000;
		  currentRange++;
		  reDraw(currentTab);
		}
	      else if (event.mouseButton.x > 800 && event.mouseButton.x < 1600)
		{
		  //This will be adding the data to the arrays
		  if (currentTab == 1)//If it is a tile
		    {
		      if (layer1data[inBoxX][inBoxY] < 1)
			{
			  layer1data[inBoxX][inBoxY] = 1;
			  layer1[inBoxX][inBoxY].setTexture(currentTexture1);
			  layer1[inBoxX][inBoxY].setFileName("Data/Tiles/" + tileName[currentTextureNum1] + ".png");
			}
		    }
		  else if (currentTab == 2)//If it is an object
		    {
		      if (layer2data[inBoxX][inBoxY] < 1)
			{
			  objects++;
			  layer2data[inBoxX][inBoxY] = 1;
			  layer2[inBoxX][inBoxY].setTexture(currentTexture2);
			  layer2[inBoxX][inBoxY].setEditorPosition(inBoxX,inBoxY);
			  layer2[inBoxX][inBoxY].setFileName("Data/Objects/" + currentTextureName2 + ".png");
			  if (currentPassable == 0)
			    {
			      layer2[inBoxX][inBoxY].setPassable(false);
			    }
			  else
			    {
			      layer2[inBoxX][inBoxY].setPassable(true);
			    }
			  layer2[inBoxX][inBoxY].setMoveCost(currentMoveCost);
			}
		    }
		  else if (currentTab == 3)//If it is a character
		    {
		      if (layer3data[inBoxX][inBoxY] < 1)
			{
			  characters++;
			  characterID++;
			  layer3data[inBoxX][inBoxY] = 1;
			  layer3[inBoxX][inBoxY].setTexture(currentTexture3);
			  layer3[inBoxX][inBoxY].setFileName("Data/Characters/" + currentTextureName3 + ".png");
			  layer3[inBoxX][inBoxY].setEditorPosition(inBoxX,inBoxY);
			  layer3[inBoxX][inBoxY].setName(currentTextureName3 + stringConvert::toString(characterID));
			  layer3[inBoxX][inBoxY].setTeamID(currentTeam);
			  layer3[inBoxX][inBoxY].setMaxSpeed(currentSpeed);
			  layer3[inBoxX][inBoxY].setMaxHitPoints(currentHP);
			  layer3[inBoxX][inBoxY].setMaxAtk(currentATK);
			  layer3[inBoxX][inBoxY].setMaxDef(currentDEF);
			  layer3[inBoxX][inBoxY].setMaxRange(currentRange);
			}
		    }
		  reDraw(currentTab);
		}
	    }
	  if (event.mouseButton.button == sf::Mouse::Right) //Right-click mouse
	    {
	      //If the mouse is clicked in the grid X size input, decrease X map size
	      if (event.mouseButton.x >= 45 && event.mouseButton.x <= 85 && event.mouseButton.y >= 65 && event.mouseButton.y <= 95 && currentTab == 1 && buttonTimer < 0)
		{
		  buttonTimer = 10000;
		  gridSizeX--;
		  reDraw(currentTab);
		}
	      //Same for the Y map size
	      else if (event.mouseButton.x >= 105 && event.mouseButton.x <= 145 && event.mouseButton.y >= 65 && event.mouseButton.y <= 95 && currentTab == 1 && buttonTimer < 0)
		{
		  buttonTimer = 10000;
		  gridSizeY--;
		  reDraw(currentTab);
		}
	      //Saving an object definition, tab 2
	      for (int a = 0; a < 20; a++)
		{
		  if (event.mouseButton.x >= 448 && event.mouseButton.x < 548 && event.mouseButton.y > 135 + (a*30) && event.mouseButton.y < 165 + (a*30) && currentTab == 2 && buttonTimer < 0)
		    {
		      buttonTimer = 10000;
		      objectDefs[a].setTexture(currentTexture2);
		      objectDefs[a].setPassable(currentPassable);
		      objectDefs[a].setMoveCost(currentMoveCost);
		      objectDefs[a].setFileName(currentTextureName2);
		    }
		}
	      for (int a = 20; a < 40; a++)
		{
		  if (event.mouseButton.x >= 548 && event.mouseButton.x < 648 && event.mouseButton.y > 135 + ((a-20)*30) && event.mouseButton.y < 165 + ((a-20)*30) && currentTab == 2 && buttonTimer < 0)
		    {
		      buttonTimer = 10000;
		      objectDefs[a].setTexture(currentTexture2);
		      objectDefs[a].setPassable(currentPassable);
		      objectDefs[a].setMoveCost(currentMoveCost);
		      objectDefs[a].setFileName(currentTextureName2);
		    }
		}

	      //Saving a character definition, tab 3
	      for (int a = 0; a < 20; a++)
		{
		  if (event.mouseButton.x >= 448 && event.mouseButton.x < 548 && event.mouseButton.y > 135 + (a*30) && event.mouseButton.y < 165 + (a*30) && currentTab == 3 && buttonTimer < 0)
		    {
		      buttonTimer = 10000;
		      characterDefs[a].setTexture(currentTexture3);
		      characterDefs[a].setTeamID(currentTeam);
		      characterDefs[a].setName(currentTextureName3 + stringConvert::toString(characterID));
		      characterDefs[a].setMaxSpeed(currentSpeed);
		      characterDefs[a].setMaxHitPoints(currentHP);
		      characterDefs[a].setMaxAtk(currentATK);
		      characterDefs[a].setMaxDef(currentDEF);
		      characterDefs[a].setMaxRange(currentRange);
		      characterDefs[a].setFileName(currentTextureName3);
		    }
		}
	      for (int a = 20; a < 40; a++)
		{
		  if (event.mouseButton.x >= 548 && event.mouseButton.x < 648 && event.mouseButton.y > 135 + ((a-20)*30) && event.mouseButton.y < 165 + ((a-20)*30) && currentTab == 3 && buttonTimer < 0)
		    {
		      buttonTimer = 10000;
		      characterDefs[a].setTexture(currentTexture3);
		      characterDefs[a].setTeamID(currentTeam);
		      characterDefs[a].setName(currentTextureName3 + stringConvert::toString(characterID));
		      characterDefs[a].setMaxSpeed(currentSpeed);
		      characterDefs[a].setMaxHitPoints(currentHP);
		      characterDefs[a].setMaxAtk(currentATK);
		      characterDefs[a].setMaxDef(currentDEF);
		      characterDefs[a].setMaxRange(currentRange);
		      characterDefs[a].setFileName(currentTextureName3);
		    }
		}

	      //Move Cost
	      if (event.mouseButton.x >= 750 && event.mouseButton.x <= 790 && event.mouseButton.y >= 250 && event.mouseButton.y <= 280 && currentTab == 2 && buttonTimer < 0)
		{
		  buttonTimer = 10000;
		  if (currentMoveCost > 0)
		    {
		      currentMoveCost--;
		    }
		  reDraw(currentTab);
		}
	      //Passable
	      else if (event.mouseButton.x >= 750 && event.mouseButton.x <= 780 && event.mouseButton.y >= 300 && event.mouseButton.y <= 330 && currentTab == 2 && buttonTimer < 0)
		{
		  buttonTimer = 10000;
		  if (currentPassable > 0)
		    {
		      currentPassable--;
		      reDraw(currentTab);
		    }
		}
	      //Team
	      else if (event.mouseButton.x >= 750 && event.mouseButton.x <= 780 && event.mouseButton.y >= 250 && event.mouseButton.y <= 280 && currentTab == 3 && buttonTimer < 0)
		{
		  buttonTimer = 10000;
		  if (currentTeam > 1)
		    {
		      currentTeam--;
		      reDraw(currentTab);
		    }
		}
	      //Speed
	      else if (event.mouseButton.x >= 750 && event.mouseButton.x <= 780 && event.mouseButton.y >= 300 && event.mouseButton.y <= 330 && currentTab == 3 && buttonTimer < 0)
		{
		  buttonTimer = 10000;
		  if (currentSpeed > 0)
		    {
		      currentSpeed--;
		    }
		  reDraw(currentTab);
		}
	      //HP
	      else if (event.mouseButton.x >= 750 && event.mouseButton.x <= 790 && event.mouseButton.y >= 350 && event.mouseButton.y <= 380 && currentTab == 3 && buttonTimer < 0)
		{
		  buttonTimer = 10000;
		  if (currentHP > 1)
		    {
		      currentHP--;
		    }
		  reDraw(currentTab);
		}
	      //ATK
	      else if (event.mouseButton.x >= 750 && event.mouseButton.x <= 790 && event.mouseButton.y >= 400 && event.mouseButton.y <= 430 && currentTab == 3 && buttonTimer < 0)
		{
		  buttonTimer = 10000;
		  if (currentATK > 0)
		    {
		      currentATK--;
		    }
		  reDraw(currentTab);
		}
	      //DEF
	      else if (event.mouseButton.x >= 750 && event.mouseButton.x <= 790 && event.mouseButton.y >= 450 && event.mouseButton.y <= 480 && currentTab == 3 && buttonTimer < 0)
		{
		  buttonTimer = 10000;
		  if (currentDEF > 0)
		    {
		      currentDEF--;
		    }
		  reDraw(currentTab);
		}
	      //Range
	      else if (event.mouseButton.x >= 750 && event.mouseButton.x <= 780 && event.mouseButton.y >= 500 && event.mouseButton.y <= 530 && currentTab == 3 && buttonTimer < 0)
		{
		  buttonTimer = 10000;
		  if (currentRange > 1)
		    {
		      currentRange--;
		    }
		  reDraw(currentTab);
		}

	      else if (event.mouseButton.x > 800 && event.mouseButton.x < 1600)
		{
		  //This will be deleting the data from the arrays
		  if (currentTab == 1)//If it is a tile
		    {
		      layer1data[inBoxX][inBoxY] = 0;
		      layer1[inBoxX][inBoxY].setTexture(blankTexture);
		    }
		  else if (currentTab == 2)//If it is an object
		    {
		      if (layer2data[inBoxX][inBoxY] == 1)
			{
			  objects--;
			  layer2data[inBoxX][inBoxY] = 0;
			  layer2[inBoxX][inBoxY].setTexture(blankTexture);
			}
		    }
		  else if (currentTab == 3)//If it is a character
		    {
		      if (layer3data[inBoxX][inBoxY] == 1)
			{
			  characters--;
			  layer3data[inBoxX][inBoxY] = 0;
			  layer3[inBoxX][inBoxY].setTexture(blankTexture);
			}
		    }
		  reDraw(currentTab);
		}
	    }
	}
    }
  return 0;
}
