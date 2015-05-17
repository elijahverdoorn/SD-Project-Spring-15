#ifndef _BUTTON_
#define _BUTTON_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string.h>
#include <sstream>
#include <iostream>
#include <math.h>

class Button
{
  int posx, posy, width, height;
  sf::RectangleShape *rect;
 public:
  //Constructors
  Button();
  Button(int x, int y, int w, int h);

  //member methods
  void draw(sf::RenderWindow *window);
  void createButton(int x, int y, int w, int h);
  //operators
};
#endif //_BUTTON_
