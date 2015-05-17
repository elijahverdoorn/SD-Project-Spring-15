#ifndef _MAP_
#define _MAP_

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "Tile.h"
#include "Object.h"

class Map
{
	int numTiles, numObjects; //int to hold number of tiles, objects
	int numRows, numColumns; //ints to hold numbers of rows anc cols
	Tile* tileArray; // an array of tiles
	Object* objectArray; // an array of objects
public:
	//constructors
	Map();//default
	Map(int rows, int cols);//from a number of rows and cols

	//deconstructor
	~Map();

	//member methods
	int getNumTiles();//return the num tiles
	int getNumColumns();//return the num cols
	int getNumRows();//return the num rows
	Tile getTile(int par);//returns the tile position par
	void setNumColumns(int par);//set the numCols
	void setNumRows(int par);//set the numRows
	void draw(sf::RenderWindow *window);//draws both the tiles and the objects
	void drawObjects(sf::RenderWindow *window);//draw just the objects
	void drawTiles(sf::RenderWindow *window);//draw just the tiles
	void changeTile(int i, Tile par);//change the tile at i to be par
	void fill(Tile par);//change all the tiles in a map to be par

	int getNumObjects();//returns the number of objects
	Object getObject(int par);//returns the object at array poisition par
	void fillObject(Object par);//fill the object array with object par
	void changeObject(int i, Object par);//change the object at position i to par
	bool checkPosition(int x, int y);//check if the object at position x,y is passable
	int getMoveCost(int x, int y);
	//operators
	//the [] operator

};
#endif // _MAP_