// This code is to export information from Editor to a txt file
// Editor.cpp can't compile for now, but this code will be implemented into Editor




// general rule:
#include <iostream>
#include <fstream>
using namespace std;

int main () {
  // create txt file
  ofstream myfile;
  myfile.open ("example.txt");

  // for the map, numRows :
  myfile << gridSizeX <<endl;

  // for the map, numCols :
  myfile << gridSizeY <<endl;

  //numObjs
  int numObjs=0;
  //line 938: (numObjs is basically the same as currentTexture2)
  else if (currentTab == 2)//If it is an object
        {
          layer2[inBoxX][inBoxY] = currentTexture2 + 1;
          numObjs+=1;
        }

  //numChars:
  int numChars=0;
  //line 943: (numChars is basically the same as currentTexture3)
  else if (currentTab == 3)//If it is a character
        {
          layer3[inBoxX][inBoxY] = currentTexture3 + 1;
          numChars+=1;
        }


  // texture for the tile, fileName for each texture:
  //loop through all tiles, need code for printTexture
  for (int tile=0; tile < (gridSizeY*gridSizeX); tile++){
    grid[tile].printTexture();
    cout<<endl;
  }




  // texture for the objects, and passable is an int, 1 for true and 0 for false
  // fileName posX posY passable movecost



  // character
  //teamNumber fileName characterName posX posY maxSpeed maxHP maxAtk maxDef maxRange //
fileName //cursor







  myfile.close();

}



