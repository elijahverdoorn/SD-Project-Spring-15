#include "Button.h"
using namespace std;
Button::Button()
{
  rect = new sf::RectangleShape;
  rect->setSize(sf::Vector2f(96,26));
  rect->setOutlineThickness(2);
  rect->setOutlineColor(sf::Color(130,96,72));
  rect->setFillColor(sf::Color(164,150,132));
  rect->setPosition(0,0);
}
Button::Button(int x, int y, int w, int h)
{
  rect = new sf::RectangleShape;
  rect->setSize(sf::Vector2f(w,h));
  rect->setOutlineThickness(2);
  rect->setOutlineColor(sf::Color(130,96,72));
  rect->setFillColor(sf::Color(164,150,132));
  rect->setPosition(x,y);
}
void Button::draw(sf::RenderWindow *window)
{
  window->draw(*rect);
}
void Button::createButton(int x, int y, int w, int h)
{
  rect->setSize(sf::Vector2f(w,h));
  rect->setOutlineThickness(2);
  rect->setOutlineColor(sf::Color(130,96,72));
  rect->setFillColor(sf::Color(164,150,132));
  rect->setPosition(x,y);
}