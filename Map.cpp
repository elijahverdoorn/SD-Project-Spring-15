#include <iostream>
#include "Tile.h"
#include "Object.h"
#include "Map.h"

//constructors
Map::Map()//default
{
	numRows = 10;
	numColumns = 10;
	numTiles = numRows * numColumns;
	tileArray = new Tile [numTiles];
	objectArray = new Object [numTiles];
}

Map::Map(int rows, int cols)//from a number of rows and cols
{
	numColumns = cols;
	numRows = rows;
	numTiles = numRows * numColumns;
	tileArray = new Tile [numTiles];
	objectArray = new Object [numTiles];
}

//deconstructor
Map::~Map()
{
	//needed? not sure with vectors
}

//member methods
int Map::getNumTiles()//return the num tiles
{
	return numTiles;
}

int Map::getNumColumns()//return the num cols
{
	return numColumns;
}

int Map::getNumRows()//return the num rows
{
	return numRows;
}

int Map::getNumObjects()
{
	return numObjects;
}

Tile Map::getTile(int par)
{
	return tileArray[par];
}

Object Map::getObject(int par)
{
	return objectArray[par];
}

void Map::setNumColumns(int par)//set the numCols
{
	numColumns = par;
	numTiles = numColumns * numRows;
}

void Map::setNumRows(int par)//set the numRows
{
	numRows = par;
	numTiles = numColumns * numRows;
}

void Map::draw(sf::RenderWindow *window)
{
	//this needs to iterate through the array, drawing tiles in a loop until iterator == numcols, then newline and repeat until iterator == numrows
	//use a 2 dimensional loop and the tile's draw method
	int tempX = 0, tempY = 0;
	for (int i = 0; i < numRows; ++i)
	{
		for (int j = 0; j < numColumns; ++j)
		{
			tileArray[(i * numColumns) + j].setPosition(tempX,tempY);
			tileArray[(i * numColumns) + j].draw(window);
			objectArray[(i * numColumns) + j].setPosition(tempX,tempY);
			objectArray[(i * numColumns) + j].draw(window);
			tempX += 50;
		}
		tempY += 50;
		tempX = 0;
	}
}

void Map::changeTile(int i, Tile par)//change the tile at i to be par
{
	tileArray[i] = par;
}

void Map::changeObject(int i, Object par)
{
	objectArray[i] = par;
}

void Map::fill(Tile par)//change all the tiles in a map to be par
{
	for (int i = 0; i < numTiles; ++i)
	{
		changeTile(i, par);
	}
}

void Map::fillObject(Object par)
{
	for (int i = 0; i < numTiles; ++i)
	{
		changeObject(i, par);
	}
}

bool Map::checkPosition(int x, int y)
{
	for (int i = 0; i < numTiles; ++i)
	{
		if ((objectArray[i].getPositionX() == x) && (objectArray[i].getPositionY() == y))
		{
			return objectArray[i].isPassable();
		}
	}
}

int Map::getMoveCost(int x, int y)
{
	for (int i = 0; i < numTiles; ++i)
	{
		if ((objectArray[i].getPositionX() == x) && (objectArray[i].getPositionY() == y))
		{
			return objectArray[i].getMoveCost();
		}
	}
}
//operators
//[] operator
